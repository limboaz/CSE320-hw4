#include "cse320_functions.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main (void){
	Sem_init();
	//prompt user input
	char arg[20];
	while(1){
		fputs("Please select from the following: \nmalloc\nfopen\nclean\nfork\nprint\nexit\n", stdout);
		fgets(arg, 19, stdin);
		int i;
		for ( i = 0; i < 19; i++){
			if(arg[i] == '\n'){
				arg[i] = '\0';
				break;
			}
		}
		if (strcmp(arg, "malloc") == 0){
			fputs("please enter the number of bytes: ", stdout);
			int num;
			scanf(" %d", &num);
			cse320_malloc(num);
		}else if( strcmp(arg, "fopen") == 0){
			fputs("Please enter file name and mode: ", stdout);
			char fname[30];
			char fmode[10];
			scanf(" %s %s", fname, fmode);
			cse320_fopen(fname, fmode);
		}else if(strcmp(arg, "clean") == 0){
			cse320_clean();
		}else if(strcmp(arg, "fork") == 0){
			cse320_fork();
		}else if(strcmp(arg, "print") == 0){
			printAddr();
			printFiles();
		}else if(strcmp(arg, "exit") == 0){
			exit(0);
		}else{
			printf("illegal command. \n");
		}

	}

}
