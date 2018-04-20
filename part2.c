#include "cse320_functions.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <wait.h>
#include <semaphore.h>
#include <pthread.h>

addr_in_use addr[25];
files_in_use files[25];

unsigned int sec = 5;

int addr_cnt = 0;
int file_cnt = 0;

sem_t ad, file;

int Sem_init(){		//tell user to call it first  add it to header
	sem_init(&ad, 0, 1);
	sem_init(&file, 0, 1);
}

int add_to_addr(void * temp){
	int added = 0;
	int i;
	for (i = 0; i < 25; i++){	//check if already referenced
		if ( temp == addr[i].addr ){
			addr[i].ref_count++;
			added = 1;	//existing address
			return added;
		}
	}
	if ( added == 0 && addr_cnt < 25){
		addr[addr_cnt].addr = temp;
		addr[addr_cnt].ref_count = 1;
		added = 2;	//new address
		addr_cnt++;
	}else if ( added == 0){
		free(temp);
		sem_post(&ad);
		cse320_clean();
		exit(-1);
	}
	return added;
}

FILE *add_to_files(const char *s, char *mode){
	char *fname = (char *)malloc(127);
	fname[0] = '\0';
	strcpy(fname, s);
	
	int added = 0; 
	FILE *f;
	int i;
	for (i = 0; i < 25; i++){
		if(files[i].filename != NULL){
			if(strcmp(fname, files[i].filename) == 0){
				files[i].ref_count++;
				f = files[i].f;
				added = 1;
				break;
			}
		}
	}
	if (added == 0 && file_cnt < 25){
		files[file_cnt].filename = fname;
		files[file_cnt].ref_count = 1;
		f = fopen(s, mode);
		files[file_cnt].f = f;
		file_cnt++;
		added = 2;
	}else if (added == 0){
		sem_post(&file);
		free(fname);
		cse320_clean();
		exit(-1);
	}
	return f;
}


void *cse320_malloc(int size){
	void *temp = malloc(size);
	sem_wait(&ad);
	add_to_addr(temp);
	sem_post(&ad);
	return temp;
}

void cse320_free(void *p){
	int freed = 0;
	int i;
	sem_wait(&ad);
	for ( i = 0; i < 25; i++){
		if (addr[i].addr == p && addr[i].ref_count > 0){
			addr[i].addr = NULL;
			addr[i].ref_count --;
			free(p);
			freed = 1;
			break;
		}else if(addr[i].addr == p){
			fputs("Free: Double free attempt\n", stdout);
			errno = EADDRNOTAVAIL;
			exit(-1);
		}
	}
	sem_post(&ad);
	if (freed == 0){
		fputs("Free: Illegal address\n", stdout);
		errno = EFAULT;
		exit(-1);
	}
}

FILE *cse320_fopen( char *s, char *mode ){
	sem_wait(&file);
	FILE *f = add_to_files(s, mode);
	sem_post(&file);
	return f;
}

void cse320_fclose(FILE *f){
	int closed = 0;
	int i;
	sem_wait(&file);
	for ( i = 0; i < 25; i++){
		if( f == files[i].f && files[i].ref_count > 0){
			files[i].ref_count--;
			if(files[i].ref_count == 0){
				fclose(f);
			}
			closed = 1;
			break;
		
		}else if ( f == files[i].f ){
			fputs("Close: Ref count is zero\n", stdout);
			closed = 2;
			errno = EINVAL;
			exit(-1);
		}
	}
	sem_post(&file);
	if ( closed == 0 ){
		fputs("Close: Illegal filename\n", stdout);
		errno = ENOENT;
		exit(-1);
	}
}

void cse320_clean(){
	//clean the addrs
	int i;
	int freed = 0;
	int closed = 0;
	sem_wait(&ad);
	sem_wait(&file);
	for ( i = 0; i < 25; i++ ){
		if (addr[i].ref_count > 0){
			free(addr[i].addr);
			addr[i].addr = NULL;
			addr[i].ref_count = 0;
			addr_cnt = 0;
			freed++;
		}
		if (files[i].ref_count > 0){
			fclose(files[i].f);	
			free(files[i].filename);
			files[i].filename = NULL;
			files[i].f = NULL;
			files[i].ref_count = 0;
			file_cnt = 0;
			closed++;
		}

	}
	sem_post(&ad);
	sem_post(&file);
}

void handler(int sig){
	alarm(sec);
	while(wait(NULL) != -1);
	//alarm(sec);
}

unsigned int cse320_settimer(unsigned int t){
	sec = t;
	return sec;
}

pid_t cse320_fork(){
	pid_t pid;
	
	signal(SIGALRM, handler);
	if ((pid = fork()) == 0){
		
	} else {
		alarm(sec);
	}
	
	return pid;
}

//debug helpers
void printAddr(){
	int i;
	for (i = 0; i < 25 && addr[i].addr != NULL; i++){
		printf("NO: %d ADDR: %p CNT: %d\n", i, addr[i].addr, addr[i].ref_count);
	}
}

void printFiles(){
	int i;
	for (i = 0; i < 25 && files[i].f != NULL; i++){
		printf("NO: %d NAME: %s CNT:%d\n", i, files[i].filename, files[i].ref_count);
	}
}
