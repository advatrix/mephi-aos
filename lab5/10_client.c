#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

#define _GNU_SOURCE
#define MSG_LEN 32

extern int errno;

typedef struct msg_ds {
    long type;
    long from;
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

    key_t key = ftok(argv[1], 'a');
    int msqid = msgget(key, 0666);


    msg_ds request;
    msg_ds response;

    for (int i  = 0; ;i++) {
        strcpy(request.data, argv[2]);
        request.type = 1;
        request.from = getpid();

        if(msgsnd(msqid, &request, sizeof(request), 0)) {
            printf("unable to send to server\n");
            perror("msgsnd");
            exit(1);
        }
        sleep(delay);
        msgrcv(msqid, &response, sizeof(response), getpid(), 0);

        fprintf(stdout, "Iter %d\n", i);
        fprintf(stdout, "Type: %ld\n", response.type);
        fprintf(stdout, "Body: %s\n", response.data);

    }

    return 0;
}
