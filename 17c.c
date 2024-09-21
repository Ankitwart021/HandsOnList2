// Name : 17c.c
// Author : Ankit Kumar
// Date : 20sept
/*Description : 
    Write a program to execute ls -l | wc.
    a. use dup
    b. use dup2
    c. use fcntl
*/

// d3=fcntl(fd, F_DUPFD, n); assigne fd greater than or equal to n

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

void main()
{
    int pipefd[2];
    pid_t cid;

    if (pipe(pipefd) == -1)
    {
        printf("ERROR");
    }
    else
    {
        cid = fork();
        if (cid == 0)
        {
            // closing standard output
            close(0);
            // reassigning stdin to pipe reading end;
            // dup2 will reassign pipefd[0] to 0 as it is lowest avalible fd from 0.so now pipefd[0] will act as STDIN
            fcntl(pipefd[0], F_DUPFD, 0);
            close(pipefd[1]); // closing unused pipe writing end
            execl("/usr/bin/wc", "wc", NULL);
        }
        else
        {
            close(1); // closing stdout
            // reassigning stdout to pipe writing end
            // fcntl will reassign pipefd[1] to 1(STDOUT) as it is lowest avalible fd from 1. so now pipefd[1] will act as STDOUT
            fcntl(pipefd[1], F_DUPFD, 1);
            close(pipefd[0]); // closing unused reading end

            execl("/usr/bin/ls", "ls -l", "-l", NULL);
        }
    }
}
