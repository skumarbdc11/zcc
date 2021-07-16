/************************************************************************/
/* Reference to operands                                                */
/************************************************************************/

#include "zstruct.h"
#include "register.h"
#include "inst.h"
#include "move.h"
#include "zinst.h"
#include "zutils.h"

#define sign(x)	get_listitem_sign((x))
#define size(x) get_listitem_typesize((x))

extern PCR_t g_cr_block;

PLIST_t inst8(INST_e inst, PLIST_t op1, PLIST_t op2)
{
	inst_op2_b(inst, op1->node_type, op2->node_type, op1, op2);
	return op1;
}

PLIST_t inst_b(INST_e inst, PLIST_t op1, PLIST_t op2)
{
	if(get_listitem_sign(op2))
		inst_op2_sb(inst, op1->node_type, op2->node_type, op1, op2);
	else
		inst_op2_ub(inst, op1->node_type, op2->node_type, op1, op2);
	return op1;
}

PLIST_t inst16(INST_e inst, PLIST_t op1, PLIST_t op2)
{
	inst_op2_w(inst, op1->node_type, op2->node_type, op1, op2);
	return op1;
}

PLIST_t inst_w(INST_e inst, PLIST_t op1, PLIST_t op2)
{
	if(get_listitem_sign(op2))
		inst_op2_sw(inst, op1->node_type, op2->node_type, op1, op2);
	else
		inst_op2_uw(inst, op1->node_type, op2->node_type, op1, op2);
	return op1;
}

PLIST_t instr(INST_e inst, PLIST_t op1, PLIST_t op2)
{
	PTYPE_t type=0;
	PLIST_t src=0, dst=0;
	PLIST_t temp=0;

	switch(inst)
	{
	case MUL:
		{
			if(sign(op1) || sign(op1))
				inst = SMUL;
			if(op1->node_type != REGISTER_TYPE)
			{
				dst = newreg(sign(op1), size(op1));
				dst = move(dst, op1);
			}
			else
				dst = op1;
			if(op2->node_type != REGISTER_TYPE)
			{
				src = newreg(sign(op2), size(op2));
				src = move(src, op2);
			}
			else
				src = op2;
			
			inst_op2(inst, dst->node_type, src->node_type, dst, src);
			return (dst);
		}
		break;
	case UDIV:
		{
			if(sign(op1) || sign(op1))
				inst = SDIV;
			if(op1->node_type != REGISTER_TYPE)
			{
				dst = newreg(sign(op1), size(op1));
				dst = move(dst, op1);
			}
			else
				dst = op1;
			if(op2->node_type != REGISTER_TYPE)
			{
				src = newreg(sign(op2), size(op2));
				src = move(src, op2);
			}
			else
				src = op2;
			inst_op2(inst, dst->node_type, src->node_type, dst, src);
			return (dst);
		}
		break;
	case SLL:
		{
			if(op1->node_type != REGISTER_TYPE)
			{
				dst = newreg(sign(op1), size(op1));
				dst = move(dst, op1);
			}
			else
				dst = op1;
			if(op2->node_type != CONSTANT_TYPE)
			{
				if(op2->node_type != REGISTER_TYPE)
				{
					src = newreg(sign(op2), size(op2));
					src = move(src, op2);
				}
				else
					src = op2;
			}
			else
				src = op2;
			inst_op2(inst, dst->node_type, src->node_type, dst, src);
			return (dst);
		}
		break;
	case SRL:
		{
			if(sign(op1))
				inst = SRA;
			if(op1->node_type != REGISTER_TYPE)
			{
				dst = newreg(sign(op1), size(op1));
				dst = move(dst, op1);
			}
			else
				dst = op1;
			if(op2->node_type != CONSTANT_TYPE)
			{
				if(op2->node_type != REGISTER_TYPE)
				{
					src = newreg(sign(op2), size(op2));
					src = move(src, op2);
				}
				else
					src = op2;
			}
			else
				src = op2;
			inst_op2(inst, dst->node_type, src->node_type, dst, src);
			return (dst);
		}
		break;

	case CPZ:
		{
			if(!inst_op1(inst, op1->node_type, op1))
			{
				dst = newreg(sign(op1),size(op1));
				dst = move(dst,op1);
				inst_op1(inst, dst->node_type, dst);
			}
			return (dst);
		}
		break;

	case LEA:
		{
			op1 = newreg(0,32);
			if(op2->node_type == IDENTIFIER_TYPE)
			{
				type = ((PIDENT_t)op2->node_ptr)->pvar_type;
				src = newaddress(((PIDENT_t)op2->node_ptr), 0);
				inst_op2(inst, op1->node_type, src->node_type, op1, src);
			}
			else
			{
				src = op2;
				inst_op2(inst, op1->node_type, src->node_type, op1, src);
			}
			return (op1);
		}
		break;
	}

	dst = refer(op1);
	switch(op2->node_type) /* destination operand */
	{
	case IDENTIFIER_TYPE:
		{
			type = ((PIDENT_t)op2->node_ptr)->pvar_type;
			src = newaddress(((PIDENT_t)op2->node_ptr), 0);
			switch(type->type)
			{
			case CHAR_t:
				dst = inst_b(inst,dst,src); break;
			case SHORT_t:
				dst = inst_w(inst,dst,src); break;
			case INT_t:
			case LONG_t:
				inst_op2(inst, dst->node_type, src->node_type, dst, src);
				break;
			}
		}
		break;
	case REGISTER_TYPE:
	case CONSTANT_TYPE:
		{
			if(dst->node_type != REGISTER_TYPE)
				switch(get_listitem_type(dst))
				{
				case CHAR_t:
					dst = inst8(inst,dst,op2); break;
				case SHORT_t:
					dst = inst16(inst,dst,op2); break;
				case INT_t:
				case LONG_t:
					inst_op2(inst, dst->node_type, op2->node_type, dst, op2);
					break;
				}
			else
				inst_op2(inst, dst->node_type, op2->node_type, dst, op2);
		}
		break;
	case ADDRESS_TYPE:
	case REGREL_TYPE:
	case FPREL_TYPE:
		{
			if(dst->node_type != REGISTER_TYPE)
			{
				switch(get_listitem_type(dst))
				{
				case CHAR_t:
					temp = newreg(get_listitem_sign(dst),8); break;
				case SHORT_t:
					temp = newreg(get_listitem_sign(dst),16); break;
				case INT_t:
				case LONG_t:
					temp = newreg(get_listitem_sign(dst),32); break;
				}
				dst = instr(LD,temp,op2);
			}
			switch(get_listitem_type(op2))
			{
			case CHAR_t:
				dst = inst8(inst,dst,op2); break;
			case SHORT_t:
				dst = inst16(inst,dst,op2); break;
			case INT_t:
			case LONG_t:
				inst_op2(inst, dst->node_type, op2->node_type, dst, op2); break;
			}
		}
		break;
	case REGIND_TYPE:
	case REGDEC_TYPE:
	case REGINC_TYPE:
		{
			switch(dst->node_type)
			{
			case CONSTANT_TYPE:
			case REGISTER_TYPE:
				break;
			default:
				switch(get_listitem_type(dst))
				{
				case CHAR_t:
					temp = newreg(get_listitem_sign(dst),8); break;
				case SHORT_t:
					temp = newreg(get_listitem_sign(dst),16); break;
				case INT_t:
				case LONG_t:
					temp = newreg(get_listitem_sign(dst),32); break;
				}
				dst = instr(LD,temp,op2);
				break;
			}
			switch(get_listitem_type(op2))
			{
			case CHAR_t:
				dst = inst8(inst,dst,op2); break;
			case SHORT_t:
				dst = inst16(inst,dst,op2); break;
			case INT_t:
			case LONG_t:
				inst_op2(inst, dst->node_type, op2->node_type, dst, op2); break;
			}
		}
		break;
	}

	return (dst);
}

PLIST_t instr_ldcc(DIR_e cc)
{
	PLIST_t cc_reg=0;

	cc_reg = newreg(0,32);
	inst_op1_cc(cc,REGISTER_TYPE,cc_reg);

	return (cc_reg);
}

#define LABEL(x) ((PLABEL_t)((x->operand[0])->node_ptr))
void instr_jpcc(DIR_e cc, PCR_t crlabel)
{
	inst_op1_jpcc(cc,LABEL(crlabel));
}

PLIST_t instr_modulus(PLIST_t op1, PLIST_t op2)
{
	PLIST_t src=0, dst=0;
	INST_e inst;

	if(sign(op1) || sign(op1))
		inst = SDIV;
	else
		inst = UDIV;
	if(op1->node_type != REGISTER_TYPE)
		dst = newreg(sign(op1), size(op1));
	else
		dst = op1;
	if(op2->node_type != REGISTER_TYPE)
		src = newreg(sign(op2), size(op2));
	else
		src = op2;
	dst = move(dst, op1);
	src = move(src, op2);
	inst_op2(inst, dst->node_type, src->node_type, dst, src);
	return (src);
}
