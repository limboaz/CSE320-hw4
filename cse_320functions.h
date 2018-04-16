#include <errno.h>

struct addr{
	void * addr;
	int ref_count;
}addr_in_use = {NULL, 0};
typedef struct addr addr_in_use;

struct files{
	char *filename;
	int ref_count;
}files_in_use = {NULL, 0};
typedef struct files files_in_use;

#define MAX_CNT 25;

void errAddr(){
	
}

void errFiles(){

}
