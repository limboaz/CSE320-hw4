#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main (void){
	printf("Please select from the following command:\nrun X\nhelp\nexit\ntype 'help' to see all available commands\n");
	//char * command = (char *)malloc(255);
	//scanf("%s", command);
	pid_t pid;

	while (1){
		char **args = (char**)malloc(sizeof(char*) * 2);
		char *cmd = (char *)malloc(127);
		fgets(cmd, 127, stdin);
		if (strcmp(cmd, "help") == 0){
			printf("At printing help. \n");
		}else if (strcmp(cmd, "exit") == 0){
			wait(NULL);
			exit(0);
		}else {	//when there may be more than one cmd from input 
			char *p = strtok(cmd, " ");
			cmd = p;	//cmd = "run"
			p = strtok(NULL, " ");
			char *f = p;	//f = filename
			p = strtok(NULL, " ");
			//*(args) = p;	//filename
			char path[127];
			char abs[3] = "../";
			strcat(path, abs);
			strcat(path, p);
			*(args) = path;
			*(args + 1) = NULL;
			if (strcmp(cmd, "run") == 0 && *(args) != NULL){
				
				execvp(f, args);
			}
		}
	
	}
}
