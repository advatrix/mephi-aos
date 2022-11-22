#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#define MSG_LEN 32

extern int errno;

typedef struct msg_ds {
    long type;
    char data[MSG_LEN + 1];
} msg_ds;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s msq_id\n", argv[0]);
        exit(1);
    }

    char *ptr;

    int msqid = strtol(argv[1], &ptr, 0);
    if (strlen(argv[1])!=ptr-argv[1]){
        fprintf(stderr, "%s: incorrect message queue id\n", argv[1]);
        exit(1);
    }

    if (msgctl(msqid, IPC_RMID, 0)) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
