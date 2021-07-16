#ifndef _SYMTAB_H

#include "zstruct.h"

typedef struct _sym_tag    SYM_TAB, *PSYM_TAB;

/* Symbol table structure */
struct _sym_tag 
{
	char *name;
	PIDENT_t pattrib;
	PSYM_TAB link;
};

/************************************************************************/
/* Interfaces                                                           */
/************************************************************************/
void init_symhash(void);
void add_symbol(PIDENT_t pattrib);
PIDENT_t get_symbol(char *symname);
void delete_symhash(int scope);

void print_symbol(PIDENT_t psym);

#endif
