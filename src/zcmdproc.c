/************************************************************************/
/* Command processor module                                             */
/************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "zcmdproc.h"
#include "zpreproc.h"

#define MAX_OPT 6

extern char *inp_file; /* Input c file */
extern char *out_file; /* Output src file */
extern char *lst_file; /* Output c list file */
extern char *module_seg; /* Module segment */

int flags[] = { 0, 0, 0 };
char *cmdopt[MAX_OPT] = 
{
	"-verbose",
	"-genlst",
	"-incsrc",
	"-include:",
	"-define:",
	"-help"
};
char *helpopt[MAX_OPT] = 
{
	"Display the output generated in various stages of compilation",
	"Generates the preprocessed input file",
	"Embeds the source content in the output file",
	"Specifies the include path list separated by semicolon",
	"Command line macro definition",
	"Displays this help"
};

void usage()
{
	int index=0;

	puts("\nZCC Command line options");
	for(;index<MAX_OPT;index++)
	{
		printf("\n  %s\t-  %s",cmdopt[index],helpopt[index]);
	}
}

int update_fileinfo(char *inpfile)
{
	char *ptr=0;

	if(strrchr(inpfile,'.'))
	{
		out_file = (char*)calloc(1,strlen(inpfile)+5);
		lst_file = (char*)calloc(1,strlen(inpfile)+5);
		module_seg = (char*)calloc(1,strlen(inpfile)+6);

		strcpy(out_file,inpfile);
		strcpy(lst_file,inpfile);
		strcpy(module_seg,inpfile);

		ptr = strrchr(out_file,'.'); *ptr=0;
		ptr = strrchr(lst_file,'.'); *ptr=0;
		ptr = strrchr(module_seg,'.'); *ptr=0;
		strcat(out_file,".src");
		strcat(lst_file,".lis");
		strcat(module_seg,"_TEXT");
	}
	else
		return 0;

	return 1;
}

int process_commands(int argc, void *argv[])
{
	char *cmd=0;
	int index=0;
	int file_flg=0;

	while(argc)
	{
		cmd = (char*)argv[0];

		if(*cmd == '-')
		{
			for(index=0;index<MAX_OPT;index++)
			{
				if(!strnicmp(cmd,cmdopt[index],strlen(cmdopt[index])))
				{
					switch(index)
					{
					case VERBOSE: /* verbose */
						flags[VERBOSE] = 1;
						break;
					case GENLST:
						flags[GENLST] = 1;
						break;
					case INCSRC:
						flags[INCSRC] = 1;
						break;
					case INCLUDE:
						cmd += strlen(cmdopt[INCLUDE]);
						update_includelist(cmd);
						break;
					case DEFINE:
						cmd += strlen(cmdopt[DEFINE]);
						update_maclist(cmd);
						break;
					case HELP:
						usage();
						return 0;
					default:
						{
							printf("\nERROR: Invalid option %s",cmd);
							return 0;
						}
						break;
					}
				}
			}
		}
		else
		{
			file_flg = 1;
			inp_file = (char*)calloc(1,strlen(cmd)+1);
			strcpy(inp_file,cmd);
			if(!update_fileinfo(inp_file))
				return 0;
		}

		++argv;
		--argc;
	}

	if(!file_flg)
	{
		printf("\nERROR: Source file is not given");
		usage();
		return 0;
	}

	return 1;
}
