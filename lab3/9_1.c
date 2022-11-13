#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>

void child_disp(int sig) {
    if (sig == SIGALRM) {
        printf("child got alarm\n");
    }
    else signal(sig, SIG_DFL);
}

void child_code() {
    signal(SIGALRM, child_disp);
    alarm(1);
    pause();
    exit(0);
}

int main() {

    int child_pid;

    if ((child_pid = fork()) == 0) {
        child_code();
    } else {
        int code;
//        sleep(1);
//        kill(child_pid, SIGUSR1);
        wait(&code);
        printf("wait: status %d\n", code);
    }
    return 0;
}