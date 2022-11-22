#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#define _GNU_SOURCE
#define MSG_LEN 32

extern int errno;

typedef struct msg_ds {
    long type;
    char data[MSG_LEN + 1];
} msg_ds;

int main(int argc, char *argv[]) {
    key_t key = ftok(argv[0], 'a');
    int msqid = msgget(key, IPC_CREAT | 0666);
    msg_ds request;
    msg_ds response;


    for(int i = 0;; i++) {
        msgrcv(msqid, &request, sizeof(request), 0, 0);

        printf("Got message (iter %d)\n", i);
        printf("Type: %ld\n", request.type);
        printf("Body: %s\n", request.data);

        response.type = 1;
        strcpy(response.data, request.data);
        for (int i = 0; i < strlen(response.data); ++i)
            response.data[i]--;

        printf("Sent message\n");
        printf("Type: %ld\n", response.type);
        printf("Body: %s\n", response.data);

        msgsnd(request.type, &response, sizeof(response), 0);
    }

    msgctl(msqid, IPC_RMID, 0);
    return 0;
}
