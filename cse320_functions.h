#include <errno.h>
#include <stdio.h>

typedef struct addr_in_use{
	void * addr;
	int ref_count;
}addr_in_use;

typedef struct files_in_use{
	char *filename;
	int ref_count;
}files_in_use;

#define MAX_CNT 25;

void *cse320_malloc(int);
void cse320_free(void *);
FILE *cse320_fopen(char *, char *);
void cse320_fclose(FILE *);
int cse320_clean();
