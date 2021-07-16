#ifndef _ZPREPROC_H
#define _ZPREPROC_H

typedef struct _filelist_t		FILELIST_t, *PFILELIST_t;
typedef struct _pathlist_t		PATHLIST_t, *PPATHLIST_t;
typedef struct _macrolist_t		MACROLIST_t, *PMACROLIST_t;

#define MAX_INCLUDES 100
#define MAX_BUFFSIZE 512
#define INPUTFILE "input$.c"

struct _filelist_t
{
	char filename[MAX_BUFFSIZE];
	int linecount;
};

struct _pathlist_t
{
	char path[MAX_BUFFSIZE];
	PPATHLIST_t next;
};

struct _macrolist_t
{
	char *macroname;
	char *replacement;
	int lineno;

	PMACROLIST_t next;
};

int update_stack(char *buffer);
int preproc();
void update_includelist(char *incpath);
void update_maclist(char *macstr);

#endif
