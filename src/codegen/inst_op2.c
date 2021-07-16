/************************************************************************/
/* Selecting instruction with two operands                              */
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "zstruct.h"
#include "inst.h"
#include "zutils.h"

#undef _DEBUG

extern PCR_t g_cr_block;

#define TABSIZE (sizeof(instop2)/sizeof(INST_t))

static INST_t instop2[] =
{
	{0,0, 2, {REGISTER_TYPE,CONSTANT_TYPE,0,0}},
	{0,0, 2, {REGISTER_TYPE,REGISTER_TYPE,0,0}},
	{0,0, 2, {REGISTER_TYPE,ADDRESS_TYPE,0,0}},
	{0,0, 2, {REGISTER_TYPE,REGIND_TYPE,0,0}},
	{0,0, 2, {REGISTER_TYPE,REGINC_TYPE,0,0}},
	{0,0, 2, {REGISTER_TYPE,REGREL_TYPE,0,0}},
	{0,0, 2, {REGISTER_TYPE,FPREL_TYPE,0,0}},

	{0,0, 2, {ADDRESS_TYPE,REGISTER_TYPE,0,0}},

	{0,0, 2, {REGIND_TYPE,CONSTANT_TYPE,0,0}},
	{0,0, 2, {REGIND_TYPE,REGISTER_TYPE,0,0}},

	{0,0, 2, {REGREL_TYPE,REGISTER_TYPE,0,0}},

	{0,0, 2, {FPREL_TYPE,REGISTER_TYPE,0,0}},

	{0,0, 2, {REGDEC_TYPE,CONSTANT_TYPE,0,0}},
	{0,0, 2, {REGDEC_TYPE,REGISTER_TYPE,0,0}},

	{0,0, 2, {REGINC_TYPE,CONSTANT_TYPE,0,0}},
	{0,0, 2, {REGINC_TYPE,REGISTER_TYPE,0,0}},
};

PCR_t inst_op2(INST_e inst, NTYPE_e op1, NTYPE_e op2, PLIST_t optval1, PLIST_t optval2)
{
	int ndx=0;
	PCR_t pnew=0;

	for(ndx=0;ndx<TABSIZE;ndx++)
	{
		if((op1==instop2[ndx].op_type[0])&&(op2==instop2[ndx].op_type[1]))
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
	if((inst==CP) || (inst==CPC))
		pnew->pinst->inst_type = COMPARE;
	else
		pnew->pinst->inst_type = LOAD;
	pnew->pinst->num_op = 2;
	pnew->pinst->op_type[0] = op1;
	pnew->pinst->op_type[1] = op2;
	pnew->operand[0] = optval1;
	pnew->operand[1] = optval2;

	g_cr_block = add_cr(g_cr_block, pnew);

	return (pnew);
}

PCR_t inst_op2_b(INST_e inst, NTYPE_e op1, NTYPE_e op2, PLIST_t optval1, PLIST_t optval2)
{
	PCR_t pnew=0;

	if(op1==REGISTER_TYPE)
		return NULL;
	pnew = inst_op2(inst,op1,op2,optval1,optval2);
	if(pnew)
		pnew->directive = B;

	return (pnew);
}

PCR_t inst_op2_w(INST_e inst, NTYPE_e op1, NTYPE_e op2, PLIST_t optval1, PLIST_t optval2)
{
	PCR_t pnew=0;

	if(op1==REGISTER_TYPE)
		return NULL;
	pnew = inst_op2(inst,op1,op2,optval1,optval2);
	if(pnew)
		pnew->directive = W;

	return (pnew);
}

PCR_t inst_op2_sb(INST_e inst, NTYPE_e op1, NTYPE_e op2, PLIST_t optval1, PLIST_t optval2)
{
	PCR_t pnew=0;

	if(op1!=REGISTER_TYPE)
		return NULL;
	pnew = inst_op2(inst,op1,op2,optval1,optval2);
	if(pnew)
		pnew->directive = SB;

	return (pnew);
}

PCR_t inst_op2_ub(INST_e inst, NTYPE_e op1, NTYPE_e op2, PLIST_t optval1, PLIST_t optval2)
{
	PCR_t pnew=0;

	if(op1!=REGISTER_TYPE)
		return NULL;
	pnew = inst_op2(inst,op1,op2,optval1,optval2);
	if(pnew)
		pnew->directive = UB;

	return (pnew);
}

PCR_t inst_op2_sw(INST_e inst, NTYPE_e op1, NTYPE_e op2, PLIST_t optval1, PLIST_t optval2)
{
	PCR_t pnew=0;

	if(op1!=REGISTER_TYPE)
		return NULL;
	pnew = inst_op2(inst,op1,op2,optval1,optval2);
	if(pnew)
		pnew->directive = SW;

	return (pnew);
}

PCR_t inst_op2_uw(INST_e inst, NTYPE_e op1, NTYPE_e op2, PLIST_t optval1, PLIST_t optval2)
{
	PCR_t pnew=0;

	if(op1!=REGISTER_TYPE)
		return NULL;
	pnew = inst_op2(inst,op1,op2,optval1,optval2);
	if(pnew)
		pnew->directive = UW;

	return (pnew);
}


