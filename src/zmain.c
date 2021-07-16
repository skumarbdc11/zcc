/************************************************************************/
/* ZCC main routine                                                     */
/************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "zsymtab.h"
#include "zpreproc.h"
#include "zcmdproc.h"

#define zparse() yyparse()

/* externs */
extern FILE *yyin;
extern int yydebug;
extern int yyparse();
extern FILELIST_t g_filelist[MAX_INCLUDES];
extern int inc_level;
extern int flags[];
extern void print_xdefs();

/* --scope level-- */
int g_scope_level = 0;

/* --stack size-- */
long g_stack_size = 0;

/* --current function symbol-- */
PIDENT_t g_current_function = 0;

/* --current cr block-- */
PCR_t g_cr_block=0;

/* --input/output file-- */
char *inp_file=0; /* Input c file */
char *out_file=0; /* Output src file */
char *lst_file=0; /* Output c list file */
char *module_seg=0; /* Module segment */

/* --file pointer-- */
FILE *pfile=0, *outfile=0;

/* --error count-- */
int g_errcount=0;

int cmain(int argc, void *argv[])
{
//	yydebug = 1;

	/* Initialize symbol table */
	init_symhash();


	argv++;
	if(!process_commands(argc-1, argv))
	{
		return 0;
	}

	if(preproc())
	{
		pfile = fopen(lst_file,"r");
		outfile = fopen(out_file,"w");

		if((!pfile) || (!outfile))
			return -1;

		yyin = pfile;
		strcpy(g_filelist[0].filename, inp_file);
		inc_level = 0;

		fprintf(outfile, "\n\tDEFINE %s, space=EROM\n", module_seg);

		printf("Compiling... %s",inp_file);
		zparse();
		print_xdefs();
		printf("\n%d error(s)",g_errcount);

		fclose(pfile);
		fclose(outfile);

		if(flags[GENLST] == 0)
			unlink(lst_file);
	}

	return 0;
}
