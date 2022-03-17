# Lab 6 Signals and Pipes

## Goals

- Practice with signal concepts.

- Practice with process communication using pipes.

- Handling system calls for signals and pipes in C.

## Statements

###  Exercise 01

Implement a C program in which a parent process creates a child process.

The parent, 10 seconds after the creation of the child, must send the SIGUSR1 signal to the child process, and then terminate its execution.

The child process, when it receives the signal, should display the following message on the screen: "SIGNAL RECEIVED" and the signal number and then terminate its execution.

###  Exercise 02

Implement a program that captures the SIGSEGV signal

- Print an error message.

- Put the default treatment back.

To raise the signal, it must write to position 0 in memory. Use a pointer for this.

###  Exercise 03

Implement a program in which the parent process creates a child.

The parent must capture the SIGUSR1 signal and the SIGCHLD signal. A different treatment must be done for each signal.

The son falls asleep for 2 seconds, sends the SIGUSR1 signal to the parent, and falls asleep for 3 seconds before finishing.

###  Exercise 04

Implement a program that waits 3 seconds for the user to press a key.

If the 3 seconds pass without pressing anything, the program ends.

###  Exercise 05

Implement a program that implements an infinite loop that does the following:

- Set a 3 second alarm.

- Pause the process.

It should capture the alarm signal and display a message with the signal number.

The process should continue until CTRL-C is pressed on the keyboard.
 
###  Exercise 06

Write a program in C that implements the command:

“ls | wc”.


###  Exercise 07

Write a C program that allows 2 programs (prog_esc and prog_lec), which by default use standard input and output to write or read the data
they use, to communicate through a pipe created by the parent of both processes.

The prog_lec program asks for a string using STDIN and writes it.

The prog_esc just writes a string to the STDOUT standard output.
