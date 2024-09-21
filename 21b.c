// Name : 21b.c
// Author : Ankit Kumar
/*Description :
Write two programs so that both can communicate by FIFO -Use two way communication.
*/
// Date : 20sept

#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void main
{
    char *s; 
    int fd;  
    long int size = 100;
    char *file = "./21a-fifo";
    while (1)
    {
        fd = open(file, O_RDONLY); 

        if (fd == -1)
            perror("Error");
        else
        {
            char buf;
            while (read(fd, &buf, 1) > 0)
                write(1, &buf, 1);
            write(1, "\n", 1);
            close(fd);
        }

        fd = open(file, O_WRONLY);
        if (fd == -1){
            perror("Error");
        }
        else
        {
            printf("enter message:\n");
            int l = getline(&s, &size, stdin);
            write(fd, s, l);
            close(fd);
        }


    }
}
