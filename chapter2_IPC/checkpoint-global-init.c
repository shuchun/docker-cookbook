/**
 *
 * set a event to close in parent process,
 * when process was closed will return EOF signal.
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

//global status
int checkpoint[2];
//[parent] init
pipe(checkpoint);
