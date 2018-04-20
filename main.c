#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#define XD 0

int main (void){
	
	pid_t pid;

	char *args[6];
	char cmd[127];
	while(1){
		printf("Please select from the following command:\nrun X\nhelp\nexit\ntype 'help' to see all available commands\n");
		fgets(cmd, 127, stdin);
		int i;
		for(i = 0; i < 127; i++){
			if (cmd[i] == '\n'){
				cmd[i] = '\0';
				break;
			}
		}
		if (strcmp(cmd, "help") == 0){
			printf("run X: X can be any executable with at most five parameters\nhelp\nexit\n");
		}else if (strcmp(cmd, "exit") == 0){
			wait(NULL);
			exit(0);
		}else {	//when there may be more than one cmd from input 
			char *p = strtok(cmd, " ");
			p = strtok(NULL, " ");
			
			int j;
			for (j = 0; j < 5 && p != NULL; j++){
				*(args + j) = p;
				p = strtok(NULL, " ");
			}

			*(args + j) = NULL;
			if (strncmp(cmd, "run", 3) == 0 && *(args) != NULL){
				
				if ((pid = fork()) == 0){
					execvp(*(args), args);
					char rpl[127];
					rpl[0] = '.';
					rpl[1] = '/';
					rpl[2] = '\0';
					strcat(rpl, *args);
					*args = rpl;
					execvp(rpl, args);
					exit(0);
				}
				waitpid(pid, NULL, XD);
			}
		}
	
	}
}
