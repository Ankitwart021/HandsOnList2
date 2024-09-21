// Name : 29.c
// Author : Ankit Kumar
// Description : Write a program to remove the message queue.
// Date : 20sept
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main()
{
    // generate unique no
    key_t key = ftok(".", 1); // projext path is current directory and project id=1
    // create massage queue using msgget
    //  msgget creates a message queue
    //  and returns identifier
    int msgid = msgget(key, 0666 | IPC_CREAT);
    struct msqid_ds buf;
    //remove msg queue using flag IPC_RMID
    msgctl(msgid, IPC_RMID, &buf);
    return 0;
}
