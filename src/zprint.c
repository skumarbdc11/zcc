/************************************************************************/
/* Print routines                                                       */
/************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "zstruct.h"
#include "ztypesize.h"
#include "zpreproc.h"
#include "zcmdproc.h"

extern PIDENT_t g_current_function;
extern int get_typesize(PTYPE_t ptype);
extern FILE *outfile;
extern char *module_seg; /* Module segment */
extern char *inp_file; /* Input c file */
extern int flags[];

static char buff[512];
int file_flag=0;
PPATHLIST_t xdeflist=0;
FILE *linefile=0;

void add_xdef(char *name)
{
	PPATHLIST_t node=0;

	node = (PPATHLIST_t)calloc(1,sizeof(PATHLIST_t));
	strcpy(node->path,name);

	if(xdeflist)
		node->next = xdeflist;
	xdeflist = node;

	return;
}

static char *mnemonic[] = { "<null>", 
"LD", "ADD", "ADC", "SUB", "SBC", "CP", "CPC", "NEG", "COM", "MUL", "SMUL",
"UDIV", "SDIV", "SLL", "SRL", "SRA", "AND", "XOR", "OR", "LD"/*LDCC*/,
"JP", "CPZ", "INC", "DEC", "LEA", "PUSH", "POP", "CALLA", "PUSHM", "POPM",
"LINK", "UNLINK", "RET"
};

void print_instruction(PINST_t pinst)
{
	switch(pinst->inst_type)
	{
	case OTHER:
		{
		}
		break;
	default:
		{
			sprintf(buff, "%s", mnemonic[pinst->inst]);
		}
		break;
	}
}

static char *suffix[] = { 
	" ","b","w","sb","sw","ub","uw", 
	"lt", "ult", "gt", "ugt", "le", "ule", "ge", "uge", "eq", "ne" };
void print_directive(DIR_e dir)
{
	char buf[10];

	if(!dir)
	{	strcat(buff,"\t\t"); return; }

	if(dir<7) 
		sprintf(buf,".%s\t", suffix[dir]);
	else
		sprintf(buf,"\t\t%s, ", suffix[dir]);
	strcat(buff,buf);
}

void print_operand(NTYPE_e type, PLIST_t operand)
{
	char buf[10];

	switch(type)
	{
	case CONSTANT_TYPE:
		{
			sprintf(buf," #%xh", DATA_INT(NODE_DATA(operand)));
		}
		break;
	case ADDRESS_TYPE:
		{
			PLABEL_t label = (PLABEL_t)(operand->node_ptr);
			sprintf(buf," %s", label->name);
		}
		break;
	case REGISTER_TYPE:
		{
			PREG_t reg = (PREG_t)(operand->node_ptr);
			if(reg->pseudo_flag)
				sprintf(buf," $R%d", reg->u.number);
			else
				sprintf(buf," %s", reg->u.name);
		}
		break;
	case REGIND_TYPE:
		{
			PREG_t reg = (PREG_t)(operand->node_ptr);
			if(reg->pseudo_flag)
				sprintf(buf," ($R%d)", reg->u.number);
			else
				sprintf(buf," (%s)", reg->u.name);
		}
		break;
	case FPREL_TYPE:
	case REGREL_TYPE:
		{
			PREG_t reg = (PREG_t)(operand->node_ptr);

			if(reg->pseudo_flag)
				sprintf(buf," %d($R%d)", (reg->offset), reg->u.number);
			else
				sprintf(buf," %d(%s)", reg->offset, reg->u.name);
		}
		break;
	case REGINC_TYPE:
		{
			PREG_t reg = (PREG_t)(operand->node_ptr);
			if(reg->pseudo_flag)
				sprintf(buf," ($R%d++)", reg->u.number);
			else
				sprintf(buf," (%s++)", reg->u.name);
		}
		break;
	case REGDEC_TYPE:
		{
			PREG_t reg = (PREG_t)(operand->node_ptr);
			if(reg->pseudo_flag)
				sprintf(buf," (--$R%d)", reg->u.number);
			else
				sprintf(buf," (--%s)", reg->u.name);
		}
		break;
	}
	strcat(buff,buf);
}

void print_operands(PCR_t pcr)
{
	int count=0;

	while(count<pcr->pinst->num_op)
	{
		print_operand(pcr->pinst->op_type[count], pcr->operand[count]);

		count++;
		if(count<pcr->pinst->num_op)
			strcat(buff,",");
	}
}

void openfile()
{
	if(linefile)
		rewind(linefile);
	else
		linefile = fopen(inp_file,"r");
}

void closefile()
{
}

void includesource(int prev, int curr)
{
	int count=0;
	char ch=0;

	if(prev)
	{
		count = curr - prev;
		if(count)
			fprintf(outfile,"\n;");
		else
			fputc('\n',outfile);
		while(count)
		{
			ch = fgetc(linefile);
			fputc(ch,outfile);
			if(ch=='\n')
			{
				count--;
				if(count)
					fputc(';',outfile);
			}
		}
	}
	else
	{
		while(1)
		{
			ch = fgetc(linefile);
			if(ch=='\n')
			{
				count++;
				if(count==(curr-1))
					break;
			}
		}
		
		fprintf(outfile,"\n;");
		while(1)
		{
			ch = fgetc(linefile);
			fputc(ch,outfile);
			if(ch=='\n')
				break;
		}
	}
}

void print_cr_block(PCR_t block)
{
	int index=0;
	int prev_line=0;

	if(file_flag)
	{
		fprintf(outfile,"\n\n\tSEGMENT %s\n",module_seg);
		add_xdef(g_current_function->pident_name);
	}
	while(block)
	{
		if(file_flag)
			fprintf(outfile,"\t");
		else
			printf("\n%3d: ", index++);
		switch(block->cr_type)
		{
		case CRINST:
			{
				print_instruction(block->pinst);
				print_directive(block->directive);
				print_operands(block);
				strcat(buff,"\n");
				if(file_flag)
					fputs(buff,outfile);
				else
					puts(buff);
			}
			break;
		case CRLABEL:
			{
				PLABEL_t label=0;

				label = (PLABEL_t)(block->operand[0]->node_ptr);
				if(file_flag)
					fprintf(outfile,"\n%s:\n",label->name);
				else
					printf("\n%s:", label->name);
			}
			break;
		case CRLINE:
			{
				if(block->next && (block->next->cr_type==CRLINE))
					break;
				if(flags[INCSRC])
				{
					if(prev_line==0)
						openfile();
					includesource(prev_line,block->lineno);
					prev_line = block->lineno;
				}
				else
					fputc('\n',outfile);
			}
			break;
		}
		block = block->next;
	}
	closefile();
}

void print_function()
{
	PIDENT_t arglist;
	if(g_current_function)
	{
		if(!file_flag)
		{
			printf("\n\n;************************* _%s *************************", g_current_function->pident_name);
			printf(  "\n;Name                   Address       Size");
			arglist = g_current_function->parg_list;
			while(arglist)
			{
				printf("\n;%-23sFP+%-11d%-3d",arglist->pident_name,arglist->stackpos+8,
					get_typesize(arglist->pvar_type));
				arglist = arglist->parg_list;
			}
		}
		else
		{
			fprintf(outfile,"\n\n;************************* _%s *************************", g_current_function->pident_name);
			fprintf(outfile,  "\n;Name                   Address       Size");
			arglist = g_current_function->parg_list;
			while(arglist)
			{
				fprintf(outfile,"\n;%-23sFP+%-11d%-3d",arglist->pident_name,arglist->stackpos+8,
					get_typesize(arglist->pvar_type));
				arglist = arglist->parg_list;
			}
		}
	}
}

void print_localsymbol(PIDENT_t psym)
{
	if(psym)
	{
		if(!file_flag)
		{
			printf("\n;%-23sFP-%-11d%-3d",psym->pident_name,psym->stackpos,
				get_typesize(psym->pvar_type));
		}
		else
		{
			if(psym->scope)
			{
				fprintf(outfile,"\n;%-23sFP-%-11d%-3d",psym->pident_name,psym->stackpos,
					get_typesize(psym->pvar_type));
			}
		}
	}
}

void declare_symbol(PIDENT_t psym)
{
	int init_flag=0, size=0, total=0, count=0;
	PDATA_t pdata=0;
	PLIST_t pinitlist=0;

	if(psym->scope)
		return;

	init_flag = (psym->pinitlist)?1:0;

	if(psym->ident_type != FUNCTION_t)
	{
		/* Select segment */
		if(init_flag)
		{
			fprintf(outfile, "\n\tSEGMENT FAR_DATA");
		}
		else
		{
			fprintf(outfile, "\n\tSEGMENT FAR_BSS");
		}

		/* Create label */
		fprintf(outfile, "\n_%s:",psym->pident_name);
		add_xdef(psym->pident_name);
	}

	/* allocate size & initialize it */
	switch(psym->ident_type)
	{
	case VARIABLE_t:
		{
			if(init_flag)
			{
				pdata = (PDATA_t)(psym->pinitlist->node_ptr);
				switch(get_typesize(psym->pvar_type))
				{
				case CHAR_SIZE:
					fprintf(outfile, "\n\tDB %d",pdata->val.int_val&0xff);
					break;
				case SHORT_SIZE:
					fprintf(outfile, "\n\tDW %d",pdata->val.int_val&0xffff);
					break;
				case INT_SIZE:
					fprintf(outfile, "\n\tDL %d",pdata->val.int_val);
					break;
				}
			}
			else
			{
				fprintf(outfile,"\n\tDS %d",get_typesize(psym->pvar_type));
			}
		}
		break;

	case ARRAY_t:
		{
			if(init_flag)
			{
				pinitlist = psym->pinitlist;
				size = get_typesize(psym->pvar_type);
				count = 0;

				while (pinitlist) 
				{
					count++;
					pdata = (PDATA_t)(pinitlist->node_ptr);
					if(pdata->pdata_type->type == STRING_t)
					{
						fprintf(outfile,"\n\tDB \"%s\"\n\tDB 0",pdata->val.pstring);
						return;
					}
					else
					{
						switch(size)
						{
						case CHAR_SIZE:
							fprintf(outfile,"\n\tDB %d",pdata->val.int_val&0xff);
							break;
						case SHORT_SIZE:
							fprintf(outfile,"\n\tDW %d",pdata->val.int_val&0xffff);
							break;
						case INT_SIZE:
							fprintf(outfile,"\n\tDL %d",pdata->val.int_val);
							break;
						}
					}
					pinitlist = pinitlist->next;
				}

				total = psym->pvar_type->u.psubtype->size;
				if(count<total)
				{
					while(total-count)
					{
						count++;
						switch(size)
						{
						case CHAR_SIZE:
							fprintf(outfile,"\n\tDB 0");
							break;
						case SHORT_SIZE:
							fprintf(outfile,"\n\tDW 0");
							break;
						case INT_SIZE:
							fprintf(outfile,"\n\tDL 0");
							break;
						}
					}
				}
			}
			else
			{
				fprintf(outfile,"\n\tDS %d",get_typesize(psym->pvar_type));
			}
		}
		break;

	case FUNCTION_t:
		{
			add_xdef(psym->pident_name);
		}
		break;
	}

	if(psym->ident_type != FUNCTION_t)
	{
		if(psym->parg_list)
			declare_symbol(psym->parg_list);
	}
}

void print_xdefs()
{
	fputs("\n",outfile);
	while(xdeflist)
	{
		fprintf(outfile,"\n\tXDEF _%s",xdeflist->path);
		xdeflist = xdeflist->next;
	}
}