#ifndef _REGISTER_H
#define _REGISTER_H

typedef struct _regtab_t	REGTAB_t, *PREGTAB_t;
typedef enum _status_e		STATUS_e;

enum _status_e { USED, FREE };

struct _regtab_t
{
	int number;		/* register number */
	STATUS_e status;		/* used flag */
	char name[4];	/* name of the register */
};


PLIST_t newreg(char sign, int size);
PLIST_t spreg();
PLIST_t returnreg();
int get_freereg();
int get_r13reg();
void setreg_used(int regnum);
void free_registers();
void free_r13reg();

#endif
