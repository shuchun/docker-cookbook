/**
 *
 * close write fd file and call EOF signal at parent process.
 * wait recive EOF signal at child process.
 * Usage:gcc main-1-uts.c -o demo2 && ./demo2 && hostname
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

//sync primitive
int checkpoint[2];
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
	char c;
	close(checkpoint[1]);
	//wait .....
	read(checkpoint[0],&c,1);
	printf(" - World !\n");
	//call set hostname 
	printf("Ooops\n");
	return 1;
}

/*
 * the main method,start position
 */
int main(){
	//init sync primitive
	pipe(checkpoint);
	printf(" - Hello ?\n");
	/*int child_pid = clone(child_main,child_stack + 
		STACK_SIZE,SIGCHLD | CLONE_NEWUTS | CLONE_NEWIPC,NULL);
	*/
	int child_pid = clone(child_main,child_stack+
		STACK_SIZE,SIGCHLD,NULL);
	//some damn long init job
	sleep(4);
	//signal "done"
	close(checkpoint[1]);
	waitpid(child_pid,NULL,0);
	return 0;
}
