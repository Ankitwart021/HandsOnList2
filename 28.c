// Name : 28.c
// Author : Ankit Kumar
/*Description : 
Write a program to change the exiting message queue permission. (use msqid_ds structure)
*/
// Date : 20sept

#include <sys/msg.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <time.h>
typedef struct mesg_buffer
{
    /* data */
    long mesg_type;
    char mesg_text[100];
} mesg_buffer;
int main(int argc, char const *argv[])
{
    /* code */
    mesg_buffer message;
    // generate unique no
    key_t key = ftok(".", 1); // projext path is current directory and project id=1
    // create massage queue using msgget
    //  msgget creates a message queue
    //  and returns identifier
    int msgid = msgget(key, 0666 | IPC_CREAT);
    struct msqid_ds buf;
    msgctl(msgid, IPC_STAT, &buf);
    struct ipc_perm msg_perm = buf.msg_perm; /* Ownership and permissions */
    printf("access permission %d\n", msg_perm.mode);
    buf.msg_perm.mode = 0776;
    msgctl(msgid, IPC_SET, &buf);
    

    struct msqid_ds cbuf;
    msgctl(msgid, IPC_STAT, &cbuf);
    struct ipc_perm u_msg_perm = cbuf.msg_perm; /* Ownership and permissions */
    printf("access permission %d\n", u_msg_perm.mode);
    return 0;
}
