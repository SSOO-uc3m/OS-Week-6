#include "week_06.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>  

/* ##############################*/
/*                               */
/* problem02 auxiliary functions */
/*                               */
/* ##############################*/

// add function to capture the signal SIGSEGV

// execute de the dafault action of SIGSEGV

/* ##############################*/
/*                               */
/* problem03 auxiliary functions */
/*                               */
/* ##############################*/

// add function to capture the signal SIGUSR1

// print time passed

// add function to capture the signal SIGCHLD

/* ##############################*/
/*                               */
/* problem04 auxiliary functions */
/*                               */
/* ##############################*/

const int TIME=3;
const int nMax = 10;
const int nMin = 1;

bool endTime = false;

// add function to capture the signal SIGALRM

// endTime flag put to true

// print time passed

#define ALARM_TIME 3

// add function to capture the signal SIGALRM

int exercise01 (){
    int pid;
    
    // create a mask of signals to block during the handler
    
    // create an empty set of signals

	// create a child process
	
	// parent wait SECONDS
	
	// parent send signal SIGUSR1
	
	// parent exit
	
	// child we specify the action to perform for SIGUSR1
	
	// child blocked until the signal is received
	
	// child exit
	

    
}

int exercise02 (){
    int *p;
	
	// custom handler for SIGSEGV
	
	// check if there is an error installing the handler 
	
    printf ("I have already placed the handler\n");
    p=0;
    printf ("I am going to put a value in a pointer to which I have not reserved memory\n");
    *p=5; 
}

int exercise03 (){
	
	// create two mask of signals add a custom handler

	// create a child process

	// child wait SECONDS_WAIT_1
	
	// child send SIGUSR1 signal to his parent
	
	// child wait SECONDS_WAIT_2

	// parent create a mask of signals to capture SIGUSR1 during the handler and an empty set of signals


	// parent create a mask of signals to capture SIGCHLD during the handler and an empty set of signals

	// parent blocked until a signal is received (SIGUSR1)

	// parent blocked until the signal is received (SIGCHLD)


}

int exercise04 (){
    int n;   

	
	// create a mask of signals to block during the handler
    
    // create an empty set of signals
	
	// set ALARM for TIME seconds
	
	//if (signal(SIGALRM, alarmGoesOff) == SIG_ERR) exit(-1);

	// ask a number to the user
	
	// if endTime is true, n will have a random value
	
	// print the number read
	
	exit(0);
}

 int exercise05() {

	// add an infinite loop
	 
	// add a custom handler for SIGALRM
	
	// check if there is an error installing the handler 
		
	// set an alarm for ALARM_TIME seconds
	
	// block the process until any signal is received 

 }

int exercise06 ()
{
    
    int myPipe[2]; 
    pid_t childLs, childWc;

     // establish the pipe 
		
	// create the child process	childLs    
	
    // childLs process  changed the standard outlet for the pipe 
	
	// childLs execute ls command    

    // parent process  changed the standard input for the pipe 

	// create the child process	childWc

	// childWc execute wc command    
	
	// parent process wait for both childs to finish
    
	
    return 0 ;
}