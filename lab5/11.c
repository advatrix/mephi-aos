#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <time.h>

#define _GNU_SOURCE
#define MSG_LEN 32

extern int errno;

typedef struct msg_ds {
    long type;
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

    msg_ds msg;

    if (fork()) {
        while (1) {
            msg.type = 1;
            printf("%d\n", getpid());
            sleep(rand() % 5);
            msgsnd(msqid, &msg, sizeof(msg), 0);
            msgrcv(msqid, &msg, sizeof(msg), 2, 0);
        }
    } else {
        while (1) {
            msgrcv(msqid, &msg, sizeof(msg), 1, 0);
            printf("%d\n", getpid());
            sleep(rand() % 5);
            msg.type = 2;
            msgsnd(msqid, &msg, sizeof(msg), 0);
        }
    }

    remove_queues();
    return 0;
}
