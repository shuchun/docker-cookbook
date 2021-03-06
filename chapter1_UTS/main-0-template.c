/**
 *
 * a complete demo,to start /bin/bash at child process.
 * Usage:gcc main-0-template.c -o demo1 && ./demo1
 *
 */

#define _GUN_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>
#define STACK_SIZE (1024 * 1024)
static char child_stack[STACK_SIZE];
char* const child_args[] = {
	"/bin/bash",
	NULL
};
int child_main(void* arg);

/*
 * child process start shell
 */
int child_main(void* arg){
	printf(" - World !\n");
	execv(child_args[0],child_args);
	printf("Ooops\n");
	return 1;
}

/*
 * the main method,start position
 */
int main(){
	printf(" - Hello ?\n");
	int child_pid = clone(child_main,child_stack + 
		STACK_SIZE,SIGCHLD,NULL);
	waitpid(child_pid,NULL,0);
	return 0;
}
