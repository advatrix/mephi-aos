#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>

void disp(int sig) {
    if (sig == SIGINT) printf("got SIGINT\n");
    else signal(sig, SIG_DFL);
}

int main() {
    signal(SIGINT, disp);

    sigset_t sigset;
    sigaddset(&sigset, SIGINT);
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    printf("doing something...\n");
    sleep(5);
    printf("finish doing.\n");

    sigprocmask(SIG_UNBLOCK, &sigset, NULL);
    sleep(1);
    printf("exiting\n");
    return 0;
}