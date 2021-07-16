/************************************************************************/
/* Register allocation routines                                         */
/************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "zstruct.h"
#include "register.h"
#include "inst.h"
#include "zutils.h"
#include "zralloc.h"


extern PIDENT_t g_current_function;
extern int max_pseudo_num;
extern REGTAB_t regtab[];
extern PCR_t g_cr_block;
extern long g_stack_size;
extern FILE *outfile;

static int crnode_size=0;
static char msg[256];
static unsigned short regmask=0x0000;

static void SET_MASK(int bit)
{
	unsigned short mask=1;

	mask = mask << (16-(bit+1));
	regmask |= mask;
}

static int number_block(PCR_t crblock)
{
	int index=0;

	while(crblock)
	{
		crblock->index = index++;
		crblock = crblock->next;
	}

	return (index-1);
}

static int find_range(PCR_t crblock, int regnum, int *start, int *end)
{
	int index=0;
	int numop=0;
	PREG_t reg=0;

	*start = *end = -1;
	for(index=0;index<=crnode_size;index++)
	{
		if(crblock->cr_type == CRINST)
		{
			numop = (crblock->pinst->num_op) ? crblock->pinst->num_op-1 : 0;
			while(numop>=0)
			{
				switch(crblock->pinst->op_type[numop])
				{
				case REGISTER_TYPE:
				case REGINC_TYPE:
				case REGDEC_TYPE:
				case REGIND_TYPE:
				case REGREL_TYPE:
					{
						reg = (PREG_t)(crblock->operand[numop]->node_ptr);
						if((reg->pseudo_flag) && (reg->u.number==regnum))
						{
							/* got it */
							if(*start == (-1)) /* first node */
								*start = crblock->index;
							else
								*end = crblock->index;
						}
					}
					break;
				}
				--numop;
			}
		}
		crblock = crblock->next;
	}

	if((*start!=(-1)) && (*end==(-1)))
		*end = *start;
	else if((*start==(-1)) && (*end==(-1)))
		return 0;

	return 1;
}

static void display_nodes(PREGNODE_t pnode)
{
	PARCLIST_t arclist=0;

	printf("\n-------Register Nodes");
	while(pnode)
	{
		if(pnode->colored)
		{
			sprintf(msg, "\n<node> $R%d(%d-%d) colored with R%d <node>",
				pnode->pseudoreg, pnode->start, pnode->end, pnode->reg);
		}
		else
		{
			sprintf(msg, "\n<node> $R%d(%d-%d) not colored <node>",
				pnode->pseudoreg, pnode->start, pnode->end);
		}
		puts(msg);

		arclist = pnode->parcs;
		printf("\n\t<arcs> ");
		while(arclist)
		{
			sprintf(msg, "$R%d ", arclist->node->pseudoreg);
			printf("%s",msg);
			arclist = arclist->next;
		}
		printf("<arcs>");

		pnode = pnode->next;
	}
}

static PREGNODE_t create_nodes(PCR_t crblock)
{
	PREGNODE_t pnode=0, phead=0, ptail=0;
	int regnum=0, start=0, end=0;

	for(regnum=0; regnum<max_pseudo_num; regnum++)
	{
		if(find_range(crblock,regnum,&start,&end))
		{
			pnode = (PREGNODE_t)calloc(1,sizeof(REGNODE_t));
			pnode->pseudoreg = regnum;
			pnode->start = start;
			pnode->end = end;
			pnode->colored = 0; /* not colored yet */

			if(phead)
				ptail->next = pnode;
			else
				phead = pnode;
			ptail = pnode;
		}
	}

	return (phead);
}


/*
 *	1. If there is no arcs for the node then color it with free reg and leave it free
 *
 *  2. If there is an arc then color the current node with free reg and mark it as used
 *     2.1 Then parse each nodes in its arc list by recursive call to color_node
 *     2.2 Once all the arc list is colored then free all the used registers
 */
static int color_node(PREGNODE_t regnode)
{
	PREGNODE_t arcnode=0;
	PARCLIST_t parcs=0;

	if(!regnode->colored)
	{
		/* 1 */
		if(!regnode->parcs)
		{
			regnode->reg = get_freereg();
			if(regnode->reg == -1)
			{
				regnode->reg = get_r13reg();

				if(regnode->reg == -1)
				{
					sprintf(msg,"\n**No register available for $R%d(%d-%d)",
						regnode->pseudoreg, regnode->start, regnode->end);
					puts(msg);
					return 0;
				}
			}
#ifdef _DEBUG
			sprintf(msg, "\n--Reg $R%d(%d-%d) colored with R%d",
				regnode->pseudoreg, regnode->start, regnode->end, regnode->reg);
			puts(msg);
#endif // _DEBUG
			SET_MASK(regnode->reg);
			regnode->colored = 1;
		}
		else
		{
			/* 2 */
			regnode->reg = get_freereg();
			if(regnode->reg == -1)
			{
				sprintf(msg,"\n**No register available for $R%d(%d-%d)",
					regnode->pseudoreg, regnode->start, regnode->end);
				puts(msg);
				return 0;
			}
			setreg_used(regnode->reg);
#ifdef _DEBUG
			sprintf(msg, "\n--Reg $R%d(%d-%d) colored with R%d",
				regnode->pseudoreg, regnode->start, regnode->end, regnode->reg);
			puts(msg);
#endif // _DEBUG
			SET_MASK(regnode->reg);
			regnode->colored = 1;

			parcs = regnode->parcs;
			while(parcs)
			{
				/* 2.1 */
				arcnode = parcs->node;
				if(!color_node(arcnode))
					return 0;
				parcs = parcs->next;
			}

			/* 2.2 */
			free_registers();
		}
	}

	return 1;
}

static int in_range(PREGNODE_t r1, PREGNODE_t r2)
{
	if( ((r2->start>=r1->start) && (r2->start<=r1->end)) ||
		((r2->end>=r1->start) && (r2->end<=r1->end)) )
		return 1;

	return 0;
}

static void create_arcs(PREGNODE_t pnodes)
{
	PREGNODE_t regnode=0, tempnode=0;
	PARCLIST_t arcnode=0, ptail=0;

	regnode = pnodes;
	while(regnode)
	{
		ptail = regnode->parcs;
		while(ptail)
		{
			if(!ptail->next)
				break;
			ptail = ptail->next;
		}

		for(tempnode = pnodes; tempnode; tempnode=tempnode->next)
		{
			if((tempnode->pseudoreg != regnode->pseudoreg) &&
				(tempnode->colored == 0))
			{
				if(in_range(regnode,tempnode))
				{
					arcnode = (PARCLIST_t)calloc(1,sizeof(ARCLIST_t));
					arcnode->node = tempnode;

					if(regnode->parcs)
						ptail->next = arcnode;
					else
						regnode->parcs = arcnode;
					ptail = arcnode;
				}
			}
		}

		regnode = regnode->next;
	}
}

static int get_regnum(PREGNODE_t pnodes, int pseudoreg)
{
	while(pnodes)
	{
		if(pnodes->pseudoreg == pseudoreg)
			return (pnodes->reg);
		pnodes = pnodes->next;
	}

	return 0;
}

static void modify_crblock(PCR_t crblock, PREGNODE_t regnodes)
{
	int index=0;
	int numop=0;
	PREG_t reg=0;
	int actreg=0;

	for(index=0;index<=crnode_size;index++)
	{
		if(crblock->cr_type == CRINST)
		{
			numop = (crblock->pinst->num_op) ? crblock->pinst->num_op-1 : 0;
			while(numop>=0)
			{
				switch(crblock->pinst->op_type[numop])
				{
				case REGISTER_TYPE:
				case REGINC_TYPE:
				case REGDEC_TYPE:
				case REGIND_TYPE:
				case REGREL_TYPE:
					{
						reg = (PREG_t)(crblock->operand[numop]->node_ptr);
						if(reg->pseudo_flag)
						{
							actreg = get_regnum(regnodes,reg->u.number);

							if((actreg<0) && (actreg>13))
							{
								return; //***
							}
							reg->pseudo_flag = 0;
							strcpy(reg->u.name, regtab[actreg].name);
						}
					}
					break;
				}
				--numop;
			}
		}
		crblock = crblock->next;
	}
}

/*
 *	Interfaces
 */
int gcolor(PCR_t crblock)
{
	PREGNODE_t pnodes=0, regnode=0;

	regmask = 0;
	/* Find the total code records */
	crnode_size = number_block(crblock);

	/* create register nodes */
	pnodes = create_nodes(crblock);

	if(pnodes)
	{
#ifdef _DEBUG
		display_nodes(pnodes);
#endif // _DEBUG

		/* draw arcs for the interference list */
		create_arcs(pnodes);

#ifdef _DEBUG
		display_nodes(pnodes);
#endif // _DEBUG

		/* coloring the nodes */
		regnode = pnodes;
		while(regnode)
		{
			if(!color_node(regnode))
				return 0;

			regnode = regnode->next;
		}

#ifdef _DEBUG
		display_nodes(pnodes);
#endif // _DEBUG
	}
	else
		return 0;

	/* modify code record blocks */
	modify_crblock(crblock, pnodes);

#ifdef _DEBUG
	printf("\nREG_MASK: %04X\nStacksize: %d", regmask, g_stack_size);
#endif // _DEBUG

	g_cr_block = 0;
	inst_link(g_stack_size);
	if(regmask)
	{
		inst_pushpop(PUSHM,CONSTANT_TYPE,new_node(CONSTANT_TYPE,new_data(INT_t,regmask)));
		g_cr_block = add_cr(g_cr_block,crblock);
		inst_pushpop(POPM,CONSTANT_TYPE,new_node(CONSTANT_TYPE,new_data(INT_t,regmask)));
	}
	inst_unlink();
	inst_ret();

	return 1;
}
