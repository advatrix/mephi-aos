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

void print_stats(struct msqid_ds ds) {
    struct ipc_perm perm = ds.msg_perm;
    printf("Ownership and permissions\n");
    printf("Key: %d\n", perm.__key);
    printf("Effective UID of owner: %d\n", perm.uid);
    printf("Effective GID of owner: %d\n", perm.gid);
    printf("Effective UID of creator: %d\n", perm.cuid);
    printf("Effective GID of creator: %d\n", perm.cgid);
    printf("Permissions: %o\n", perm.mode);
    printf("Sequence number: %u\n\n", perm.__seq);
    printf("Time of last msgsnd: %ld\n", ds.msg_ctime);
    printf("Time of last msgrcv: %ld\n", ds.msg_rtime);
    printf("Time of last change: %ld\n", ds.msg_ctime);
    printf("Current number of bytes in queue: %lu\n", ds.__msg_cbytes);
    printf("Current number of messages in queue: %lu\n", ds.msg_qnum);
    printf("Maximum number of bytes allowed in queue: %lu\n", ds.msg_qbytes);
    printf("PID of last msgsnd: %d\n", ds.msg_lspid);
    printf("PID of last msgrcv: %d\n", ds.msg_lrpid);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s file\n", argv[0]);
        exit(-1);
    }

    key_t key = ftok(argv[1], 'a');
    int msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) {
        printf("Unable to get message queue identifier\n");
        exit(errno);
    }
    printf("msqid: %d\n", msqid);

    msg_ds msg;

    int message_types[] = {1, 2, 3};
    const char* messages[] = {"type 1", "type 2", "type 3"};

    for (int i = 0; i < 3; i++) {
        msg.type = message_types[i];
        strcpy(msg.data, messages[i]);
        msgsnd(msqid, &msg, sizeof(msg), 0);
    }

    struct msqid_ds ds = {0};
    msgctl(msqid, IPC_STAT, &ds);
    print_stats(ds);

    return 0;
}
