#include "cse320_functions.h"
#include <unistd.h>
#include <stdlib.h>

addr_in_use addr[25];
files_in_use files[25];
int addr_cnt = 0;
int file_cnt = 0;

int add_to_addr(void * temp){
	int i;
	for (i = 0; i < 25; i++){
		if ( temp == addr[i].addr ){}
	}
	addr[addr_cnt].addr = temp;
	addr_cnt++;
	return addr_cnt;
}

int add_to_file(char *s){
	files[file_cnt].filename = s;
	files[file_cnt].ref_count++;
	file_cnt++;
	return file_cnt;
}


void *cse320_malloc(int size){
	void *temp = malloc(size);
	add_to_addr(temp);

}
