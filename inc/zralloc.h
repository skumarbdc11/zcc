#ifndef _ZRALLOC_H
#define _ZRALLOC_H

typedef struct _regnode_t		REGNODE_t, *PREGNODE_t;
typedef struct _arclist_t		ARCLIST_t, *PARCLIST_t;

/* Register graph node */
struct _regnode_t
{
	int pseudoreg;  /* pseudo register number */
	int colored;    /* whether it is colored */
	int reg;        /* actual register number assigned */

	int start;		/* start code record index */
	int end;		/* end code record index */

	PARCLIST_t parcs; /* pointer to the arcs */

	PREGNODE_t next; /* next register node */
};

/* Arc list */
struct _arclist_t
{
	PREGNODE_t node;  /* pseudo register node */

	PARCLIST_t next; /* next arc */
};

/*
 *	Interfaces
 */
int gcolor(PCR_t crblock);

#endif
