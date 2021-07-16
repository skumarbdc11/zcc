/************************************************************************/
/* Preprocessor routines                                                */
/************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "zpreproc.h"


extern char *inp_file; /* Input c file */
extern char *lst_file; /* Output c list file */

FILELIST_t g_filelist[MAX_INCLUDES];
int inc_level=0;

static char buff[MAX_BUFFSIZE];
static PPATHLIST_t g_pinclist=0;
static PMACROLIST_t g_pmaclist=0;

int update_stack(char *buffer)
{
	char *str = buffer;
	char *filename=0;
	FILE *ptemp=0;
	char file[MAX_BUFFSIZE];

	while(*str)
	{
		if((*str=='<') || (*str=='\"'))
		{
			str++;
			break;
		}
		str++;
	}

	if(*str)
	{
		filename = strtok(str,"\">");
		if(!filename)
			return 0;

		strcpy(g_filelist[inc_level].filename,filename);
		if(!(ptemp=fopen(filename,"r")))
		{
			while(g_pinclist)
			{
				sprintf(file,"%s\\%s",g_pinclist->path,filename);
				if((ptemp==fopen(file,"r")))
				{
					strcpy(g_filelist[inc_level].filename, file);
					return 1;
				}
				g_pinclist = g_pinclist->next;
			}
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
		return 0;

	return 1;
}

int read_line1(FILE *file, FILE *out)
{
	int count=0;
	int ch=0,ch1=0;

	while(1)
	{
		ch = fgetc(file);

		if(ch == EOF)
		{
			if(count)
			{
				g_filelist[inc_level].linecount++;
				return 1;
			}
			else
				return 0;
		}

		if(ch == '/')
		{
			if((ch1 = fgetc(file)) == '*')
			{
				fputc(ch,out);
				fputc(ch1,out);
				while(1)
				{
					ch = fgetc(file);
					ch1 = fgetc(file);
					if((ch=='*')&&(ch1=='/'))
					{
						fputc(ch,out);
						fputc(ch1,out);
						ch = fgetc(file);
						break;
					}
					else
						ungetc(ch1,file);

					fputc(ch,out);
					if(ch=='\n')
					{
						g_filelist[inc_level].linecount++;
					}
				}
			}
			else
				ungetc(ch1,file);
		}

		buff[count] = ch;
		++count;
		if(ch == '\n')
		{
			g_filelist[inc_level].linecount++;
			break;
		}
		if(count >= (MAX_BUFFSIZE-1))
		{
			buff[MAX_BUFFSIZE-1] = '\0';
			return 1;
		}
	}

	buff[count] = '\0';

	return 1;
}

int read_line(FILE *file, FILE *out)
{
	int count=0;
	char ch=0,ch1=0;

	while(1)
	{
		ch = fgetc(file);

		if(ch == EOF)
		{
			if(count)
			{
				g_filelist[inc_level].linecount++;
				return 1;
			}
			else
				return 0;
		}

		if(ch == '/')
		{
			if((ch1 = fgetc(file)) == '*')
			{
				fputc(ch,out);
				fputc(ch1,out);
				while(1)
				{
					ch = fgetc(file);
					ch1 = fgetc(file);
					if((ch=='*')&&(ch1=='/'))
					{
						fputc(ch,out);
						fputc(ch1,out);
						ch = fgetc(file);
						break;
					}
					else
						ungetc(ch1,file);

					fputc(ch,out);
					if(ch=='\n')
					{
						if(inc_level)
							fprintf(out,"%-*s",inc_level,"\t");
						g_filelist[inc_level].linecount++;
					}
				}
			}
			else
				ungetc(ch1,file);
		}

		fputc(ch,out);
		buff[count] = ch;
		++count;
		if(ch == '\n')
		{
			if(inc_level)
				fprintf(out,"%-*s",inc_level,"\t");
			g_filelist[inc_level].linecount++;
			break;
		}
		if(count >= (MAX_BUFFSIZE-1))
		{
			buff[MAX_BUFFSIZE-1] = '\0';
			return 1;
		}
	}

	buff[count] = '\0';

	return 1;
}

int preproc_includes(FILE *in, FILE *out)
{
	FILE *next=0;
	char *ptr=0;

	while(read_line(in,out))
	{
		if((ptr=strstr(buff,"#include")))
		{
			inc_level++;
			g_filelist[inc_level].linecount = 0;
			if(inc_level>MAX_INCLUDES)
			{
				printf("\n**Nested includes reaches maximum limit for %s",g_filelist[inc_level-1].filename);
				return 0;
			}
			
			if(!update_stack(ptr))
			{
				printf("\n**Couldn't open file %s",g_filelist[inc_level].filename);
				return 0;
			}

			if(!(next=fopen(g_filelist[inc_level].filename,"r")))
			{
				printf("\n**Couldn't open file %s",g_filelist[inc_level].filename);
				return 0;
			}

			if(preproc_includes(next,out))
			{
				fclose(next);
				next = 0;
				inc_level--;
				if(inc_level)
					fprintf(out,"\n%-*s#endinclude\n",inc_level,"\t");
				else
					fprintf(out,"\n#endinclude\n");
			}
		}
	}

	if(next)
		fclose(next);
	return 1;
}

void replace_text(char *ploc, char *macro, char *str)
{
	char *temp;
	char *ptr = &buff[0];
	char *head;

	temp = (char*)calloc(1,MAX_BUFFSIZE);
	head = temp;
	while(*ptr)
	{
		if(ptr==ploc)
		{
			memcpy(temp,str,strlen(str));
			temp += strlen(str);
			ptr += strlen(macro);
		}
		else
		{
			*temp = *ptr;
			++temp;
			++ptr;
		}
	}
	*temp = '\0';

	strcpy(buff,head);
	free(head);
}

int preproc_defines(FILE *in, FILE *out)
{
	char *ptr=0;
	char *word=0;
	PMACROLIST_t node=0;

	inc_level=0;
	g_filelist[inc_level].linecount=0;
	while(read_line(in,out))
	{
		if((ptr=strstr(buff,"#define")))
		{
			node = (PMACROLIST_t)calloc(1,sizeof(MACROLIST_t));
			word = strtok(ptr," \t");
			word = strtok(NULL, " \t");
			node->macroname = (char*)strdup(word);
			word = strtok(NULL,"\n");
			node->replacement = (char*)strdup(word);
			node->lineno = g_filelist[inc_level].linecount;

			if(g_pmaclist)
				node->next = g_pmaclist;
			g_pmaclist = node;
		}
	}

	if(g_pmaclist)
	{
		inc_level=0;
		g_filelist[inc_level].linecount = 0;
		in = fopen(lst_file,"w");
		rewind(out);
		while(read_line1(out,in))
		{
			node = g_pmaclist;
			while(node) 
			{
				if(g_filelist[inc_level].linecount != node->lineno)
				{
					if((ptr=strstr(buff,node->macroname)))
					{
						if(!isalpha(*(ptr+strlen(node->macroname))))
							replace_text(ptr,node->macroname, node->replacement);
					}
				}
				node = node->next;
			}
			fputs(buff,in);
		}
	}
	fclose(in);
	fclose(out);

	node = g_pmaclist;
	while(node)
	{
		g_pmaclist = node->next;
		if(node->macroname)
			free(node->macroname);
		if(node->replacement)
			free(node->replacement);
		free(node);
		node = g_pmaclist;
	}

	return 1;
}

int preproc()
{
	FILE *in, *out;


	if(!(in=fopen(inp_file,"r")))
	{
		printf("\n**Could not open file %s",inp_file);
		return 0;
	}

	strcpy(g_filelist[0].filename,inp_file);

	if(!(out=fopen(lst_file,"w")))
	{
		printf("\nCould not open file %s",lst_file);
		return 0;
	}

	if(!preproc_includes(in,out))
		return 0;

	fclose(in);
	fclose(out);

	if(!(in=fopen(lst_file,"r+")))
		return 0;

	if(!(out=tmpfile()))
		return 0;

	if(!preproc_defines(in,out))
		return 0;

	fclose(in);
	fclose(out);

	return 1;
}

void update_includelist(char *incpath)
{
	char *ptr=0;
	PPATHLIST_t inclist=0, listtail=0;

	listtail = g_pinclist;
	ptr = strtok(incpath,";\0");
	do {
		if(ptr)
		{
			inclist = (PPATHLIST_t)calloc(1,sizeof(PATHLIST_t));
			strcpy(inclist->path,ptr);
			inclist->next = 0;

			if(listtail)
				listtail->next = inclist;
			else
				g_pinclist = inclist;

			listtail = inclist;
		}
	} while((ptr=strtok(NULL,";\0")));
}

void update_maclist(char *macstr)
{
	char *ptr=0;
	PMACROLIST_t mac=0;

	ptr = strtok(macstr,"=\0");

	if(ptr)
	{
		mac = (PMACROLIST_t)calloc(1,sizeof(MACROLIST_t));
		mac->macroname = (char*)calloc(1,strlen(ptr)+1);
		strcpy(mac->macroname,ptr);
		mac->lineno=0;

		ptr = strtok(NULL,"=\0");
		if(ptr)
		{
			mac->replacement = (char*)calloc(1,strlen(ptr)+1);
			strcpy(mac->replacement,ptr);
		}

		if(g_pmaclist)
			mac->next = g_pmaclist;
		g_pmaclist = mac;
	}
}
