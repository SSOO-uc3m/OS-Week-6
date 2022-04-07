#include "week_06.h"
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


/* ##############################*/
/*                               */
/* problem01                     */
/*                               */
/* ##############################*/


void receivedSignal(int s) { 
  printf("received signal %d\n", s); 
  }

int exercise01() {
  int pid;
  int status;
  // create a mask of signals to block during the handler

  // create a mask of signals to block during the handler
  struct sigaction act;
  act.sa_handler = receivedSignal;
  act.sa_flags = 0;
  sigemptyset(&(act.sa_mask)); // create an empty set of signals

  // create a child process
  pid = fork();

  if (pid > 0) {
    printf("i'm the parent process, and I'm going to sleep 10 s\n");

    // parent wait SECONDS
    sleep(10);
    // parent send signal SIGUSR1
    printf("send signal for my child\n");

    kill(pid, SIGUSR1);
    printf("i'm the parent process, waiting for my child\n");

    waitpid(pid, &status,
            0); // wait for the child process and get their finish status
                // parent exit
    printf("i'm the parent process, i'm going to exit\n");

    exit(0);
  }
  if (pid == 0) {
    printf("i'm the child  process, and I'm going to be blocked\n");

    // child we specify the action to perform for SIGUSR1
    sigaction(SIGUSR1, &act, NULL);
    // child blocked until the signal is received
    pause();
    // child exit
    printf("i'm the child process, received signal, i'm going to exit\n");

    exit(0);
  }
}

/* ##############################*/
/*                               */
/* problem02                     */
/*                               */
/* ##############################*/


void capturar_senyal(int senyal) {
  printf("Error: illegal memory usage\n");
  signal(SIGILL, SIG_DFL);
}

int exercise02() {
  int *p;

  // custom handler for SIGSEGV
  if (signal(SIGILL, capturar_senyal) ==
      SIG_ERR) { // check if there is an error installing the handler

    perror("Error while installing the handler");
    exit(-1);
  }
  printf("I have already placed the handler\n");

  p = 0;
  printf("I am going to put a value in a pointer to which I have not reserved "
         "memory\n");
  *p = 5;
}

/* ##############################*/
/*                               */
/* problem03                     */
/*                               */
/* ##############################*/

void childDeath(int s) { 
  printf("Child has died\n"); 
  }

int exercise03() {

  // create two mask of signals add a custom handler
  struct sigaction sa1, sa2;
  int pid;
  // create a child process
  pid = fork();

  if (pid == 0) {
    // child wait 2 seconds
    sleep(2);

    // child send SIGUSR1 signal to his parent
    kill(getppid(), SIGUSR1);
    // child wait 3 seconds
    sleep(3);

    exit(0);
  } else if (pid > 0) {
    // parent create a mask of signals to capture SIGUSR1 during the handler and
    // an empty set of signals
    sa1.sa_handler = SIGUSR1;
    sa1.sa_flags = 0;
    sigaction(SIGUSR1, &sa1, NULL);

    // parent create a mask of signals to capture SIGCHLD during the handler and
    // an empty set of signals
    sa2.sa_handler = childDeath;
    sa2.sa_flags = 0;
    sigaction(SIGCHLD, &sa2, NULL);

    // parent blocked until a signal is received (SIGUSR1)
    pause();

    // parent blocked until the signal is received (SIGCHLD)
    waitpid(pid, NULL, 0);
    // wait(NULL);
    exit(0);
  }
}

const int TIME = 3;
const int nMax = 10;
const int nMin = 1;

bool endTime = false;

void alarmGoesOff (int s){
	  printf ("The alarm signal %d has arrived: \n",s);
	  endTime=1;
}

int exercise04() { 


  int n;   
  
  // create a mask of signals to block during the handler
  struct sigaction sa;
	sa.sa_handler = alarmGoesOff;
	sa.sa_flags=0;
  // create an empty set of signals
	sigemptyset (&(sa.sa_mask));
  // set ALARM for TIME seconds
	sigaction (SIGALRM, &sa, NULL);
	//if (signal(SIGALRM, alarmGoesOff) == SIG_ERR) exit(-1);

	alarm(TIME);
		printf ("Write  a number (you have got %d seconds) \n",TIME );
		scanf ("%d",&n);
		if (endTime){
			srand(time(0));
			n = rand()%((nMax+1)-nMin) + nMin;
			printf ("Time is up, the number will be %d\n",n );
		}		
		else {
			printf ("number %d has been read\n",n );
		}
	exit(0);
  

  exit(0);
}

/* ##############################*/
/*                               */
/* problem05                     */
/*                               */
/* ##############################*/

#define ALARM_TIME 3

void alarmGoesOff2(int signal) {

	printf("Alarm %d \n", signal);
 
} 

int exercise05() {

for(;;){
	if (signal(SIGALRM, alarmGoesOff2) == SIG_ERR) {
		perror("Error while installing a SIGALRM handler.\n");
		exit(-1);	
	}
	alarm(ALARM_TIME);           /* start the timer */ 
	pause();            /* next caught signal wakes us up */ 
	} 
}

int exercise06() {

  int myPipe[2];
  pid_t childLs, childWc;

  if (pipe(myPipe) < 0) {
    perror("error pipe");
    exit(-1);
  }

  childLs = fork();

  if (childLs < 0) {
    exit(-1);
  }

  if (childLs == 0) { // childLs process

    close(STDOUT_FILENO);
    dup(myPipe[STDOUT_FILENO]);
    close(myPipe[STDOUT_FILENO]);
    close(myPipe[STDIN_FILENO]);

    execlp("ls", "ls", NULL);
    exit(-1);
  }

 
  childWc = fork();
  
   if (childWc < 0) {
    exit(-1);
    }

  if (childWc == 0) {
    
    close(STDIN_FILENO);
    dup(myPipe[STDIN_FILENO]);
    close(myPipe[STDIN_FILENO]);
    close(myPipe[STDOUT_FILENO]);
    // redirection
    // close(STDOUT_FILENO);
    // open(file,O_RDWR|O_CREAT,0660);
  	// creat(file,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    execlp("wc", "wc", NULL);
    exit(-1);
  }

   close(myPipe[1]);  
  
   waitpid(childLs, NULL, 0);
   waitpid(childWc, NULL, 0);

  return 0;
}