/************************************************************************/
/* Utility functions                                                    */
/************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "zstruct.h"
#include "zutils.h"
#include "ztypesize.h"
#include "zassert.h"
#include "zsymtab.h"

#undef _DEBUG

extern PCR_t g_cr_block;
extern void print_cr_block(PCR_t block);
extern PIDENT_t g_current_function;
extern void yyerror(char* s);

long get_intval(CONST_TYPE type, const char *data, unsigned char *sign)
{
	long value = 0;
	
	switch(type)
	{
	case HEX:
		sscanf(data+2,"%x",&value);
		break;
	case OCT:
		sscanf(data+1,"%o",&value);
		break;
	case DEC:
		sscanf(data,"%d",&value);
		break;
	case CHR:
		if(data[1]=='\'') 
			value = 0; 
		else 
			value = data[1];
		break;
	}

	/* look for U/L suffix here ... */
	*sign = 1; /* signed default */

	return value;
}

double get_fltval(const char *data)
{
	double value = 0;

	sscanf(data,"%f",&value);

	return value;
}

/************************************************************************/
/* Type size                                                            */
/************************************************************************/
int typesize(PLIST_t node)
{
	if(node->node_type == CONSTANT_TYPE)
	{
		switch(DATA_TYPE((PDATA_t)node->node_ptr))
		{
		case CHAR_t: return CHAR_SIZE;
		case SHORT_t: return SHORT_SIZE;
		case INT_t: return INT_SIZE;
		case LONG_t: return LONG_SIZE;
		case FLOAT_t: return FLOAT_SIZE;
		case DOUBLE_t: return DOUBLE_SIZE;
		}
	}
	else if(node->node_type == IDENTIFIER_TYPE)
	{
		return get_typesize(IDENT_VARTYPE((PIDENT_t)node->node_ptr));
	}

	return 0;
}

int get_structsize(PTYPE_t ptype)
{
	int size = 0;

	if(ptype->u.ptag)
		size += get_typesize(ptype->u.ptag->pvar_type);
/*	else 
		ERROR(ERR_CODE_1); /* struct/union declaration not found */


	return size;
}

int get_unionsize(PTYPE_t ptype)
{
	int maxsize = 0, size = 0;

	if(ptype->u.ptag)
	{
		size = get_typesize(ptype->u.ptag->pvar_type);
		maxsize = (maxsize<size)?size:maxsize;
	}
/*	else 
		ERROR(ERR_CODE_1); /* struct/union declaration not found */

	return maxsize;
}

int get_typesize(PTYPE_t ptype)
{
	switch(ptype->type)
	{
	case CHAR_t: return CHAR_SIZE;
	case SHORT_t: return SHORT_SIZE;
	case INT_t: return INT_SIZE;
	case LONG_t: return LONG_SIZE;
	case FLOAT_t: return FLOAT_SIZE;
	case DOUBLE_t: return DOUBLE_SIZE;
	case POINTER_t: return POINTER_SIZE;
	case VARIABLE_t: return get_typesize(ptype->u.psubtype);
	case STRUCT_t: return get_structsize(ptype);
	case UNION_t: return get_unionsize(ptype);
	case TYPEDEF_t: return get_typesize(ptype->u.ptag->pvar_type);
	}
	return 0;
}

int get_integraltypesize(TYPE_e type)
{
	TYPE_t temp;
	temp.type = type;
	return get_typesize(&temp);
}

/************************************************************************/
/* TYPE_t                                                               */
/************************************************************************/
PTYPE_t new_type(TYPE_e type, TYPE_e issigned, TYPE_e qualifier, int offset, TYPE_e specifier)
{
	PTYPE_t pnewtype = NULL;

	pnewtype = (PTYPE_t)calloc(1,sizeof(TYPE_t));

	ZASSERT(pnewtype);

	pnewtype->type = type;
	pnewtype->issigned = issigned;
	pnewtype->qualifier = qualifier;
	pnewtype->specifier = specifier;
	pnewtype->offset = offset;
	pnewtype->u.psubtype = NULL;
	pnewtype->u.ptag = NULL;

	pnewtype->size = get_typesize(pnewtype);

	return (pnewtype);
}

void add_subtype(PTYPE_t ptype, PTYPE_t psubtype)
{
	if(ptype->u.psubtype == NULL)
	{
		ptype->u.psubtype = psubtype;
		return;
	}
	else
		add_subtype(ptype->u.psubtype,psubtype);
}

void delete_type(PTYPE_t ptype)
{
	if(ptype->u.psubtype == NULL)
	{
		free(ptype);
	}
	else
		delete_type(ptype->u.psubtype);
}

/************************************************************************/
/* DATA_t                                                               */
/************************************************************************/
PDATA_t new_data(TYPE_e type, ...)
{
	PDATA_t pnewdata = NULL;
	va_list va;

	va_start(va,type);
	pnewdata = (PDATA_t)calloc(1,sizeof(DATA_t));
	ZASSERT(pnewdata);

	switch(type)
	{
	case INT_t:
		pnewdata->pdata_type = new_type(INT_t,SIGNED_t,CONST_t,0,0);
		pnewdata->val.int_val = va_arg(va,int);
		break;
	case FLOAT_t:
		pnewdata->pdata_type = new_type(FLOAT_t,SIGNED_t,CONST_t,0,0);
		pnewdata->val.flt_val = va_arg(va,float);
		break;
	case STRING_t:
		pnewdata->pdata_type = new_type(STRING_t,0,CONST_t,0,0);
		pnewdata->val.pstring = va_arg(va,char*);
		pnewdata->pdata_type->size = strlen(pnewdata->val.pstring);
		break;
	}

	va_end(va);
	return (pnewdata);
}

void delete_data(PDATA_t pdata)
{
	if(pdata->pdata_type->type == STRING_t)
		free(pdata->val.pstring);

	delete_type(pdata->pdata_type);
	free(pdata);
}

/************************************************************************/
/* IDENT_t                                                              */
/************************************************************************/
PIDENT_t new_ident(const char *pident_name)
{
	PIDENT_t pnewident = NULL;

	pnewident = (PIDENT_t)calloc(1,sizeof(IDENT_t));
	ZASSERT(pnewident);

	pnewident->pident_name = (char*)strdup(pident_name);
	pnewident->pvar_type = NULL;
	pnewident->parg_list = NULL;
	return (pnewident);
}

void delete_ident(PIDENT_t pident)
{
	if(pident->pvar_type)
		delete_type(pident->pvar_type);
	if(pident->parg_list)
		delete_ident(pident->parg_list);
	free(pident);
}

void ident_addstuff(PIDENT_t pident, TYPE_e ident_type, PTYPE_t pvar_type, PIDENT_t parg_list)
{
	pident->ident_type = ident_type;
	pident->pvar_type = pvar_type;
	pident->parg_list = parg_list;
}

void add_argument(PIDENT_t pident, PIDENT_t parg)
{
	if(pident->parg_list == NULL)
	{
		pident->parg_list = parg;
		return;
	}
	else
		add_argument(pident->parg_list,parg);
}

/************************************************************************/
/* LIST_t                                                               */
/************************************************************************/
PLIST_t new_node(NTYPE_e node_type, void* node_ptr)
{
	PLIST_t newnode;

	newnode = (PLIST_t)calloc(1,sizeof(LIST_t));
	ZASSERT(newnode);

	newnode->node_type = node_type;
	newnode->node_ptr = node_ptr;
	newnode->next = NULL;

	return (newnode);
}

PLIST_t new_node_cr(NTYPE_e node_type, void* node_ptr, PCR_t pcr)
{
	PLIST_t newnode;

	newnode = (PLIST_t)calloc(1,sizeof(LIST_t));
	ZASSERT(newnode);

	newnode->node_type = node_type;
	newnode->node_ptr = node_ptr;
	newnode->cr_ptr = pcr;
	newnode->next = NULL;

	return (newnode);
}

void add_node(PLIST_t parent, PLIST_t next)
{
	if(parent->next == NULL)
		parent->next = next;
	else
		add_node(parent->next,next);
}

/************************************************************************/
/* CR_t                                                                 */
/************************************************************************/
PCR_t new_cr(CRTYPE_e cr_type, PINST_t pinst)
{
	PCR_t pnew = (PCR_t)calloc(1,sizeof(CR_t));

	pnew->cr_type = cr_type;
	pnew->pinst = pinst;

	return (pnew);
}

void add_operand(PCR_t pcr, int op_num, PLIST_t pop)
{
	pcr->operand[op_num] = pop;
}

PCR_t add_cr(PCR_t parent, PCR_t child)
{
/*
	if( parent && child &&
		(parent->cr_type==CRLINE) && (child->cr_type==CRLINE) 
		&& (parent->lineno==child->lineno))
		return child;
*/

	if(parent && parent->cr_type == CREXPVAL)
	{
		parent = ((PLIST_t)(parent->operand[0]))->cr_ptr;
	}
	if(child && child->cr_type == CREXPVAL)
	{
		child = ((PLIST_t)(child->operand[0]))->cr_ptr;
	}
	if(parent)
	{
		if(parent->next == NULL)
		{
			parent->next = child;
			if(child)
				child->prev = parent;
		}
		else
		{
			add_cr(parent->next,child);
		}
		return parent;
	}
	else
		return child;
}

/************************************************************************/
/* Others                                                               */
/************************************************************************/
int update_parameter_offsets(PIDENT_t parglist)
{
	PIDENT_t ptemp = parglist;
	int stackpos=0;

	while(ptemp)
	{
		ptemp->stackpos = stackpos;
		stackpos += get_typesize(IDENT_VARTYPE(ptemp));
		ptemp = ptemp->parg_list;
	}
	return stackpos;
}

PIDENT_t getparam(PIDENT_t pfunc, char* param)
{
	PIDENT_t plist=0;

	if(pfunc)
	{
		plist = IDENT_ARGLST(pfunc);
		while(plist)
		{
			if(!strcmp(plist->pident_name, param))
				return plist;
			plist = plist->parg_list;
		}
	}

	return NULL;
}

PLIST_t newaddress(PIDENT_t ident, int disp)
{
	PLIST_t pnode=0;
	PIDENT_t ptest=0;

	pnode = (PLIST_t)calloc(1,sizeof(LIST_t));

	ptest = get_symbol(ident->pident_name);

	if(ptest)
	{  /* Either global or local */
		if(ident->scope == 0) /* global variable */
		{
			PLABEL_t pnew=0;
			
			pnew = (PLABEL_t)calloc(1,sizeof(LABEL_t));
			pnew->label_flag = 0;
			pnew->name = (char*)calloc(1,strlen(ident->pident_name)+2);
			sprintf(pnew->name,"_%s",ident->pident_name);
			pnew->offset = disp;
			pnew->sign = IDENT_VARTYPE(ident)->issigned;
			pnew->size = get_typesize(IDENT_VARTYPE(ident));

			pnode->node_type = ADDRESS_TYPE;
			pnode->node_ptr = pnew;
		}
		else /* local variable */
		{
			PREG_t preg=0;

			preg = (PREG_t)calloc(1,sizeof(REG_t));

			preg->pseudo_flag = 0;
			strcpy(preg->u.name,"FP");
			preg->offset = -ident->stackpos;
			preg->sign = IDENT_VARTYPE(ident)->issigned;
			preg->size = get_typesize(IDENT_VARTYPE(ident));

			pnode->node_type = FPREL_TYPE;
			pnode->node_ptr = preg;
		}
	}
	else
	{ /* either parameter or undeclared variable */
		PIDENT_t param=0;

		param = getparam(g_current_function, ident->pident_name);
		if(param)
		{
			PREG_t preg=0;

			preg = (PREG_t)calloc(1,sizeof(REG_t));

			preg->pseudo_flag = 0;
			strcpy(preg->u.name,"FP");
			preg->offset = param->stackpos + FPSIZE + PCSIZE;
			preg->sign = IDENT_VARTYPE(param)->issigned;
			preg->size = get_typesize(IDENT_VARTYPE(param));

			pnode->node_type = FPREL_TYPE;
			pnode->node_ptr = preg;
		}
		else
		{
			yyerror("**Undeclared identifier");
		}
	}
	return (pnode);
}

TYPE_e get_listitem_type(PLIST_t item)
{
	int size;

	if(item->node_type == CONSTANT_TYPE)
		return (DATA_TYPE((PDATA_t)item->node_ptr));
	else if(item->node_type == IDENTIFIER_TYPE)
		return (IDENT_VARTYPE((PIDENT_t)item->node_ptr)->type);

	switch(item->node_type)
	{
	case ADDRESS_TYPE:
		size = ((PLABEL_t)item->node_ptr)->size;
		break;
	case REGREL_TYPE:
	case FPREL_TYPE:
	case REGIND_TYPE:
	case REGDEC_TYPE:
	case REGINC_TYPE:
		size = ((PREG_t)item->node_ptr)->size;
		break;
	}

	switch(size)
	{
	case CHAR_SIZE:
		return CHAR_t;
	case SHORT_SIZE:
		return SHORT_t;
	default:
		return INT_t;
	}

	return 0;
}

int get_listitem_typesize(PLIST_t item)
{
	int size=0;

	if(item->node_type == CONSTANT_TYPE)
		return get_typesize(((PDATA_t)item->node_ptr)->pdata_type);
	else if(item->node_type == IDENTIFIER_TYPE)
		return get_typesize(IDENT_VARTYPE((PIDENT_t)item->node_ptr));

	switch(item->node_type)
	{
	case ADDRESS_TYPE:
		size = ((PLABEL_t)item->node_ptr)->size;
	case REGREL_TYPE:
	case FPREL_TYPE:
	case REGIND_TYPE:
	case REGDEC_TYPE:
	case REGINC_TYPE:
		size = ((PREG_t)item->node_ptr)->size;
	}

	return size;
}

char get_listitem_sign(PLIST_t item)
{
	if(item->node_type == CONSTANT_TYPE)
		return (DATA_SIGNED((PDATA_t)item->node_ptr));
	else if(item->node_type == IDENTIFIER_TYPE)
		return (IDENT_VARTYPE((PIDENT_t)item->node_ptr)->issigned);
	switch(item->node_type)
	{
	case ADDRESS_TYPE:
		return ((PLABEL_t)item->node_ptr)->sign;
	case REGREL_TYPE:
	case FPREL_TYPE:
	case REGIND_TYPE:
	case REGDEC_TYPE:
	case REGINC_TYPE:
		return((PREG_t)item->node_ptr)->sign;
	}

	return 0;
}

TYPE_e get_basetype(PTYPE_t ptype)
{
	PTYPE_t subtype=0;

	if(ptype->type == POINTER_t)
	{
		subtype = ptype->u.psubtype;
		if(subtype)
		{
			return get_basetype(subtype);
		}
	}

	return ptype->type;
}

PCR_t new_label()
{
	static int labelcounter=0;
	PLABEL_t pnew=0;
	PLIST_t pnode=0;
	PCR_t pcr=0;
	
	pnode = (PLIST_t)calloc(1,sizeof(LIST_t));
	pnew = (PLABEL_t)calloc(1,sizeof(LABEL_t));
	pnew->label_flag = 1;
	pnew->name = (char*)calloc(1,10);
	sprintf(pnew->name,"__L%d",labelcounter++);

	pnode->node_type = ADDRESS_TYPE;
	pnode->node_ptr = pnew;

	pcr = new_cr(CRLABEL,0);
	add_operand(pcr,0,pnode);

#ifdef _DEBUG
	printf("\n**new_label - %s", pnew->name);
#endif // _DEBUG
	return pcr;
}

PCR_t new_func_label(char *name)
{
	PLABEL_t pnew=0;
	PLIST_t pnode=0;
	PCR_t pcr=0;
	
	pnode = (PLIST_t)calloc(1,sizeof(LIST_t));
	pnew = (PLABEL_t)calloc(1,sizeof(LABEL_t));
	pnew->label_flag = 1;
	pnew->name = (char*)calloc(1,strlen(name)+2);
	sprintf(pnew->name,"_%s",name);

	pnode->node_type = ADDRESS_TYPE;
	pnode->node_ptr = pnew;

	pcr = new_cr(CRLABEL,0);
	add_operand(pcr,0,pnode);

#ifdef _DEBUG
	printf("\n**new_label - %s", pnew->name);
#endif // _DEBUG
	return pcr;
}

PCR_t get_exp_cr(PLIST_t exp)
{
	PCR_t pcrexp=0;

	pcrexp = new_cr(CREXPVAL, 0);
	add_operand(pcrexp,0/*operand number*/,exp);

#ifdef _DEBUG
	printf("\n**get_exp_cr");
#endif // _DEBUG
	return (pcrexp);
}

PCR_t return_val(PLIST_t exp)
{
#ifdef _DEBUG
	printf("\n**return_val");
#endif // _DEBUG
	return 0;
}

