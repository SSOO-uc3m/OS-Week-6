#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Write a program in C that implements the command:
  without grandchildren

“ls | grep”.

*/

int main(int argc, char* argv[]) {
    int fd[2];
    pid_t pid1, pid2;
    if (pipe(fd) == -1) {
        return -1;
    }
    
    pid1 = fork();
    if (pid1 < 0) {
        return 2;
    }
    
    if (pid1 == 0) {
        //dup2(fd[1], STDOUT_FILENO);
        close(STDOUT_FILENO);
        dup(fd[1]);
        close(fd[0]);
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        exit(-1);
    }
    
    pid2 = fork();
  
    if (pid2 < 0) {
        return -1;
    }
    
    if (pid2 == 0) {
        //close(STDIN_FILENO);
        //dup(fd01]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("grep", "grep", "c", NULL);
        exit(-1);
    }
  
    close(fd[1]);  
  
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    
    return 0;

}