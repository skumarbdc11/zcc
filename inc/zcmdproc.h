#ifndef _CMDPROC_H
#define _CMDPROC_H

typedef enum _cmdopt_e		CMDOPT_e;

enum _cmdopt_e
{
	VERBOSE,
	GENLST,
	INCSRC,
	
	INCLUDE,
	DEFINE,
	HELP,
};

int process_commands(int argc, void *argv[]);

#endif
