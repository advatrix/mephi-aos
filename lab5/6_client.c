#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <unistd.h>

#define _GNU_SOURCE
#define MSG_LEN 32

extern int errno;

typedef struct msg_ds {
    long type;
    char data[MSG_LEN + 1];
} msg_ds;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s file message delay\n", argv[0]);
        exit(1);
    }

    char *ptr;
    unsigned int delay = strtol(argv[3], &ptr, 0);
    if (strlen(argv[3])!=ptr-argv[3]){
        fprintf(stderr, "%s: incorrect delay\n", argv[3]);
        exit(1);
    }

    key_t key_server = ftok(argv[1], 'a');
    int msqid_server = msgget(key_server, IPC_CREAT | 0666);

    int msqid_client = msgget(IPC_PRIVATE, IPC_CREAT | 0666);

    msg_ds request;
    msg_ds response;

    for (int i  = 0; ;i++) {
        strcpy(request.data, argv[2]);
        request.type = msqid_client;

        msgsnd(msqid_server, &request, sizeof(request), 0);
        sleep(delay);
        msgrcv(msqid_client, &response, sizeof(response), 0, 0);

        fprintf(stdout, "Iter %d\n", i);
        fprintf(stdout, "Type: %ld\n", response.type);
        fprintf(stdout, "Body: %s\n", response.data);

    }

    msgctl(msqid_client, IPC_RMID, 0);

    return 0;
}
