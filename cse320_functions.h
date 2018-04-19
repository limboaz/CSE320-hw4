#ifndef CSE320_FUNCTIONS_H
#define CSE320_FUNCTIONS_H


#include <errno.h>
#include <stdio.h>
#include <sys/types.h>

typedef struct addr_in_use{
	void * addr;
	int ref_count;
}addr_in_use;

typedef struct files_in_use{
	char *filename;
	int ref_count;
	FILE *f;
}files_in_use;


void *cse320_malloc(int);
void cse320_free(void *);
int Sem_init();
FILE *cse320_fopen(char *, char *);
void cse320_fclose(FILE *);
void cse320_clean();
pid_t cse320_fork();
unsigned int cse320_settimer(unsigned int);
void printFiles();
void printAddr();

#endif
