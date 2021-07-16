/************************************************************************/
/* Code record emit functions                                           */
/************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "zstruct.h"
#include "zutils.h"
#include "zsymtab.h"
#include "ztypesize.h"
#include "zassert.h"
#include "zemit.h"
#include "inst.h"
#include "zinst.h"
#include "register.h"
#include "move.h"
#include "zralloc.h"

#define sign(x)	get_listitem_sign((x))
#define size(x) get_listitem_typesize((x))

#undef _DEBUG
//#define _DEBUG

extern PCR_t g_cr_block;
extern void print_cr_block(PCR_t block);
extern void print_function();
extern void declare_symbol(PIDENT_t psym);
extern int g_line;

void yyerror(char* s);

/************************************************************************/
/* Unary                                                                */
/************************************************************************/
PLIST_t emit_negate(PLIST_t arg1)
{
	if(NODE_TYPE(arg1)==CONSTANT_TYPE)
	{
		DATA_INT(NODE_DATA(arg1)) = -DATA_INT(NODE_DATA(arg1));
	}
	else
	{
		PLIST_t temp;

		g_cr_block = add_cr(g_cr_block, arg1->cr_ptr);

		temp = newreg(sign(arg1), size(arg1));
		temp = instr(LD,temp, arg1);
		inst_op1(NEG, temp->node_type, temp);
		arg1 = temp;

		temp->cr_ptr = g_cr_block = add_cr(temp->cr_ptr,g_cr_block);
	}

#ifdef _DEBUG
	puts("--NEGATE");
	print_cr_block(g_cr_block);
#endif // _DEBUG

	return arg1;
}

PLIST_t emit_lineno(PLIST_t arg1)
{
	PCR_t line;

	line = new_cr(CRLINE,0);
	line->lineno = g_line;

	g_cr_block = add_cr(g_cr_block,line);
	g_cr_block = add_cr(g_cr_block, arg1->cr_ptr);

	arg1->cr_ptr = g_cr_block;

#ifdef _DEBUG
	puts("--LINE");
	print_cr_block(g_cr_block);
#endif // _DEBUG

	return arg1;
}

PLIST_t emit_complement(PLIST_t arg1)
{
	if(NODE_TYPE(arg1)==CONSTANT_TYPE)
	{
		DATA_INT(NODE_DATA(arg1)) = ~DATA_INT(NODE_DATA(arg1));
	}
	else
	{
		PLIST_t temp;
		g_cr_block = add_cr(g_cr_block, arg1->cr_ptr);

		temp = newreg(sign(arg1), size(arg1));
		temp = instr(LD,temp, arg1);
		inst_op1(COM, temp->node_type, temp);
		arg1 = temp;

		temp->cr_ptr = g_cr_block = add_cr(temp->cr_ptr,g_cr_block);
#ifdef _DEBUG
	puts("--COMPLEMENT");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	}

	return arg1;
}

PLIST_t emit_not(PLIST_t arg1)
{
	if(NODE_TYPE(arg1)==CONSTANT_TYPE)
	{
		DATA_INT(NODE_DATA(arg1)) = !DATA_INT(NODE_DATA(arg1));
	}
	else
	{
#ifdef _DEBUG
	puts("--NOT");
#endif // _DEBUG
		arg1 = emit_complement(arg1);
	}
	return arg1;
}


/************************************************************************/
/* Binary                                                               */
/************************************************************************/
PLIST_t emit_multiply(PLIST_t arg1, PLIST_t arg2)
{
	if( (NODE_TYPE(arg1)==CONSTANT_TYPE) && (NODE_TYPE(arg2)==CONSTANT_TYPE) )
	{
		DATA_INT(NODE_DATA(arg1)) = DATA_INT(NODE_DATA(arg1)) * DATA_INT(NODE_DATA(arg2));
		free(arg2);
		arg1->next = NULL;
	}
	else
	{
		g_cr_block = add_cr(g_cr_block, arg1->cr_ptr);
		g_cr_block = add_cr(g_cr_block, arg2->cr_ptr);

		arg1 = instr(MUL,arg1,arg2);
		arg1->cr_ptr = NULL;

		g_cr_block = arg1->cr_ptr = add_cr(arg1->cr_ptr,g_cr_block);
#ifdef _DEBUG
	puts("--MULTIPLY");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	}
	return arg1;
}

PLIST_t emit_divide(PLIST_t arg1, PLIST_t arg2)
{
	if( (NODE_TYPE(arg1)==CONSTANT_TYPE) && (NODE_TYPE(arg2)==CONSTANT_TYPE) )
	{
		DATA_INT(NODE_DATA(arg1)) = DATA_INT(NODE_DATA(arg1)) / DATA_INT(NODE_DATA(arg2));
		free(arg2);
		arg1->next = NULL;
	}
	else
	{
		g_cr_block = add_cr(g_cr_block, arg1->cr_ptr);
		g_cr_block = add_cr(g_cr_block, arg2->cr_ptr);

		arg1 = instr(UDIV,arg1,arg2);
		arg1->cr_ptr = NULL;

		g_cr_block = arg1->cr_ptr = add_cr(arg1->cr_ptr,g_cr_block);
#ifdef _DEBUG
	puts("--DIVIDE");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	}
	return arg1;
}

PLIST_t emit_modulus(PLIST_t arg1, PLIST_t arg2)
{
	if( (NODE_TYPE(arg1)==CONSTANT_TYPE) && (NODE_TYPE(arg2)==CONSTANT_TYPE) )
	{
		DATA_INT(NODE_DATA(arg1)) = DATA_INT(NODE_DATA(arg1)) % DATA_INT(NODE_DATA(arg2));
		free(arg2);
		arg1->next = NULL;
	}
	else
	{
		g_cr_block = add_cr(g_cr_block, arg1->cr_ptr);
		g_cr_block = add_cr(g_cr_block, arg2->cr_ptr);

		arg1 = instr_modulus(arg1,arg2);
		arg1->cr_ptr = NULL;

		g_cr_block = arg1->cr_ptr = add_cr(arg1->cr_ptr,g_cr_block);
#ifdef _DEBUG
	puts("--MODULUS");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	}
	return arg1;
}

PLIST_t emit_sub(PLIST_t arg1, PLIST_t arg2)
{
	if( (NODE_TYPE(arg1)==CONSTANT_TYPE) && (NODE_TYPE(arg2)==CONSTANT_TYPE) )
	{
		DATA_INT(NODE_DATA(arg1)) = DATA_INT(NODE_DATA(arg1)) - DATA_INT(NODE_DATA(arg2));
		free(arg2);
		arg1->next = NULL;
	}
	else
	{
		g_cr_block = add_cr(g_cr_block, arg1->cr_ptr);
		g_cr_block = add_cr(g_cr_block, arg2->cr_ptr);

		arg1 = instr(SUB,arg1,arg2);
		arg1->cr_ptr = NULL;

		g_cr_block = arg1->cr_ptr = add_cr(arg1->cr_ptr,g_cr_block);
#ifdef _DEBUG
	puts("--SUBTRACT");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	}
	return arg1;
}

PLIST_t emit_add(PLIST_t arg1, PLIST_t arg2)
{
	if( (NODE_TYPE(arg1)==CONSTANT_TYPE) && (NODE_TYPE(arg2)==CONSTANT_TYPE) )
	{
		DATA_INT(NODE_DATA(arg1)) = DATA_INT(NODE_DATA(arg1)) + DATA_INT(NODE_DATA(arg2));
		free(arg2);
		arg1->next = NULL;
	}	
	else
	{
		g_cr_block = add_cr(g_cr_block, arg1->cr_ptr);
		g_cr_block = add_cr(g_cr_block, arg2->cr_ptr);

		arg1 = instr(ADD,arg1,arg2);
		arg1->cr_ptr = NULL;

		g_cr_block = arg1->cr_ptr = add_cr(arg1->cr_ptr,g_cr_block);
#ifdef _DEBUG
	puts("--ADD");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	}
	return (arg1);
}


/************************************************************************/
/* Bitwise                                                              */
/************************************************************************/
PLIST_t emit_leftshift(PLIST_t arg1, PLIST_t arg2)
{
	if( (NODE_TYPE(arg1)==CONSTANT_TYPE) && (NODE_TYPE(arg2)==CONSTANT_TYPE) )
	{
		DATA_INT(NODE_DATA(arg1)) = DATA_INT(NODE_DATA(arg1)) << DATA_INT(NODE_DATA(arg2));
	}
	else
	{
		g_cr_block = add_cr(g_cr_block, arg1->cr_ptr);
		g_cr_block = add_cr(g_cr_block, arg2->cr_ptr);

		arg1 = instr(SLL,arg1,arg2);
		arg1->cr_ptr = NULL;

		g_cr_block = arg1->cr_ptr = add_cr(arg1->cr_ptr,g_cr_block);
#ifdef _DEBUG
	puts("--Shift left");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	}
	return arg1;
}

PLIST_t emit_rightshift(PLIST_t arg1, PLIST_t arg2)
{
	if( (NODE_TYPE(arg1)==CONSTANT_TYPE) && (NODE_TYPE(arg2)==CONSTANT_TYPE) )
	{
		DATA_INT(NODE_DATA(arg1)) = DATA_INT(NODE_DATA(arg1)) >> DATA_INT(NODE_DATA(arg2));
	}
	else
	{
		g_cr_block = add_cr(g_cr_block, arg1->cr_ptr);
		g_cr_block = add_cr(g_cr_block, arg2->cr_ptr);

		arg1 = instr(SRL,arg1,arg2);
		arg1->cr_ptr = NULL;

		g_cr_block = arg1->cr_ptr = add_cr(arg1->cr_ptr,g_cr_block);
#ifdef _DEBUG
	puts("--Shift right");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	}
	return arg1;
}

PLIST_t emit_logicaland(PLIST_t arg1, PLIST_t arg2)
{
	if( (NODE_TYPE(arg1)==CONSTANT_TYPE) && (NODE_TYPE(arg2)==CONSTANT_TYPE) )
	{
		DATA_INT(NODE_DATA(arg1)) = (DATA_INT(NODE_DATA(arg1)) & DATA_INT(NODE_DATA(arg2)));
	}
	else
	{
		g_cr_block = add_cr(g_cr_block, arg1->cr_ptr);
		g_cr_block = add_cr(g_cr_block, arg2->cr_ptr);

		arg1 = instr(AND,arg1,arg2);
		arg1->cr_ptr = NULL;

		g_cr_block = arg1->cr_ptr = add_cr(arg1->cr_ptr,g_cr_block);
#ifdef _DEBUG
	puts("--And");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	}
	return arg1;
}

PLIST_t emit_logicalxor(PLIST_t arg1, PLIST_t arg2)
{
	if( (NODE_TYPE(arg1)==CONSTANT_TYPE) && (NODE_TYPE(arg2)==CONSTANT_TYPE) )
	{
		DATA_INT(NODE_DATA(arg1)) = DATA_INT(NODE_DATA(arg1)) ^ DATA_INT(NODE_DATA(arg2));
	}
	else
	{
		g_cr_block = add_cr(g_cr_block, arg1->cr_ptr);
		g_cr_block = add_cr(g_cr_block, arg2->cr_ptr);

		arg1 = instr(XOR,arg1,arg2);
		arg1->cr_ptr = NULL;

		g_cr_block = arg1->cr_ptr = add_cr(arg1->cr_ptr,g_cr_block);
#ifdef _DEBUG
	puts("--Xor");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	}
	return arg1;
}

PLIST_t emit_logicalor(PLIST_t arg1, PLIST_t arg2)
{
	if( (NODE_TYPE(arg1)==CONSTANT_TYPE) && (NODE_TYPE(arg2)==CONSTANT_TYPE) )
	{
		DATA_INT(NODE_DATA(arg1)) = DATA_INT(NODE_DATA(arg1)) | DATA_INT(NODE_DATA(arg2));
	}
	else
	{
		g_cr_block = add_cr(g_cr_block, arg1->cr_ptr);
		g_cr_block = add_cr(g_cr_block, arg2->cr_ptr);

		arg1 = instr(OR,arg1,arg2);
		arg1->cr_ptr = NULL;

		g_cr_block = arg1->cr_ptr = add_cr(arg1->cr_ptr,g_cr_block);
#ifdef _DEBUG
	puts("--Or");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	}
	return arg1;
}


/************************************************************************/
/* Relational                                                           */
/************************************************************************/
PLIST_t emit_lessthan(PLIST_t arg1, PLIST_t arg2)
{
	if( (NODE_TYPE(arg1)==CONSTANT_TYPE) && (NODE_TYPE(arg2)==CONSTANT_TYPE) )
	{
		DATA_INT(NODE_DATA(arg1)) = DATA_INT(NODE_DATA(arg1)) < DATA_INT(NODE_DATA(arg2));
	}
	else
	{
		g_cr_block = add_cr(g_cr_block, arg1->cr_ptr);
		g_cr_block = add_cr(g_cr_block, arg2->cr_ptr);

		arg1 = instr(CP,arg1,arg2);
		if(sign(arg1) || sign(arg2))
			arg1 = instr_ldcc(LT);
		else
			arg1 = instr_ldcc(ULT);
		arg1->cr_ptr = NULL;

		g_cr_block = arg1->cr_ptr = add_cr(arg1->cr_ptr,g_cr_block);
#ifdef _DEBUG
	puts("--LT");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	}
	return arg1;
}

PLIST_t emit_greaterthan(PLIST_t arg1, PLIST_t arg2)
{
	if( (NODE_TYPE(arg1)==CONSTANT_TYPE) && (NODE_TYPE(arg2)==CONSTANT_TYPE) )
	{
		DATA_INT(NODE_DATA(arg1)) = DATA_INT(NODE_DATA(arg1)) > DATA_INT(NODE_DATA(arg2));
	}
	else
	{
		g_cr_block = add_cr(g_cr_block, arg1->cr_ptr);
		g_cr_block = add_cr(g_cr_block, arg2->cr_ptr);

		arg1 = instr(CP,arg1,arg2);
		if(sign(arg1) || sign(arg2))
			arg1 = instr_ldcc(GT);
		else
			arg1 = instr_ldcc(UGT);
		arg1->cr_ptr = NULL;

		g_cr_block = arg1->cr_ptr = add_cr(arg1->cr_ptr,g_cr_block);
#ifdef _DEBUG
	puts("--GT");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	}
	return arg1;
}

PLIST_t emit_lessthanequal(PLIST_t arg1, PLIST_t arg2)
{
	if( (NODE_TYPE(arg1)==CONSTANT_TYPE) && (NODE_TYPE(arg2)==CONSTANT_TYPE) )
	{
		DATA_INT(NODE_DATA(arg1)) = DATA_INT(NODE_DATA(arg1)) <= DATA_INT(NODE_DATA(arg2));
	}
	else
	{
		g_cr_block = add_cr(g_cr_block, arg1->cr_ptr);
		g_cr_block = add_cr(g_cr_block, arg2->cr_ptr);

		arg1 = instr(CP,arg1,arg2);
		if(sign(arg1) || sign(arg2))
			arg1 = instr_ldcc(LE);
		else
			arg1 = instr_ldcc(ULE);
		arg1->cr_ptr = NULL;

		g_cr_block = arg1->cr_ptr = add_cr(arg1->cr_ptr,g_cr_block);
#ifdef _DEBUG
	puts("--LE");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	}
	return arg1;
}

PLIST_t emit_greaterthanequal(PLIST_t arg1, PLIST_t arg2)
{
	if( (NODE_TYPE(arg1)==CONSTANT_TYPE) && (NODE_TYPE(arg2)==CONSTANT_TYPE) )
	{
		DATA_INT(NODE_DATA(arg1)) = DATA_INT(NODE_DATA(arg1)) >= DATA_INT(NODE_DATA(arg2));
	}
	else
	{
		g_cr_block = add_cr(g_cr_block, arg1->cr_ptr);
		g_cr_block = add_cr(g_cr_block, arg2->cr_ptr);

		arg1 = instr(CP,arg1,arg2);
		if(sign(arg1) || sign(arg2))
			arg1 = instr_ldcc(GE);
		else
			arg1 = instr_ldcc(UGE);
		arg1->cr_ptr = NULL;

		g_cr_block = arg1->cr_ptr = add_cr(arg1->cr_ptr,g_cr_block);
#ifdef _DEBUG
	puts("--GE");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	}
	return arg1;
}

PLIST_t emit_equal(PLIST_t arg1, PLIST_t arg2)
{
	if( (NODE_TYPE(arg1)==CONSTANT_TYPE) && (NODE_TYPE(arg2)==CONSTANT_TYPE) )
	{
		DATA_INT(NODE_DATA(arg1)) = (DATA_INT(NODE_DATA(arg1)) == DATA_INT(NODE_DATA(arg2)));
	}
	else
	{
		g_cr_block = add_cr(g_cr_block, arg1->cr_ptr);
		g_cr_block = add_cr(g_cr_block, arg2->cr_ptr);

		arg1 = instr(CP,arg1,arg2);
		arg1 = instr_ldcc(EQ);
		arg1->cr_ptr = NULL;

		g_cr_block = arg1->cr_ptr = add_cr(arg1->cr_ptr,g_cr_block);
#ifdef _DEBUG
	puts("--EQ");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	}
	return arg1;
}

PLIST_t emit_notequal(PLIST_t arg1, PLIST_t arg2)
{
	if( (NODE_TYPE(arg1)==CONSTANT_TYPE) && (NODE_TYPE(arg2)==CONSTANT_TYPE) )
	{
		DATA_INT(NODE_DATA(arg1)) = (DATA_INT(NODE_DATA(arg1)) != DATA_INT(NODE_DATA(arg2)));
	}
	else
	{
		g_cr_block = add_cr(g_cr_block, arg1->cr_ptr);
		g_cr_block = add_cr(g_cr_block, arg2->cr_ptr);

		arg1 = instr(CP,arg1,arg2);
		arg1 = instr_ldcc(NE);
		arg1->cr_ptr = NULL;

		g_cr_block = arg1->cr_ptr = add_cr(arg1->cr_ptr,g_cr_block);
#ifdef _DEBUG
	puts("--NEQ");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	}
	return arg1;
}

PLIST_t emit_reland(PLIST_t arg1, PLIST_t arg2)
{
	if( (NODE_TYPE(arg1)==CONSTANT_TYPE) && (NODE_TYPE(arg2)==CONSTANT_TYPE) )
	{
		DATA_INT(NODE_DATA(arg1)) = (DATA_INT(NODE_DATA(arg1)) && DATA_INT(NODE_DATA(arg2)));
	}
	else
	{
		g_cr_block = add_cr(g_cr_block, arg1->cr_ptr);
		g_cr_block = add_cr(g_cr_block, arg2->cr_ptr);

		arg1 = instr(AND,arg1,arg2);
		arg1->cr_ptr = NULL;

		g_cr_block = arg1->cr_ptr = add_cr(arg1->cr_ptr,g_cr_block);
#ifdef _DEBUG
	puts("--Relational and");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	}
	return arg1;
}

PLIST_t emit_relor(PLIST_t arg1, PLIST_t arg2)
{
	if( (NODE_TYPE(arg1)==CONSTANT_TYPE) && (NODE_TYPE(arg2)==CONSTANT_TYPE) )
	{
		DATA_INT(NODE_DATA(arg1)) = (DATA_INT(NODE_DATA(arg1)) || DATA_INT(NODE_DATA(arg2)));
	}
	else
	{
		g_cr_block = add_cr(g_cr_block, arg1->cr_ptr);
		g_cr_block = add_cr(g_cr_block, arg2->cr_ptr);

		arg1 = instr(OR,arg1,arg2);
		arg1->cr_ptr = NULL;

		g_cr_block = arg1->cr_ptr = add_cr(arg1->cr_ptr,g_cr_block);
#ifdef _DEBUG
	puts("--Relational or");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	}
	return arg1;
}

/************************************************************************/
/* ++                                                                   */
/************************************************************************/
PLIST_t emit_post(PLIST_t op, int add)
{
	PLIST_t reg=0, reg1=0;
	INST_e inst;

	reg  = newreg(sign(op),size(op));
	if(add)
		inst = INCR;
	else
		inst = DECR;

	g_cr_block = add_cr(g_cr_block, op->cr_ptr);
	reg = move(reg,op);
	if(!(inst_op1(inst,op->node_type,op)))
	{
		reg1  = newreg(sign(op),size(op));
		reg1 = move(reg1,op);
		switch(size(reg1))
		{
		case 8:
			inst_op1_b(inst,REGISTER_TYPE,reg1);
			break;
		case 16:
			inst_op1_w(inst,REGISTER_TYPE,reg1);
			break;
		default:
			inst_op1(inst,REGISTER_TYPE,reg1);
		}
		emit_assign(op,0,reg1);
	}

	reg->cr_ptr=NULL;
	g_cr_block = reg->cr_ptr = add_cr(reg->cr_ptr,g_cr_block);

#ifdef _DEBUG
	puts("--Post");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	return (reg);
}

PLIST_t emit_pre(PLIST_t op, int add)
{
	PLIST_t reg=0;
	INST_e inst;

	if(add)
		inst = INCR;
	else
		inst = DECR;

	g_cr_block = add_cr(g_cr_block, op->cr_ptr);
	if(!(inst_op1(inst,op->node_type,op)))
	{
		reg  = newreg(sign(op),size(op));
		reg = move(reg,op);
		inst_op1(inst,REGISTER_TYPE,reg);
		emit_assign(op,0,reg);
		op = reg;
	}

	op->cr_ptr=NULL;
	g_cr_block = op->cr_ptr = add_cr(op->cr_ptr,g_cr_block);

#ifdef _DEBUG
	puts("--Pre");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	return (op);
}

PLIST_t emit_pointeraccess(PLIST_t ident)
{
	PLIST_t pcr=0, paddr=0;

	paddr = emit_addressaccess(ident);
	paddr->node_type = REGIND_TYPE;

#ifdef _DEBUG
	puts("--Pointer");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	return (paddr);
}

PLIST_t emit_addressaccess(PLIST_t ident)
{
	PLIST_t preg=0;
	INST_e inst;

	if(ident->node_type != REGISTER_TYPE)
	{
		g_cr_block = add_cr(g_cr_block,ident->cr_ptr);

		inst = LEA;
		preg = instr(inst,NULL,ident);
		((PREG_t)(preg->node_ptr))->sign = sign(ident);
		((PREG_t)(preg->node_ptr))->size = size(ident);

		preg->cr_ptr = NULL;
		g_cr_block = preg->cr_ptr = add_cr(preg->cr_ptr,g_cr_block);
	}
	else
		preg = ident;

#ifdef _DEBUG
	puts("--Address");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	return (preg);
}

PLIST_t emit_arrayaccess(PLIST_t ident, PLIST_t exp)
{
	PLIST_t pcr=0, preg=0;
	PTYPE_t basetype=0;
	INST_e inst;
	PIDENT_t pident=0;
	int offset=0;

	g_cr_block = add_cr(g_cr_block,ident->cr_ptr);
	g_cr_block = add_cr(g_cr_block,exp->cr_ptr);

	pident = ((PIDENT_t)ident->node_ptr);
	if(pident->ident_type != ARRAY_t)
		inst = LD;
	else
		inst = LEA;

	basetype = pident->pvar_type;
	pcr = emit_multiply(exp,new_node(CONSTANT_TYPE,new_data(INT_t,get_typesize(basetype))));
	if(inst==LEA)
		preg = instr(inst,NULL,ident);
	else
		preg = refer(ident);
	if((NODE_TYPE(pcr) == CONSTANT_TYPE) && (DATA_INT(NODE_DATA(pcr)) < 8191))
	{
		offset = DATA_INT(NODE_DATA(pcr));
		pcr = preg;
		pcr->node_type = REGREL_TYPE;
		((PREG_t)(pcr->node_ptr))->offset = offset;
	}
	else
	{
		pcr = instr(ADD,preg,pcr);
		pcr->node_type = REGIND_TYPE;
	}
	((PREG_t)(pcr->node_ptr))->sign = sign(ident);
	((PREG_t)(pcr->node_ptr))->size = size(ident);

	pcr->cr_ptr = NULL;
	g_cr_block = pcr->cr_ptr = add_cr(pcr->cr_ptr,g_cr_block);

#ifdef _DEBUG
	puts("--Array");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	return (pcr);
}

/************************************************************************/
/* Assignment operator                                                  */
/************************************************************************/
PLIST_t emit_assign(PLIST_t lhs, int op, PLIST_t rhs)
{
	g_cr_block = add_cr(g_cr_block, lhs->cr_ptr);
	g_cr_block = add_cr(g_cr_block, rhs->cr_ptr);

	lhs = move(lhs,rhs);
	lhs->cr_ptr = NULL;

	g_cr_block = lhs->cr_ptr = add_cr(lhs->cr_ptr,g_cr_block);
#ifdef _DEBUG
	puts("--Assignment");
	print_cr_block(g_cr_block);
#endif // _DEBUG

	return lhs;
}

/************************************************************************/
/* Others                                                               */
/************************************************************************/
PCR_t emit_if(PLIST_t exp, PLIST_t val, PCR_t tblk, PCR_t fblk)
{
	PLIST_t arg1=0, arg2=0;
	PCR_t finishlbl=0, falselbl=0;

#ifdef _DEBUG
	printf("\n**emit_if");
#endif // _DEBUG
	if(tblk && tblk->cr_type == CREXPVAL)
	{
		tblk = ((PLIST_t)(tblk->operand[0]))->cr_ptr;
	}
	if(fblk && fblk->cr_type == CREXPVAL)
	{
		fblk = ((PLIST_t)(fblk->operand[0]))->cr_ptr;
	}
	
	if( val == NULL) /* boolean exp */
	{
		arg1 = exp;
		arg2 = new_node(CONSTANT_TYPE, new_data(INT_t,1));
		g_cr_block = add_cr(g_cr_block, arg1->cr_ptr);

		falselbl = new_label();
		arg1 = instr(CPZ,arg1,NULL);
		instr_jpcc(EQ, falselbl);
		g_cr_block = add_cr(g_cr_block,tblk);
		if(fblk)
		{
			finishlbl = new_label();
			instr_jpcc(0,finishlbl);
		}
		g_cr_block = add_cr(g_cr_block, falselbl);
		if(fblk)
		{
			g_cr_block = add_cr(g_cr_block,fblk);
		}
		g_cr_block = add_cr(g_cr_block, finishlbl);
	}
#ifdef _DEBUG
	puts("--IF");
	print_cr_block(g_cr_block);
#endif // _DEBUG

	return g_cr_block;
}

PCR_t emit_switch(PLIST_t val, PCR_t blk)
{
#ifdef _DEBUG
	printf("\n**emit_switch");
#endif // _DEBUG
	return 0;
}

PCR_t emit_jp(PCR_t jmp_label)
{
#ifdef _DEBUG
	printf("\n**emit_jp");
#endif // _DEBUG
	return (get_jp(jmp_label));
}

int emit_function(PCR_t pstmts)
{
	if(!gcolor(pstmts))
		return 0;

	pstmts = g_cr_block;

#ifdef _DEBUG
	print_cr_block(pstmts);
	print_function();
	delete_symhash(1);
#endif // _DEBUG

#ifdef _DEBUG
	printf("\n**emit_function");
	print_cr_block(pstmts);
#endif // _DEBUG
	return 1;
}

void  emit_sym_decl(PLIST_t psymlist)
{
//	print_symbol((PIDENT_t)psymlist->node_ptr);

	while(psymlist)
	{
		declare_symbol((PIDENT_t)psymlist->node_ptr);
		psymlist = psymlist->next;
	}
#ifdef _DEBUG
	printf("\n**emit_sym_decl");
#endif // _DEBUG
	return;
}

PCR_t prefix_label(PCR_t parent, PCR_t label)
{
	g_cr_block = label;
	g_cr_block = add_cr(g_cr_block,parent);
	
#ifdef _DEBUG
	printf("\n**prefix_label");
	print_cr_block(g_cr_block);
#endif // _DEBUG
	return (g_cr_block);
}

PCR_t process_break_continue(PCR_t parent, PCR_t start_label)
{
	PCR_t cr=0, temp=0, end_label=0;
	int endlbl_flg=0;

	end_label = new_label();

	cr = parent;
	while(cr)
	{
		/* continue statement */
		switch(cr->cr_type)
		{
		case CRCONTINUE:
			{
				temp = cr;
				cr = emit_jp(start_label);
				cr->prev = temp->prev;
				cr->next = temp->next;
				if(cr->next)
					cr->next->prev = cr;
				cr->prev->next = cr;
				free(temp);temp=0;
			}
			break;
		case CRBREAK:
			{
				temp = cr;
				cr = emit_jp(end_label);
				cr->prev = temp->prev;
				cr->next = temp->next;
				if(cr->next)
					cr->next->prev = cr;
				cr->prev->next = cr;
				free(temp);temp=0;
				endlbl_flg=1;
			}
			break;
		}
		cr = cr->next;
	}
	if(endlbl_flg)
		parent = add_cr(parent,end_label);
	
#ifdef _DEBUG
	printf("\n**process_break_continue");
	print_cr_block(parent);
#endif // _DEBUG
	return parent;
}

/************************************************************************/
/* Function call                                                        */
/************************************************************************/
static PIDENT_t reverse_list(PIDENT_t parglist)
{
	PIDENT_t pnode=0, phead=0;;

	if(parglist)
	{
		phead = new_ident(parglist->pident_name);
		ident_addstuff(phead,parglist->ident_type,parglist->pvar_type,NULL);

		parglist = parglist->parg_list;
		while(parglist)
		{
			pnode = new_ident(parglist->pident_name);
			ident_addstuff(pnode,parglist->ident_type,parglist->pvar_type,phead);
			phead = pnode;

			parglist = parglist->parg_list;
		}
	}

	return (phead);
}

PLIST_t emit_functioncall(PLIST_t fname, PLIST_t args)
{
	PLIST_t reg=0;
	PLABEL_t flabel=0;
	int stksize=0;
	PLIST_t ret_reg=0;
	PIDENT_t func=0, parg=0;

	func = get_symbol(IDENT_NAME((PIDENT_t)fname->node_ptr));
	if(!func)
		return NULL;

	parg = reverse_list(func->parg_list);
	/* push arguments */
	while(args)
	{
		/* push each argument on stack */
		g_cr_block = add_cr(g_cr_block,args->cr_ptr);

		switch(args->node_type)
		{
		case CONSTANT_TYPE:
		case REGISTER_TYPE:
			{
				switch(IDENT_VARTYPE(parg)->type)
				{
				case CHAR_t:
					inst_op2_b(LD,REGDEC_TYPE,args->node_type,spreg(),args);
					stksize+=8;
					break;
				case SHORT_t:
					inst_op2_w(LD,REGDEC_TYPE,args->node_type,spreg(),args);
					stksize+=16;
					break;
				case INT_t:
				case LONG_t:
					inst_op2(LD,REGDEC_TYPE,args->node_type,spreg(),args);
					stksize+=32;
					break;
				}
			}
			break;
		default:
			{
				reg = newreg(sign(args),size(args));
				reg = move(reg,args);
				//inst_pushpop(PUSH,REGISTER_TYPE,reg);
				switch(IDENT_VARTYPE(parg)->type)
				{
				case CHAR_t:
					inst_op2_b(LD,REGDEC_TYPE,REGISTER_TYPE,spreg(),reg);
					stksize+=8;
					break;
				case SHORT_t:
					inst_op2_w(LD,REGDEC_TYPE,REGISTER_TYPE,spreg(),reg);
					stksize+=16;
					break;
				case INT_t:
				case LONG_t:
					inst_op2(LD,REGDEC_TYPE,REGISTER_TYPE,spreg(),reg);
					stksize+=32;
					break;
				}
			}
			break;
		}

		args = args->next;
		parg = parg->parg_list;
	}

	if(stksize && parg)
	{
		yyerror("**Too few arguments");
		exit(1);
	}

	/* function call */
	flabel = (PLABEL_t)calloc(1,sizeof(LABEL_t));
	flabel->label_flag = 1;
	flabel->name = (char*)calloc(1,strlen(IDENT_NAME((PIDENT_t)fname->node_ptr))+1);
	sprintf(flabel->name,"_%s", IDENT_NAME((PIDENT_t)fname->node_ptr));
	inst_call(flabel);

	/* deallocate stack */
	if(stksize)
		emit_add(spreg(),new_node(CONSTANT_TYPE,new_data(INT_t,stksize/8)));

	
	/* return value */
	switch(IDENT_VARTYPE(func)->type)
	{
	case VOID_t:
		ret_reg = fname;
		break;
	default:
		ret_reg = newreg((char)(IDENT_VARTYPE(func)->issigned), IDENT_VARTYPE(func)->size);
		inst_op2(LD,REGISTER_TYPE,REGISTER_TYPE,ret_reg,returnreg());
		break;
	}

	g_cr_block = ret_reg->cr_ptr = add_cr(ret_reg->cr_ptr,g_cr_block);

#ifdef _DEBUG
	printf("\n**functioncall");
	print_cr_block(g_cr_block);
#endif // _DEBUG

	return (ret_reg);
}
