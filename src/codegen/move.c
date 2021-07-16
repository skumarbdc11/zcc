/************************************************************************/
/* Reference to operands                                                */
/************************************************************************/

#include "zstruct.h"
#include "register.h"
#include "inst.h"
#include "move.h"
#include "zutils.h"

extern PCR_t g_cr_block;


PLIST_t refer(PLIST_t op)
{
	PTYPE_t type=0;
	PLIST_t op1=0, op2=0, dst=0;

	dst = op;
	switch(op->node_type)
	{
	case IDENTIFIER_TYPE:
		{
			type = ((PIDENT_t)op->node_ptr)->pvar_type;
			op2 = newaddress(((PIDENT_t)op->node_ptr), 0);
			op1 = newreg((char)type->issigned, type->size);
			switch(type->type)
			{
			case CHAR_t:
				if(inst_op2_b(LD,op1->node_type,op2->node_type,op1,op2))
					return (op1);
				break;
			case SHORT_t:
				if(inst_op2_w(LD,op1->node_type,op2->node_type,op1,op2))
					return (op1);
				break;
			case INT_t:
			case LONG_t:
				if(inst_op2(LD,op1->node_type,op2->node_type,op1,op2))
					return (op1);
				break;
			}
			dst = move(op1,op2);
		}
		break;
/*
	case ADDRESS_TYPE:
	case REGREL_TYPE:
	case FPREL_TYPE:
	case REGIND_TYPE:
	case REGDEC_TYPE:
	case REGINC_TYPE:
		{
			switch(get_listitem_type(op))
			{
			case CHAR_t:
				op1 = newreg(get_listitem_sign(op),8); break;
			case SHORT_t:
				op1 = newreg(get_listitem_sign(op),16); break;
			case INT_t:
			case LONG_t:
				op1 = newreg(get_listitem_sign(op),32); break;
			}
			dst = move(op1,op);
		}
		break;
*/
	}

	return (dst);
}

PLIST_t move8(PLIST_t op1, PLIST_t op2)
{
	inst_op2_b(LD, op1->node_type, op2->node_type, op1, op2);
	return op1;
}

PLIST_t move_b(PLIST_t op1, PLIST_t op2)
{
	if(get_listitem_sign(op2))
		inst_op2_sb(LD, op1->node_type, op2->node_type, op1, op2);
	else
		inst_op2_ub(LD, op1->node_type, op2->node_type, op1, op2);
	return op1;
}

PLIST_t move16(PLIST_t op1, PLIST_t op2)
{
	inst_op2_w(LD, op1->node_type, op2->node_type, op1, op2);
	return op1;
}

PLIST_t move_w(PLIST_t op1, PLIST_t op2)
{
	if(get_listitem_sign(op2))
		inst_op2_sw(LD, op1->node_type, op2->node_type, op1, op2);
	else
		inst_op2_uw(LD, op1->node_type, op2->node_type, op1, op2);
	return op1;
}

PLIST_t move(PLIST_t op1, PLIST_t op2)
{
	PTYPE_t type=0;
	PLIST_t src=0, dst=0;
	PLIST_t temp=0;

	src = refer(op2);
	switch(op1->node_type) /* destination operand */
	{
	case VARIABLE_t:
	case IDENTIFIER_TYPE:
		{
			TYPE_e vtype;

			type = ((PIDENT_t)op1->node_ptr)->pvar_type;
			dst = newaddress(((PIDENT_t)op1->node_ptr), 0);
			vtype = get_basetype(type);
			switch(vtype)
			{
			case CHAR_t:
				dst = move8(dst,src); break;
			case SHORT_t:
				dst = move16(dst,src); break;
			case INT_t:
			case LONG_t:
				dst = move(dst,src); break;
			}
		}
		break;
	case REGISTER_TYPE:
		{
			if(src->node_type != REGISTER_TYPE)
			{
				switch(get_listitem_type(src))
				{
				case CHAR_t:
					dst = move_b(op1,src); break;
				case SHORT_t:
					dst = move_w(op1,src); break;
				case INT_t:
				case LONG_t:
					inst_op2(LD, op1->node_type, src->node_type, op1, src);
					break;
				}
				dst = op1;
			}
			else
				dst = src;
				//inst_op2(LD, op1->node_type, src->node_type, op1, src);
			//dst = op1;
		}
		break;
	case CONSTANT_TYPE:
		{
			if(src->node_type != REGISTER_TYPE)
				switch(get_listitem_type(src))
				{
				case CHAR_t:
					dst = move_b(op1,src); break;
				case SHORT_t:
					dst = move_w(op1,src); break;
				case INT_t:
				case LONG_t:
					inst_op2(LD, op1->node_type, src->node_type, op1, src);
					break;
				}
			else
				inst_op2(LD, op1->node_type, src->node_type, op1, src);
			dst = op1;
		}
		break;
	case ADDRESS_TYPE:
	case REGREL_TYPE:
	case FPREL_TYPE:
		{
			if(src->node_type != REGISTER_TYPE)
			{
				switch(get_listitem_type(src))
				{
				case CHAR_t:
					temp = newreg(get_listitem_sign(src),8); break;
				case SHORT_t:
					temp = newreg(get_listitem_sign(src),16); break;
				case INT_t:
				case LONG_t:
					temp = newreg(get_listitem_sign(src),32); break;
				}
				src = move(temp,src);
			}
			switch(get_listitem_type(op1))
			{
			case CHAR_t:
				dst = move8(op1,src); break;
			case SHORT_t:
				dst = move16(op1,src); break;
			case INT_t:
			case LONG_t:
				inst_op2(LD, op1->node_type, src->node_type, op1, src); break;
			}
			dst = op1;
		}
		break;
	case REGIND_TYPE:
	case REGDEC_TYPE:
	case REGINC_TYPE:
		{
			switch(src->node_type)
			{
			case CONSTANT_TYPE:
			case REGISTER_TYPE:
				break;
			default:
				switch(get_listitem_type(src))
				{
				case CHAR_t:
					temp = newreg(get_listitem_sign(src),8); break;
				case SHORT_t:
					temp = newreg(get_listitem_sign(src),16); break;
				case INT_t:
				case LONG_t:
					temp = newreg(get_listitem_sign(src),32); break;
				}
				src = move(temp,src);
				break;
			}
			switch(get_listitem_type(op1))
			{
			case CHAR_t:
				dst = move8(op1,src); break;
			case SHORT_t:
				dst = move16(op1,src); break;
			case INT_t:
			case LONG_t:
				inst_op2(LD, op1->node_type, src->node_type, op1, src); break;
			}
			dst = op1;
		}
		break;
	}

	return (dst);
}
