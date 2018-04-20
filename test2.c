#include "cse320_functions.h"
#include <string.h>
#include <stdlib.h>

int main(void){
	Sem_init();
	int j;
	int * ptr;
	for (j = 0; j < 20; j++)
		 ptr = cse320_malloc(sizeof(int) * 2);
	ptr[0] = 10;
	ptr[1] = 444;
	//char name[20];
	//strcpy(name, "main.c");
	char m;
	int n;
	for ( m = 'a'; m <= 'm'; m++){
		char a = m;
		char b[2];
		b[0] = a;
		b[1] = '\0';
		FILE* f = cse320_fopen(b, "w+");
		//int i = fputs(files[(25 -('z' - m))].filename, stdout);
	}
	int t;
	pid_t pid[5];
	for( t = 0; t < 5; t++){
		
			pid[t] = cse320_fork();
		
	}
	
	if (pid[0] == 0) exit(0);

	while(1){
		;
	}
	cse320_clean();
	return 0;
}
