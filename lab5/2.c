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
    if (argc != 3) {
        fprintf(stderr, "Usage: %s msq_id msg_type\n", argv[0]);
        exit(1);
    }

    char *ptr;

    int msqid = strtol(argv[1], &ptr, 0);
    if (strlen(argv[1])!=ptr-argv[1]){
        fprintf(stderr, "%s: incorrect message queue id\n", argv[1]);
        exit(1);
    }

    long msg_type = strtol(argv[2], &ptr, 0);
    if (strlen(argv[2])!=ptr-argv[2]){
        fprintf(stderr, "%s: incorrect message type\n", argv[2]);
        exit(1);
    }

    msg_ds msg = {0};
    msgrcv(msqid, &msg, sizeof(msg), msg_type, 0);

    printf("%s\n", msg.data);

    return 0;
}
