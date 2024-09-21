// Name : 15.c
// Author : Ankit Kumar 
/*Description : 
    Write a simple program to send some data from parent to the child process.
*/
// Date : 20sept

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int pipefd[2];
    pid_t cpid;
    char buf;
    char s[10];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0)
    { /* Child reads from pipe */
        sleep(5);
        close(pipefd[1]); /* Close unused write end */

        // display from kernal using pipes reading end in child
        printf("display in child \n");
        while (read(pipefd[0], &buf, 1) > 0)
            write(1, &buf, 1);

        write(1, "\n", 1);
        close(pipefd[0]); /* Close unused read end */
    }
    else
    { /* Parent writes argv[1](message) to pipe */

        printf("writing in pipe from parent process\n");
        scanf("%s", s);
        close(pipefd[0]); /* Close unused read end */
        write(pipefd[1], s, strlen(s));
        close(pipefd[1]); /* Reader will see EOF */
        wait(0);          /* Wait for child */
    }
}
