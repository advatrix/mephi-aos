#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <signal.h>

#define _GNU_SOURCE
#define MSG_LEN 32

extern int errno;

typedef struct msg_ds {
    long type;
    long from;
    char data[MSG_LEN + 1];
} msg_ds;

int msqid;

void remove_queues() {
    msgctl(msqid, IPC_RMID, 0);
}

void disp(int sig) {
    if (sig == SIGINT) {
        remove_queues();
        exit(SIGINT);
    }
    signal(sig, SIG_DFL);
}

int main(int argc, char *argv[]) {
    signal(SIGINT, disp);

    key_t key = ftok(argv[0], 'a');
    msqid = msgget(key, IPC_CREAT | 0666);

    msg_ds request;
    msg_ds response;

    for(int i = 0;; i++) {
        msgrcv(msqid, &request, sizeof(request), 1, 0);

        printf("Got message (iter %d)\n", i);
        printf("Type: %ld\n", request.type);
        printf("Body: %s\n", request.data);

        response.type = request.from;
        strcpy(response.data, request.data);
        for (int i = 0; i < strlen(response.data); ++i)
            response.data[i]--;

        if (msgsnd(msqid, &response, sizeof(response), 0)) {
            printf("unable to send to client %ld\n", request.type);
            perror("msgsnd");
        } else {
            printf("Sent message\n");
            printf("Type: %ld\n", response.type);
            printf("Body: %s\n", response.data);
        }
    }

    remove_queues();
    return 0;
}
