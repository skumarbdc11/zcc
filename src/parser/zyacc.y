%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YYDEBUG 1

#include "zsymtab.h"
#include "zutils.h"
#include "zemit.h"
#include "zpreproc.h"

/* identifier scope */
extern int g_scope_level;
extern PIDENT_t g_current_function;
extern PCR_t g_cr_block;
extern int max_pseudo_num;
extern FILELIST_t g_filelist[MAX_INCLUDES];
extern int inc_level;
extern int file_flag;
extern int g_errcount;


extern char yytext[];
extern int g_column;
extern int g_line;

extern int yylex();
void yyerror(char* s);
extern void print_cr_block(PCR_t block);
extern void print_function();

%}

%union
{
	TOKEN_t		token;
	PTYPE_t		ptype;
	PDATA_t		pdata;
	PIDENT_t	pident;
	PLIST_t		plist;
	PCR_t		pcr;
}

%token<token> IDENTIFIER
%token<pdata> HEX_CONSTANT OCT_CONSTANT DEC_CONSTANT FLT_CONSTANT STRING_LITERAL
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP ASSIGN_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME
%token SIZEOF

%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type<token> struct_or_union storage_class_specifier type_qualifier assignment_operator
%type<ptype> type_specifier specifier_qualifier_list declaration_specifiers pointer
%type<ptype> abstract_declarator

%type<pident> direct_declarator declarator struct_declarator struct_declarator_list
%type<pident> struct_declaration struct_declaration_list struct_or_union_specifier
%type<pident> init_declarator init_declarator_list parameter_declaration parameter_list parameter_type_list

%type<plist> primary_expression postfix_expression unary_expression cast_expression
%type<plist> multiplicative_expression additive_expression shift_expression initializer initializer_list
%type<plist> relational_expression equality_expression and_expression exclusive_or_expression
%type<plist> inclusive_or_expression logical_and_expression logical_or_expression conditional_expression
%type<plist> assignment_expression expression constant_expression declaration declaration_list
%type<plist> argument_expression_list

%type<pcr> statement labeled_statement compound_statement expression_statement selection_statement
%type<pcr> iteration_statement jump_statement statement_list function_definition

%start translation_unit
%%

primary_expression
	: IDENTIFIER  
		{
			PIDENT_t psym;

			psym = get_symbol($1.data);
			if(!psym)
			{
				psym = getparam(g_current_function, $1.data);
				if(!psym)
					yyerror("undeclared identifier");
			}
			
			$$ = new_node(IDENTIFIER_TYPE, psym);
		}
	| HEX_CONSTANT 
		{
			$$ = new_node(CONSTANT_TYPE, $1);
		}
	| OCT_CONSTANT
		{
			$$ = new_node(CONSTANT_TYPE, $1);
		}
	| DEC_CONSTANT
		{
			$$ = new_node(CONSTANT_TYPE, $1);
		}
	| FLT_CONSTANT
		{
			$$ = new_node(CONSTANT_TYPE, $1);
		}
	| STRING_LITERAL
		{
			$$ = new_node(STRING_TYPE, $1);
		}
	| '(' expression ')' { $$ = $2; }
	;

postfix_expression
	: primary_expression
		{
			$$ = $1;
		}
	| postfix_expression '[' expression ']'
		{
			$$ = emit_arrayaccess($1,$3);
			g_cr_block = 0;
		}
	| postfix_expression '(' ')'
		{
			$$ = emit_functioncall($1,0);
			g_cr_block = 0;
		}
	| postfix_expression '(' argument_expression_list ')'
		{
			$$ = emit_functioncall($1,$3);
			g_cr_block = 0;
		}
	| postfix_expression '.' IDENTIFIER
	| postfix_expression PTR_OP IDENTIFIER
	| postfix_expression INC_OP
		{
			$$ = emit_post($1,1);
			g_cr_block = 0;
		}
	| postfix_expression DEC_OP
		{
			$$ = emit_post($1,0);
			g_cr_block = 0;
		}
	;

argument_expression_list
	: assignment_expression { $$ = $1; }
	| argument_expression_list ',' assignment_expression
		{
			add_node($3,$1);
			$$ = $3;
		}
	;

unary_expression
	: postfix_expression
		{
			$$ = $1;
		}
	| INC_OP unary_expression
		{
			$$ = emit_pre($2,1);
			g_cr_block = 0;
		}
	| DEC_OP unary_expression
		{
			$$ = emit_pre($2,0);
			g_cr_block = 0;
		}
	| '-' cast_expression  {$$ = emit_negate($2); g_cr_block = 0;}
/*	| unary_operator cast_expression */
	| '&' cast_expression { $$ = emit_addressaccess($2); g_cr_block = 0; }
	| '*' cast_expression { $$ = emit_pointeraccess($2); g_cr_block = 0; }
	| '~' cast_expression { $$ = emit_complement($2); g_cr_block = 0; }
	| '!' cast_expression { $$ = emit_not($2); g_cr_block =0; }
	| SIZEOF unary_expression
		{
			PDATA_t data;
			data = new_data(INT_t, typesize($2) );
			$$ = new_node(CONSTANT_TYPE, data);
		}
	| SIZEOF '(' CHAR ')' { $$ = new_node(CONSTANT_TYPE, new_data(INT_t, 1)); }
	| SIZEOF '(' SHORT ')' { $$ = new_node(CONSTANT_TYPE, new_data(INT_t, 2)); }
	| SIZEOF '(' INT ')' { $$ = new_node(CONSTANT_TYPE, new_data(INT_t, 4)); }
	| SIZEOF '(' LONG ')' { $$ = new_node(CONSTANT_TYPE, new_data(INT_t, 4)); }
	| SIZEOF '(' FLOAT ')' { $$ = new_node(CONSTANT_TYPE, new_data(INT_t, 4)); }
	;

/*unary_operator
	: '&'
	| '*'
	| '+'
	| '-'
	| '~'
	| '!'
	;
*/
cast_expression
	: unary_expression
		{
			$$ = $1;
		}
/*	| '(' type_name ')' cast_expression */
	;

multiplicative_expression
	: cast_expression { $$ = $1; }
	| multiplicative_expression '*' cast_expression { $$ = emit_multiply($1, $3); g_cr_block=0;}
	| multiplicative_expression '/' cast_expression { $$ = emit_divide($1, $3); g_cr_block=0;}
	| multiplicative_expression '%' cast_expression { $$ = emit_modulus($1, $3); g_cr_block=0;}
	;

additive_expression
	: multiplicative_expression { $$ = $1; }
	| additive_expression '+' multiplicative_expression { $$ = emit_add($1, $3); g_cr_block=0;}
	| additive_expression '-' multiplicative_expression { $$ = emit_sub($1, $3); g_cr_block=0;}
	;

shift_expression
	: additive_expression { $$ = $1; }
	| shift_expression LEFT_OP additive_expression { $$ = emit_leftshift($1, $3); g_cr_block=0; }
	| shift_expression RIGHT_OP additive_expression { $$ = emit_rightshift($1, $3); g_cr_block=0; }
	;

relational_expression
	: shift_expression { $$ = $1; }
	| relational_expression '<' shift_expression { $$ = emit_lessthan($1, $3); g_cr_block=0; }
	| relational_expression '>' shift_expression { $$ = emit_greaterthan($1, $3); g_cr_block=0; }
	| relational_expression LE_OP shift_expression { $$ = emit_lessthanequal($1, $3); g_cr_block=0; }
	| relational_expression GE_OP shift_expression { $$ = emit_greaterthanequal($1, $3); g_cr_block=0; }
	;

equality_expression
	: relational_expression { $$ = $1; }
	| equality_expression EQ_OP relational_expression { $$ = emit_equal($1, $3); g_cr_block=0; }
	| equality_expression NE_OP relational_expression { $$ = emit_notequal($1, $3); g_cr_block=0; }
	;

and_expression
	: equality_expression { $$ = $1; }
	| and_expression '&' equality_expression { $$ = emit_logicaland($1, $3); g_cr_block=0; }
	;

exclusive_or_expression
	: and_expression  { $$ = $1; }
	| exclusive_or_expression '^' and_expression { $$ = emit_logicalxor($1, $3); g_cr_block=0; }
	;

inclusive_or_expression
	: exclusive_or_expression { $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression { $$ = emit_logicalor($1, $3); g_cr_block=0; }
	;

logical_and_expression
	: inclusive_or_expression { $$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression { $$ = emit_reland($1, $3); g_cr_block=0; }
	;

logical_or_expression
	: logical_and_expression { $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression { $$ = emit_relor($1, $3); g_cr_block=0; }
	;

conditional_expression
	: logical_or_expression { $$ = $1; }
/*	| logical_or_expression '?' expression ':' conditional_expression */
	;

assignment_expression
	: conditional_expression { $$ = $1; }
	| unary_expression assignment_operator assignment_expression
		{
			$$ = emit_assign($1, $2.token, $3);
			g_cr_block=0;
		}
	;

assignment_operator
	: ASSIGN_OP {$$.token = ASSIGN_OP;}
	| MUL_ASSIGN {$$.token = MUL_ASSIGN;}
	| DIV_ASSIGN {$$.token = DIV_ASSIGN;}
	| MOD_ASSIGN {$$.token = MOD_ASSIGN;}
	| ADD_ASSIGN {$$.token = ADD_ASSIGN;}
	| SUB_ASSIGN {$$.token = SUB_ASSIGN;}
	| LEFT_ASSIGN {$$.token = LEFT_ASSIGN;}
	| RIGHT_ASSIGN {$$.token = RIGHT_ASSIGN;}
	| AND_ASSIGN {$$.token = AND_ASSIGN;}
	| XOR_ASSIGN {$$.token = XOR_ASSIGN;}
	| OR_ASSIGN {$$.token = OR_ASSIGN;}
	;

expression
	: assignment_expression 
		{
			$$ = emit_lineno($1);  g_cr_block=0;
		}
	| expression ',' assignment_expression 
		{ 
			add_node($1,$3);
			$$ = $1; 
		}
	;

constant_expression
	: conditional_expression { $$ = $1; }
	;

declaration
	: /*declaration_specifiers ';'
	|*/ declaration_specifiers init_declarator_list ';'
		{
			PIDENT_t psym,ptemp;
			PLIST_t symlist=NULL;

			psym = $2;
			if(IDENT_TYPE($2) == VARIABLE_t)
			{
				while(psym)
				{
					ptemp = psym->parg_list;
					psym->parg_list = NULL;
					/* pointers followed by base type */
					if(IDENT_VARTYPE(psym))
						add_subtype(IDENT_VARTYPE(psym), $1);
					else
						IDENT_VARTYPE(psym) = $1;
					add_symbol(psym);
					/* define_symbol(psym); */
					if(symlist==NULL)
						symlist = new_node(SYMBOL_TYPE, psym);
					else
						add_node(symlist, new_node(SYMBOL_TYPE,psym));
					psym = ptemp;
				}
			}
			else if(IDENT_TYPE($2) == ARRAY_t)
			{
				IDENT_VARTYPE(psym) = $1;
				/* base type followed by size */
				add_subtype(IDENT_VARTYPE(psym), IDENT_VARTYPE((psym->parg_list)));
				psym->parg_list = NULL;
				add_symbol(psym);
				symlist = new_node(SYMBOL_TYPE, psym);
			}
			else
			{
				/* pointers followed by base type */
				if(IDENT_VARTYPE(psym))
					add_subtype(IDENT_VARTYPE(psym), $1);
				else
					IDENT_VARTYPE(psym) = $1;
				add_symbol(psym);
				/* define_symbol(psym) */
				symlist = new_node(SYMBOL_TYPE, psym);
			}
			$$ = symlist;
		}
	;

declaration_specifiers
	: storage_class_specifier
		{
			$$ = new_type(0,0,0,0,$1.token);
		}
	| storage_class_specifier declaration_specifiers
		{
			$2->specifier = $1.token;
			$$ = $2;
		}
	| type_specifier
		{
			$$ = $1;
		}
	| type_specifier declaration_specifiers
		{
			$1->type = $2->type;
			$$ = $1;
		}
	| type_qualifier
		{
			$$ = new_type(0,0,$1.token,0,0);
		}
	| type_qualifier declaration_specifiers 
		{
			$2->qualifier = $1.token;
			$$ = $2;
		}
	;

init_declarator_list
	: init_declarator
		{
			$$ = $1;
		}
	| init_declarator_list ',' init_declarator
		{
			add_argument($1,$3);
			$$ = $1;
		}
	;

init_declarator
	: declarator
		{
			$$ = $1;
		}
	| declarator ASSIGN_OP initializer
		{
			/*typecheck($1, $3);*/
			$1->pinitlist = $3;
			$$ = $1;
			/*printf("\n**%d", DATA_INT((PDATA_t)($3->node_ptr)));*/
		}
	;

storage_class_specifier
	: TYPEDEF			{ $$.token = (TYPE_e)TYPEDEF_t; }
	| EXTERN			{ $$.token = (TYPE_e)EXTERN_t; }
	| STATIC			{ $$.token = (TYPE_e)STATIC_t; }
	| AUTO				{ $$.token = (TYPE_e)AUTO_t; }
/*	| REGISTER			{ $$.token = (TYPE_e)REGISTER_t; }*/
	;

type_specifier
	: VOID				{ $$ = new_type(VOID_t,0,0,0,0); }
	| CHAR				{ $$ = new_type(CHAR_t,SIGNED_t,0,0,0); }
	| SHORT				{ $$ = new_type(SHORT_t,SIGNED_t,0,0,0);}
	| INT				{ $$ = new_type(INT_t,SIGNED_t,0,0,0);}
	| LONG				{ $$ = new_type(LONG_t,SIGNED_t,0,0,0);}
	| FLOAT				{ $$ = new_type(FLOAT_t,SIGNED_t,0,0,0);}
	| DOUBLE			{ $$ = new_type(DOUBLE_t,SIGNED_t,0,0,0);}
	| SIGNED			{ $$ = new_type(INT_t,SIGNED_t,0,0,0);}
	| UNSIGNED			{ $$ = new_type(INT_t,UNSIGNED_t,0,0,0);}
	| struct_or_union_specifier 
		{ 
			$$ = new_type(STRUCT_t,0,0,0,0);
			$$->u.ptag = $1;
		}
	| enum_specifier			{ $$ = NULL; }
/*	| TYPE_NAME  */
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}'
		{
			PIDENT_t psym;

			psym = new_ident($2.data);
			IDENT_TYPE(psym) = STRUCT_t;
			IDENT_ARGLST(psym) = $4;
			add_symbol(psym); /* new symbol */

			$$ = psym;
		}
/*	| struct_or_union '{' struct_declaration_list '}' */
	| struct_or_union IDENTIFIER
		{
			PIDENT_t psym;

			psym = get_symbol($2.data);
			if(!psym)
				yyerror("undeclared identifier");
			else
				$$ = psym;
		}
	;

struct_or_union
	: STRUCT			{ $$.token = (TYPE_e)STRUCT_t; }
	| UNION				{ $$.token = (TYPE_e)UNION_t; }
	;

struct_declaration_list
	: struct_declaration
		{
			$$ = $1;
		}
	| struct_declaration_list struct_declaration
		{
			add_argument($1,$2);
			$$ = $1;
		}
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
		{
			if(IDENT_VARTYPE($2))
			{
				add_subtype(IDENT_VARTYPE($2),$1);
				add_subtype(IDENT_VARTYPE($2), IDENT_VARTYPE(($2->parg_list)));
				$2->parg_list = NULL;
			}
			else
				IDENT_VARTYPE($2) = $1;
			$$ = $2;
		}
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
		{
			$1->type = $2->type;
			$1->specifier = $2->specifier;
			$$ = $1;
		}
	| type_specifier
		{
			$$ = $1;
		}
	| type_qualifier specifier_qualifier_list
		{
			$2->qualifier = $1.token;
			$$ = $2;
		}
	| type_qualifier
		{
			$$ = new_type(0,0,$1.token,0,0);
		}
	;

struct_declarator_list
	: struct_declarator
		{
			$$ = $1;			
		}
/*	| struct_declarator_list ',' struct_declarator */
	;

struct_declarator
	: declarator
		{
			if(IDENT_TYPE($1) == ARRAY_t)
			{
				/* base type followed by size */
				IDENT_VARTYPE($1) = new_type(ARRAY_t,0,0,0,0);
			}
			IDENT_TYPE($1) = MEMBER_t;
			$$ = $1;
		}
/*	| ':' constant_expression */
/*	| declarator ':' constant_expression */
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: IDENTIFIER
	| IDENTIFIER ASSIGN_OP constant_expression
	;

type_qualifier
	: CONST			{$$.token = (TYPE_e)CONST_t;}
	| VOLATILE		{$$.token = (TYPE_e)VOLATILE_t;}
	;

declarator
	: pointer direct_declarator
		{
			IDENT_VARTYPE($2) = $1;
			$$ = $2;			
		}
	| direct_declarator
		{
			$$ = $1;
		}
	;

direct_declarator
	: IDENTIFIER
		{
			$$ = new_ident($1.data);
			IDENT_TYPE($$) = VARIABLE_t;
		}
/*	| '(' declarator ')' */
	| direct_declarator '[' constant_expression ']'
		{
			PIDENT_t arrsize;
			
			IDENT_TYPE($1) = ARRAY_t;
			arrsize = new_ident("~arrsize");
			ident_addstuff(arrsize, INT_t, new_type(INT_t,0,0,0,0),NULL);
			arrsize->pvar_type->size = DATA_INT(NODE_DATA($3));
			add_argument($1,arrsize);
			$$ = $1;
		}
	| direct_declarator '[' ']'
		{
			PIDENT_t arrsize;
			
			IDENT_TYPE($1) = ARRAY_t;
			arrsize = new_ident("~arrsize");
			ident_addstuff(arrsize, INT_t, new_type(INT_t,0,0,0,0),NULL);
			arrsize->pvar_type->size = 0;
			add_argument($1,arrsize);
			$$ = $1;
		}
	| direct_declarator '(' parameter_type_list ')'
		{
			IDENT_TYPE($1) = FUNCTION_t;
			IDENT_ARGLST($1) = $3;
			$$ = $1;
			//print_symbol($1);
			g_current_function = $1;
			/* update stack position for return val */
			g_current_function->stackpos = update_parameter_offsets(IDENT_ARGLST(g_current_function));
		}
	| direct_declarator '(' identifier_list ')'
	| direct_declarator '(' ')'
		{
			IDENT_TYPE($1) = FUNCTION_t;
			$$ = $1;
		}
	;

pointer
	: '*'
		{
			$$ = new_type(POINTER_t,0,0,0,0);
		}
/*	| '*' type_qualifier_list */
	| '*' type_qualifier
		{
			$$ = new_type(POINTER_t,0,0,0,$2.token);
		}
	| '*' pointer
		{
			add_subtype($2,new_type(POINTER_t,0,0,0,0));
			$$ = $2;
		}
/*	| '*' type_qualifier_list pointer */
	;

/*type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;
*/

parameter_type_list
	: parameter_list { $$ = $1; }
/*	| parameter_list ',' ELLIPSIS */
	;

parameter_list
	: parameter_declaration { $$ = $1; }
	| parameter_list ',' parameter_declaration
		{
			add_argument($1,$3);
			$$ = $1;
		}
	;

parameter_declaration
	: declaration_specifiers declarator
		{
			IDENT_TYPE($2) = PARAMETER_t;
			if(IDENT_VARTYPE($2))
				add_subtype(IDENT_VARTYPE($2), $1);
			else
				IDENT_VARTYPE($2) = $1;
			$$ = $2;
		}
	| declaration_specifiers abstract_declarator
		{
			PIDENT_t param;
			
			param = new_ident("~dummy");
			IDENT_TYPE(param) = PARAMETER_t;
			if($2)
				add_subtype($2, $1);
			else
				$2 = $1;
			IDENT_VARTYPE(param) = $2;
			$$ = param;
		}
	| declaration_specifiers
		{
			PIDENT_t param;
			
			param = new_ident("~dummy");
			IDENT_TYPE(param) = PARAMETER_t;
			IDENT_VARTYPE(param) = $1;
			$$ = param;
		}
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

/*type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;
*/
abstract_declarator
	: pointer	{ $$ = $1; }
/*	| direct_abstract_declarator
	| pointer direct_abstract_declarator */
	;

/*
direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;
*/
initializer
	: assignment_expression { $$ = $1; }
	| '{' initializer_list '}' { $$ = $2; }
	| '{' initializer_list ',' '}' { $$ = $2; }
	;

initializer_list
	: initializer { $$ = $1; }
	| initializer_list ',' initializer
		{
			add_node($1, $3);
			$$ = $1;
		}
	;

statement
	: labeled_statement 
		{ 
			$$ = $1;
		}
	| compound_statement
		{ 
			$$ = $1;
		}
	| expression_statement
		{ 
			$$ = $1;
		}
	| selection_statement
		{ 
			$$ = $1;
		}
	| iteration_statement
		{ 
			$$ = $1;
		}
	| jump_statement
		{ 
			$$ = $1;
		}
	;

labeled_statement
	: /*IDENTIFIER ':' statement
		{
			PCR_t label;
			label = new_label($1.data);
			$$ = prefix_label($3, label);
		}
	|*/ CASE constant_expression ':' statement
		{
			PCR_t pcrcase;
			pcrcase = new_cr(CRCASEVAL, 0);
			add_operand(pcrcase,0,$2);
			$$ = add_cr(pcrcase,$4);
		}
	| DEFAULT ':' statement
		{
			$$ = $3;
		}
	;

compound_statement
	: '{' '}' { $$=NULL; }
	| '{' statement_list '}' { $$=NULL; $$ = add_cr($$,$2); }
/*	| '{' declaration_list '}'*/
	| '{' declaration_list statement_list '}' { $$=NULL; $$ = add_cr($$,$3); }
	;

declaration_list
	: declaration { $$ = $1; }
	| declaration_list declaration 
		{
			add_node($1, $2);
			$$ = $1;
		}
	;

statement_list
	: statement 
		{
			$$ = NULL;
			$$ = add_cr($$,$1); 
		}
	| statement_list statement
		{
			$$ = add_cr($1, $2);
		}
	;

expression_statement
	: ';' { $$=NULL; }
	| expression ';' 
		{
			PCR_t pcrexp;
			pcrexp = new_cr(CREXPVAL, 0);
			add_operand(pcrexp,0/*operand number*/,$1);
			$$ = pcrexp;
		}
	;

selection_statement
	: IF '(' expression ')' statement
		{
			$$ = emit_if($3/*exp*/, 0/*boolean exp*/, $5/*true block*/,0/*false block*/);
			g_cr_block = 0;
		}
	| IF '(' expression ')' statement ELSE statement
		{
			$$ = emit_if($3/*exp*/, 0/*boolean exp*/, $5/*true block*/,$7/*false block*/);
			g_cr_block = 0;
		}
	| SWITCH '(' expression ')' statement
		{
			PCR_t label;
			label = new_label();
			$$ = emit_switch($3/*exp*/, $5/*statement list*/);
			$$ = prefix_label($$,label);
			$$ = process_break_continue($$,label);
		}
	;

iteration_statement
	: WHILE '(' expression ')' statement
		{
			PCR_t label, pcr;
			label = new_label(); /* create label like __L1: */
			$5 = add_cr($5, emit_jp(label));
			pcr = emit_if($3, 0, $5, 0);
			$$ = prefix_label(pcr, label);
			$$ = process_break_continue($$,label);
			g_cr_block=0;
		}
	| DO statement WHILE '(' expression ')' ';'
		{
			PCR_t label, pcr;
			label = new_label(); /* create label like __L1: */
			pcr = emit_if($5,0, emit_jp(label),0);
			pcr = add_cr($2,pcr);
			$$ = prefix_label(pcr, label);
			$$ = process_break_continue($$,label);
			g_cr_block=0;
		}
/*	| FOR '(' expression_statement expression_statement ')' statement */
	| FOR '(' expression_statement expression_statement expression ')' statement
		{
			PCR_t label, pcr;
			label = new_label(); /* create label like __L1: */
			$7 = add_cr($7, get_exp_cr($5));
			$7 = add_cr($7, emit_jp(label));
			pcr = emit_if((PLIST_t)($4->operand[0]), 0, $7, 0);
			$$ = add_cr($3,prefix_label(pcr, label));
			$$ = process_break_continue($$,label);
		}
	;

jump_statement
	: /*GOTO IDENTIFIER ';'
	|*/ CONTINUE ';'
		{
			$$ = new_cr(CRCONTINUE, 0); /* this code record will be processed later */
		}
	| BREAK ';'
		{
			$$ = new_cr(CRBREAK, 0); /* this code record will be processed later */
		}
	| RETURN ';'
		{
			$$ = new_cr(CRBREAK, 0); /* this code record will be processed later */
		}
	| RETURN expression ';'
		{
			PCR_t pcr,pcrexp;
			pcrexp = new_cr(CREXPVAL, 0);
			add_operand(pcrexp,0/*operand number*/,$2);
			pcr = return_val($2);
			pcr = add_cr(pcrexp,pcr);
			$$ = add_cr(pcr,new_cr(CRBREAK, 0)); /* this code record will be processed later */
		}
	;

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
		{
			//print_cr_block($1);
			if( !emit_function($1) )
				yyerror("Internal Error");
			else
			{
				$1 = prefix_label(g_cr_block,new_func_label(g_current_function->pident_name));
				file_flag = 1;
				print_cr_block($1);
				print_function();
				delete_symhash(1);
				file_flag = 0;

				g_current_function = (PIDENT_t)NULL;
			}
			//print_cr_block($1);
			max_pseudo_num = 0; /* reset the pseudo registe counter */
			g_cr_block=0;
		}
	| declaration
		{
			emit_sym_decl($1);
		}
	;

function_definition
	: /*declaration_specifiers declarator declaration_list compound_statement
	|*/ declaration_specifiers declarator compound_statement
		{
			PIDENT_t psym;
			
			psym = $2;
			/* pointers followed by base type */
			if(IDENT_VARTYPE(psym))
				add_subtype(IDENT_VARTYPE(psym), $1);
			else
				IDENT_VARTYPE(psym) = $1;
			add_symbol(psym);
			g_current_function = psym;
			$$ = $3;
		}
	/*| declarator declaration_list compound_statement*/
	| declarator compound_statement
		{
			PIDENT_t psym;
			
			psym = $1;
			/* pointers followed by base type */
			if(IDENT_VARTYPE(psym))
				add_subtype(IDENT_VARTYPE(psym), new_type(VOID_t,0,0,0,0));
			else
				IDENT_VARTYPE(psym) = new_type(VOID_t,0,0,0,0);
			add_symbol(psym);
			g_current_function = psym;
			$$ = $2;
		}
	;

%%

void yyerror(s)
char *s;
{
	fflush(stdout);
	printf("\n%s (%d): ERROR :%s \n", g_filelist[inc_level].filename, g_line, s);
	g_errcount++;
}

