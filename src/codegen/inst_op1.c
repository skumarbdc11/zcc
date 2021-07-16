/************************************************************************/
/* Selecting instruction with single operands                           */
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "zstruct.h"
#include "inst.h"
#include "zutils.h"

#undef _DEBUG

extern PCR_t g_cr_block;

#define TABSIZE (sizeof(instop1)/sizeof(INST_t))

static INST_t instop1[] =
{
	{0,0, 1, {REGISTER_TYPE,0,0,0}},

	{0,0, 1, {ADDRESS_TYPE,0,0,0}},

	{0,0, 1, {REGIND_TYPE,0,0,0}},

	{0,0, 1, {REGREL_TYPE,0,0,0}},
};

static INST_t instpushpop[] =
{
	{0,0, 1, {REGISTER_TYPE,0,0,0}},

	{0,0, 1, {CONSTANT_TYPE,0,0,0}},
};

static INST_t jpcc ={CTRL,JP, 1, {ADDRESS_TYPE,0,0,0}};
static INST_t call ={CTRL,CALL, 1, {ADDRESS_TYPE,0,0,0}};
static INST_t un_link ={CTRL,UNLINK, 0, {0,0,0,0}};
static INST_t ret ={CTRL,RET, 0, {0,0,0,0}};

PCR_t inst_op1(INST_e inst, NTYPE_e op1, PLIST_t opval)
{
	int ndx=0;
	PCR_t pnew=0;

	for(ndx=0;ndx<TABSIZE;ndx++)
	{
		if(op1==instop1[ndx].op_type[0])
			break;
	}

	if(ndx==TABSIZE)
	{
#ifdef _DEBUG
		printf("No match for target instruction");
#endif // _DEBUG
		return NULL;
	}

	pnew = (PCR_t)calloc(1,sizeof(CR_t));
	pnew->pinst = (PINST_t)calloc(1,sizeof(INST_t));

	pnew->cr_type = CRINST;
	pnew->directive = 0;
	pnew->pinst->inst = inst;
	pnew->pinst->inst_type = LOAD;
	pnew->pinst->num_op = 1;
	pnew->pinst->op_type[0] = op1;
	pnew->operand[0] = opval;

	g_cr_block = add_cr(g_cr_block, pnew);

	return (pnew);
}

PCR_t inst_op1_b(INST_e inst, NTYPE_e op1, PLIST_t opval)
{
	PCR_t pnew=0;

	if(op1==REGISTER_TYPE)
		return NULL;
	pnew = inst_op1(inst,op1,opval);
	if(pnew)
		pnew->directive = B;

	return (pnew);
}

PCR_t inst_op1_w(INST_e inst, NTYPE_e op1, PLIST_t opval)
{
	PCR_t pnew=0;

	if(op1==REGISTER_TYPE)
		return NULL;
	pnew = inst_op1(inst,op1,opval);
	if(pnew)
		pnew->directive = W;

	return (pnew);
}

PCR_t inst_op1_cc(DIR_e cc, NTYPE_e op1, PLIST_t opval)
{
	PCR_t pnew=0;

	if(op1!=REGISTER_TYPE)
		return NULL;
	pnew = inst_op1(LDCC,op1,opval);
	if(pnew)
		pnew->directive = cc;

	return (pnew);
}

void inst_op1_jpcc(DIR_e cc, PLABEL_t label)
{
	PCR_t pnew=0;

	pnew = new_cr(CRINST, &jpcc);
	pnew->directive = cc;
	pnew->operand[0] = new_node(ADDRESS_TYPE,(void*)label);

	g_cr_block = add_cr(g_cr_block, pnew);
}

void inst_call(PLABEL_t label)
{
	PCR_t pnew=0;

	pnew = new_cr(CRINST, &call);
	pnew->directive = 0;
	pnew->operand[0] = new_node(ADDRESS_TYPE,(void*)label);

	g_cr_block = add_cr(g_cr_block, pnew);
}

PCR_t inst_pushpop(INST_e inst, NTYPE_e op1, PLIST_t opval)
{
	int ndx=0;
	PCR_t pnew=0;

	for(ndx=0;ndx<TABSIZE;ndx++)
	{
		if(op1==instpushpop[ndx].op_type[0])
			break;
	}

	if(ndx==TABSIZE)
	{
#ifdef _DEBUG
		printf("No match for target instruction");
#endif // _DEBUG
		return NULL;
	}

	pnew = (PCR_t)calloc(1,sizeof(CR_t));
	pnew->pinst = (PINST_t)calloc(1,sizeof(INST_t));

	pnew->cr_type = CRINST;
	pnew->directive = 0;
	pnew->pinst->inst = inst;
	pnew->pinst->inst_type = LOAD;
	pnew->pinst->num_op = 1;
	pnew->pinst->op_type[0] = op1;
	pnew->operand[0] = opval;

	g_cr_block = add_cr(g_cr_block, pnew);

	return (pnew);
}

PCR_t inst_pushpop_b(INST_e inst, NTYPE_e op1, PLIST_t opval)
{
	PCR_t pnew=0;

	if((inst == POP) && (op1==CONSTANT_TYPE))
		return NULL;
	pnew = inst_op1(inst,op1,opval);
	if(pnew)
		pnew->directive = B;

	return (pnew);
}

PCR_t inst_pushpop_w(INST_e inst, NTYPE_e op1, PLIST_t opval)
{
	PCR_t pnew=0;

	if((inst == POP) && (op1==CONSTANT_TYPE))
		return NULL;
	pnew = inst_op1(inst,op1,opval);
	if(pnew)
		pnew->directive = W;

	return (pnew);
}

PCR_t inst_link(int stacksize)
{
	return (inst_pushpop(LINK,CONSTANT_TYPE,
		new_node(CONSTANT_TYPE,new_data(INT_t,stacksize))));
}

void inst_unlink()
{
	PCR_t pnew=0;

	pnew = new_cr(CRINST, &un_link);
	pnew->directive = 0;

	g_cr_block = add_cr(g_cr_block, pnew);
}

void inst_ret()
{
	PCR_t pnew=0;

	pnew = new_cr(CRINST, &ret);
	pnew->directive = 0;

	g_cr_block = add_cr(g_cr_block, pnew);
}

#define LABEL(x) ((PLABEL_t)((x->operand[0])->node_ptr))
PCR_t get_jp(PCR_t label)
{
	PCR_t pnew=0;

	pnew = new_cr(CRINST, &jpcc);
	pnew->directive = 0;/* .T. */
	pnew->operand[0] = new_node(ADDRESS_TYPE,(void*)LABEL(label));

	return (pnew);
}
