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
/* problem01 auxiliary functions */
/*                               */
/* ##############################*/

void receivedSignal(int s) { printf("received signal %d\n", s); }

/* ##############################*/
/*                               */
/* problem02 auxiliary functions */
/*                               */
/* ##############################*/

void capturar_senyal(int senyal) {
  printf("Error: illegal memory usage\n");
  signal(SIGILL, SIG_DFL);
}

// add function to capture the signal SIGSEGV

// execute de the dafault action of SIGSEGV

/* ##############################*/
/*                               */
/* problem03 auxiliary functions */
/*                               */
/* ##############################*/

// add function to capture the signal SIGUSR1

// add function to capture the signal SIGCHLD
void childDeath(int s) { printf("Child has died\n"); }

/* ##############################*/
/*                               */
/* problem04 auxiliary functions */
/*                               */
/* ##############################*/

const int TIME = 3;
const int nMax = 10;
const int nMin = 1;

bool endTime = false;

// add function to capture the signal SIGALRM

// endTime flag put to true

// print time passed

/* ##############################*/
/*                               */
/* problem05 auxiliary functions */
/*                               */
/* ##############################*/

#define ALARM_TIME 3

// add function to capture the signal SIGALRM

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

int exercise04() {
  int n;

  // create a mask of signals to block during the handler

  // create an empty set of signals

  // set ALARM for TIME seconds

  // if (signal(SIGALRM, alarmGoesOff) == SIG_ERR) exit(-1);

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