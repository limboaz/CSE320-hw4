# Homework #4

Documentation for Part1


The part 1 file is main.c. An executable file is included in the repository with a name "part1". You can run it directly or compile it yourself. 



Documentation for "cse320_functions.h"


struct addr_in_use
	
	
	A structure that contains a list of memory blocks allocated by user in one application. The maximum amount of blocks is 25. 
	There are two struct members. One is the pointer to the address, another one is the reference count. 




struct files_in_use
	
	
	A structure that contains a list of files opened by the user. Maximum amount is 25. 
	There are three struct members: a string filename which stores the actual name of the file opened, an int reference count which counts how many times this file is referenced, a file pointer f which points to the file opened. 




The source file part2.c includes a memory block array addr[25] and an opened file list files[25]. 




void *cse320_malloc(int)
	
	
	Works similarly to malloc(). Additionally, this function will add the pointer to the memory block list of the program (addr) and increment the reference count accordingly. If the number of blocks exceed 25, the function will exit with -1 and free all the allocated memory and clean the file list as well.




void cse320_free(void *)
	
	
	Works similarly as free(). It will decrement the address reference count accordingly and clean up the cell in addr as well. The freed cell is reusable so there will be no fragmentation. 




int Sem_init()
	
	
	Initialize the semaphores for thread safety. This function MUST be used before any other functions from this header file are used. Returns 1 on succeed. 



FILE *cse320_fopen(char *, char *)
	
	
	Works similarly as fopen. However it can take non const char* as the first parameter. The function will return a file pointer to user. If the same file is opened multiple times though may be in different mode, the returned file pointer will be the same one. If the user tries to open more files that exceed the maximum amount, the function will exit with -1 and clean up memory and file list. 



void cse320_fclose(FILE *f)
	
	
	Works similarly to fclose(). Additionally, this function will clean the cell from the file list that the file passed in takes and make it reusable later. 



void cse320_clean()
	
	
	This void function will clean up all allocated memory and opened files for the program. It will also reset the whole memory block list addr[] and file list files[] to be empty so they will be ready for reuse. 



pid_t cse320_fork()
	
	
	This function works similarly as fork(). Additionally, it will enable the parent process to send signal to itself so it will reap all the terminated children every 5 seconds. The timer can be reset by cse320_settimer(), as further described below. It returns the process id twice, like fork(). 



unsigned int cse320_settimer(unsigned int)
	
	
	This function will allow user to reset the default timer for parent process to send signal. The return value is the number user entered. If the input is invalid (a negative value is input), the function will exit with -1. 



#The following are two helper functions to help with debugging. 



void printFiles()
	
	
	This function will print all the opened files currently in the program, with their index, name and reference count. 



void printAddr()
	
	
	This function will print all the allocated memory blocks with their index, pointer value and reference count. 




