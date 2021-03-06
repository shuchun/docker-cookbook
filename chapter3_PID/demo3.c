/**
 *
 * a complete demo,use subprocess modify hostname
 * Usage:gcc main-1-uts.c -o demo2 && ./demo2 && hostname
 * exec demo2 file you will found the host name will modify
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
 * and set hostname
 */
int child_main(void* arg){
	printf(" -[%5d]  World !\n",getpid());
	//call set hostname 
	sethostname("centos7",12);
	execv(child_args[0],child_args);
	printf("Ooops\n");
	return 1;
}

/*
 * the main method,start position
 */
int main(){
	printf(" -[%5d] Hello ?\n",getpid());
	int child_pid = clone(child_main,child_stack + 
		STACK_SIZE,CONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID | SIGCHLD,NULL);
	waitpid(child_pid,NULL,0);
	return 0;
}
