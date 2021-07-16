/************************************************************************/
/* Structure declarations                                               */
/************************************************************************/
#ifndef _ZSTRUCT_H
#define _ZSTRUCT_H

#define MAX_OP 4

/* Typedefs */
typedef struct _token_t			TOKEN_t, *PTOKEN_t;
typedef struct _data_t			DATA_t, *PDATA_t;
typedef struct _type_t			TYPE_t, *PTYPE_t;
typedef enum _type_e			TYPE_e;
typedef struct _ident_t			IDENT_t, *PIDENT_t;
typedef struct _list_t			LIST_t, *PLIST_t;
typedef enum _ntype_e			NTYPE_e;
typedef enum _crtype_e			CRTYPE_e;
typedef struct _inst_t			INST_t, *PINST_t;
typedef struct _cr_t			CR_t, *PCR_t;
typedef enum _insttype_e		INSTTYPE_e;
typedef enum _dir_e				DIR_e;
typedef enum _inst_e			INST_e;
typedef struct _reg_t			REG_t, *PREG_t;
typedef struct _label_t			LABEL_t, *PLABEL_t;

/************************************************************************/
/* Structures                                                           */
/************************************************************************/
/* Token */
struct _token_t
{
	int token;
	char *data;
};

/* Type specifiers */
enum _type_e { VOID_t=1,CHAR_t,SHORT_t,INT_t,LONG_t,FLOAT_t,DOUBLE_t,SIGNED_t,UNSIGNED_t,POINTER_t,
			   STRING_t,EXTERN_t,STATIC_t,CONST_t,AUTO_t,GLOBAL_t,VARIABLE_t,FUNCTION_t,MEMBER_t,
			   STRUCT_t,UNION_t,TAG_t,TYPEDEF_t,VOLATILE_t,ARRAY_t,PARAMETER_t };
struct _type_t
{
	TYPE_e type;      /* base type */
	TYPE_e issigned;  /* signed/unsigned */
	TYPE_e qualifier; /* base qualifier */
	TYPE_e specifier; /* base specifier */
	int    size;	  /* size in bytes */
	int    offset;    /* offset for local var/ struct members */
	union {
		PTYPE_t psubtype;  /* sub type */
		PIDENT_t ptag;    /* struct/union tag */
	}u;
};

/* Constant data or string */
#define DATA_TYPE(x)			((x)->pdata_type->type)
#define DATA_SIGNED(x)			((x)->pdata_type->issigned)
#define DATA_QUALIFIER(x)		((x)->pdata_type->qualifier)
#define DATA_SIZE(x)			((x)->pdata_type->size)
#define DATA_OFFSET(x)			((x)->pdata_type->offset)
#define DATA_INT(x)				((x)->val.int_val)
#define DATA_FLT(x)				((x)->val.flt_val)
#define DATA_STR(x)				((x)->val.pstring)
struct _data_t
{
	PTYPE_t pdata_type;
	union {
		int int_val;
		double flt_val;
		char *pstring;
	}val;
};

/* Identifiers */
#define IDENT_NAME(x)			((x)->pident_name)
#define IDENT_TYPE(x)			((x)->ident_type)
#define IDENT_VARTYPE(x)		((x)->pvar_type)
#define IDENT_ARGLST(x)			((x)->parg_list)
struct _ident_t
{
	char   *pident_name;  /* identifier name */
	TYPE_e ident_type;   /* variable or function */
	PTYPE_t pvar_type;    /* return type in case of function */
	PIDENT_t  parg_list;  /* list of arguments in case of function */
	PLIST_t	pinitlist;

	int scope;			/* variable scope */
	long stackpos;		/* in case of local symbol */
};


/* Data list */
#define NODE_TYPE(x)  (x->node_type)
#define NODE_DATA(x)  ((PDATA_t)(x->node_ptr))
#define NODE_IDENT(x) ((PIDENT_t)(x->node_ptr))
enum _ntype_e { CONSTANT_TYPE=1, IDENTIFIER_TYPE, STRING_TYPE, REGISTER_TYPE, 
				ADDRESS_TYPE, CR_TYPE, SYMBOL_TYPE, REGIND_TYPE, REGREL_TYPE,
				SPREL_TYPE, FPREL_TYPE, REGINC_TYPE, REGDEC_TYPE };
struct _list_t
{
	NTYPE_e node_type;
	void *node_ptr;

	PCR_t cr_ptr;

	PLIST_t next;
};

/* Code record */
#define CR_TYPE(x) (x->cr_type)
enum _crtype_e { CRLABEL, CRINST, CREXPVAL, CRCASEVAL, CRCONTINUE, 
				 CRBREAK, CRRETURN, CRLINE };
enum _dir_e { B=1,W,SB,SW,UB,UW, 
			  LT,ULT,GT,UGT,LE,ULE,GE,UGE,EQ,NE };
struct _cr_t
{
	CRTYPE_e cr_type;
	int index;

	PINST_t pinst;	 /* instruction */
	DIR_e  directive; /* for instruction type cr */

	PLIST_t operand[MAX_OP]; /* operand values */

	int lineno;

	PCR_t prev;
	PCR_t next;
};

/* Instruction tab */
enum _insttype_e { OTHER, LOAD, CTRL, COMPARE  };
enum _inst_e { 
	LD=1, ADD, ADC, SUB, SBC, CP, CPC, NEG, COM, MUL, SMUL, UDIV, SDIV,
	SLL, SRL, SRA, AND, XOR, OR, LDCC, JP, CPZ, INCR, DECR, LEA, PUSH,
	POP, CALL, PUSHM, POPM, LINK, UNLINK, RET };
struct _inst_t
{
	INSTTYPE_e inst_type;
	INST_e inst;
	int num_op; /* number of operands */
	NTYPE_e op_type[MAX_OP]; /* operand types */
};

/* Registers */
struct _reg_t
{
	char pseudo_flag;

	union
	{
		int number; /* register number in case of pseudo register */
		char name[10]; /* name of the register in case of pseudo register */
	}u;

	int offset; /* in case of register relative addressing mode */
	char sign; /* operand sign */
	int size; /* operand size */
};

/* Address/Label */
struct _label_t
{
	char label_flag;
	char *name;
	int offset;
	char sign;
	int size;
};

#endif
