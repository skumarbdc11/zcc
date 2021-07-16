/************************************************************************/
/* Symbol table implementation                                          */
/************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "zassert.h"
#include "zsymtab.h"
#include "zutils.h"

/* DEBUG option */
#define SYMDEBUG 0

#define HASH_SIZE 27

/* prototypes */
void delete_symnode(PSYM_TAB);
int hashfunction(char*);

/* externs */
extern int g_scope_level;
extern long g_stack_size;
extern void yyerror(char *s);
extern void print_localsymbol(PIDENT_t psym);

/************************************************************************/
/* Symbol table                                                         */
/************************************************************************/
PSYM_TAB g_symtab[HASH_SIZE];
PSYM_TAB l_symtab[HASH_SIZE];

/************************************************************************/
/* Interfaces                                                           */
/************************************************************************/
void init_symhash(void)
{
	int index = 0;

#if SYMDEBUG
	printf("init_symhash : size=%d\n",HASH_SIZE);
#endif
	for(;index<=HASH_SIZE;index++)
		g_symtab[index] = NULL, l_symtab[index] = NULL;
}

void add_symbol(PIDENT_t pattrib)
{ 
	int index=0;
	PSYM_TAB temp;
	char *gsymname = NULL;

	if(get_symbol(pattrib->pident_name))
	{
		yyerror("Multiple declaration");
		return;
	}
	index = hashfunction(pattrib->pident_name);

#if SYMDEBUG
	//printf("add_symbol: %s: indx:%d: scope:%d\n",pattrib->pident_name,index,g_scope_level);
	print_symbol(pattrib);
#endif
	if( g_scope_level == 0 ) /* global */
	{
		pattrib->scope = 0;
		if (g_symtab[index] == NULL ) /*** insert in main array ***/
		{
			g_symtab[index] = (PSYM_TAB)calloc(1,sizeof(SYM_TAB));
			g_symtab[index]->name = strdup(pattrib->pident_name);
			g_symtab[index]->pattrib = pattrib;
			g_symtab[index]->link = NULL;
		}
		else /*** insert in new node ***/
		{
			temp=(PSYM_TAB)calloc(1,sizeof(SYM_TAB));
			temp->name = strdup(pattrib->pident_name);
			temp->pattrib = pattrib;
			temp->link = g_symtab[index];
			g_symtab[index] = temp;
		}
	}
	else
	{
		pattrib->scope = g_scope_level;
		if(pattrib->ident_type != FUNCTION_t)
		{
			/* current stack size */
			pattrib->stackpos = g_stack_size;
			g_stack_size += get_typesize(pattrib->pvar_type);
		}

		if (l_symtab[index] == NULL ) /*** insert in main array ***/
		{
			l_symtab[index] = (PSYM_TAB)calloc(1,sizeof(SYM_TAB));
			l_symtab[index]->name = strdup(pattrib->pident_name);
			l_symtab[index]->pattrib = pattrib;
			l_symtab[index]->link = NULL;
		}
		else /*** insert in new node ***/
		{
			temp=(PSYM_TAB)calloc(1,sizeof(SYM_TAB));
			temp->name = strdup(pattrib->pident_name);
			temp->pattrib = pattrib;
			temp->link = l_symtab[index];
			l_symtab[index] = temp;
		}
	}
}

PIDENT_t get_symbol(char *symname)
{ 
	PSYM_TAB p=NULL;

	/* first local scope */
	if(g_scope_level)
	{
		p = l_symtab[hashfunction(symname)];

		while ( p!=NULL && strcmp(symname, p->name) )   p = p->link;
	}

	if(!p)
	{
		/* then global scope */
		p = g_symtab[hashfunction(symname)];
		while ( p!=NULL && strcmp(symname, p->name) )   p = p->link;
	}

#if SYMDEBUG
	if(p)
		printf("get_symbol: %s: scope:%d\n",p->name, p->pattrib->scope);
#endif

	return( (p)?p->pattrib:NULL );
}

void delete_symhash(int scope)
{
	int index = 0;
	PSYM_TAB ptemp=NULL, ptemp1=NULL;

#if SYMDEBUG
	printf("delete_symhash : size=%d\n",HASH_SIZE);
#endif
	for(;index<=HASH_SIZE;index++)
	{
		if(scope)
			ptemp = l_symtab[index];
		else
			ptemp = g_symtab[index];

		while(ptemp && (ptemp->pattrib->scope == scope))
		{
			ptemp1 = ptemp->link;
			print_localsymbol(ptemp->pattrib);
			delete_symnode(ptemp);
			if(scope)
				l_symtab[index] = ptemp = ptemp1;
			else
				g_symtab[index] = ptemp = ptemp1;

			if(ptemp==NULL) break;
		}
	}
}

/************************************************************************/
/* Utility functions                                                    */
/************************************************************************/
int hashfunction(char *symname)
{
	if(symname[0] == '_')
		return 26;
	else
		return (toupper(symname[0])-'A');
}

void delete_symnode(PSYM_TAB node)
{

#if SYMDEBUG
	ZASSERT(node);
	printf("deleting node %s : scope %d\n", node->name,node->pattrib->scope);
#endif	
	if(node->pattrib)
		delete_ident(node->pattrib);

	free(node->name); node->name = NULL;
	free(node);
}

static int level=1;
static char *type_info[28] = {"<null>","VOID_t","CHAR_t","SHORT_t","INT_t","LONG_t","FLOAT_t","DOUBLE_t","SIGNED_t","UNSIGNED_t","POINTER_t",
		   "STRING_t","EXTERN_t","STATIC_t","CONST_t","AUTO_t","GLOBAL_t","VARIABLE_t","FUNCTION_t","MEMBER_t",
		   "STRUCT_t","UNION_t","TAG_t","TYPEDEF_t","VOLATILE_t","ARRAY_t" , "PARAMETER_t" };
void print_type(PTYPE_t ptype);

void print_initlist(PLIST_t pinitlist)
{
	while(pinitlist)
	{
		switch(pinitlist->node_type)
		{
		case CONSTANT_TYPE:
			{
				printf("{%d} ",DATA_INT((PDATA_t)(pinitlist->node_ptr)));
			}
			break;
		case STRING_TYPE:
			{
				printf("{%s} ",DATA_STR((PDATA_t)(pinitlist->node_ptr)));
			}
		}

		pinitlist = pinitlist->next;
	}
}

void print_symbol(PIDENT_t psym)
{
	printf("\n%*s{\n%*s ", level, " ", level, " "); level+=4;
	if(IDENT_NAME(psym))
		printf("%s,",IDENT_NAME(psym));
	if(IDENT_TYPE(psym))
		printf("type:%s,",type_info[IDENT_TYPE(psym)]);
	if(IDENT_VARTYPE(psym))
		print_type(IDENT_VARTYPE(psym));
	if(IDENT_ARGLST(psym))
		print_symbol(IDENT_ARGLST(psym));
	if(psym->pinitlist)
		print_initlist(psym->pinitlist);
	level-=4; printf("\n%*s}\tscope=%d", level, " ",psym->scope);
}

void print_type(PTYPE_t ptype)
{
	printf("\n%*s[\n%*s ", level, " ", level, " "); level+=4;
	if(ptype->type)
		printf("%s,",type_info[ptype->type]);
	if(ptype->specifier)
		printf("%s,",type_info[ptype->specifier]);
	if(ptype->qualifier)
		printf("%s,",type_info[ptype->qualifier]);
	if(ptype->issigned)
		printf("%s,",type_info[ptype->issigned]);
	printf("size:%d,offset:%d",ptype->size,ptype->offset);
	if(ptype->u.psubtype)
	{
		switch(ptype->type)
		{
		case STRUCT_t:
			print_symbol(ptype->u.ptag);
			break;
		default:
			print_type(ptype->u.psubtype);
			break;
		}
	}
	level-=4; printf("\n%*s]", level, " ");
}