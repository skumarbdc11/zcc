/************************************************************************/
/* Register                                                             */
/************************************************************************/
#include <stdlib.h>
#include <string.h>

#include "zstruct.h"
#include "register.h"

#define RTABSIZE 13
/* register table */
REGTAB_t regtab[RTABSIZE] = {
	{ 0, FREE, "R0"	},
	{ 1, FREE, "R1"	},
	{ 2, FREE, "R2"	},
	{ 3, FREE, "R3"	},
	{ 4, FREE, "R4"	},
	{ 5, FREE, "R5"	},
	{ 6, FREE, "R6"	},
	{ 7, FREE, "R7"	},
	{ 8, FREE, "R8"	},
	{ 9, FREE, "R9"	},
	{10, FREE, "R10"	},
	{11, FREE, "R11"	},
	{12, FREE, "R12"	}
};

REGTAB_t r13reg = { 13, FREE, "R13" };

/* highest pseudo register number */
int max_pseudo_num=0;

PLIST_t newreg(char sign, int size)
{
	PREG_t pnew=0;
	PLIST_t pnode=0;

	pnew = (PREG_t)calloc(1,sizeof(REG_t));
	pnode = (PLIST_t)calloc(1,sizeof(LIST_t));

	pnew->pseudo_flag = 1;
	pnew->u.number = max_pseudo_num++;
	pnew->sign = (sign == UNSIGNED_t)?0:1;
	pnew->size = size;
	pnew->offset = 0;

	pnode->node_type = REGISTER_TYPE;
	pnode->node_ptr = pnew;

	return (pnode);
}

PLIST_t spreg()
{
	PREG_t pnew=0;
	PLIST_t pnode=0;

	pnew = (PREG_t)calloc(1,sizeof(REG_t));
	pnode = (PLIST_t)calloc(1,sizeof(LIST_t));

	pnew->pseudo_flag = 0;
	strcpy(pnew->u.name,"R15");
	pnew->sign = 0;
	pnew->size = 32;
	pnew->offset = 0;

	pnode->node_type = REGISTER_TYPE;
	pnode->node_ptr = pnew;

	return (pnode);
}

PLIST_t returnreg()
{
	PREG_t pnew=0;
	PLIST_t pnode=0;

	pnew = (PREG_t)calloc(1,sizeof(REG_t));
	pnode = (PLIST_t)calloc(1,sizeof(LIST_t));

	pnew->pseudo_flag = 0;
	strcpy(pnew->u.name,"R13");
	pnew->sign = 0;
	pnew->size = 32;
	pnew->offset = 0;

	pnode->node_type = REGISTER_TYPE;
	pnode->node_ptr = pnew;

	return (pnode);
}

int get_freereg()
{
	int index=0;

	for(index=0;index<RTABSIZE;index++)
	{
		if(regtab[index].status == FREE)
			return (regtab[index].number);
	}

	return (-1); /* no free registers */
}

int get_r13reg()
{
	if(r13reg.status == FREE)
		return r13reg.number;

	return (-1); /* may have to spill register */
}

void setreg_used(int regnum)
{
	if((regnum>=0)&&(regnum<RTABSIZE))
		regtab[regnum].status = USED;

	if(regnum == r13reg.number)
		r13reg.status = USED;
}

void free_registers()
{
	int index=0;

	for(index=0;index<RTABSIZE;index++)
		regtab[index].status = FREE;
}

void free_r13reg()
{
	r13reg.status = FREE;
}
