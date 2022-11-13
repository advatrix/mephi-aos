#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

void child_code() {
    pause();
    exit(0);
}

int main() {

    int child_pid = fork();

    if (!child_pid) {
        child_code();
    } else {
        int code;
        kill(child_pid, SIGUSR2);
        wait(&code);
        printf("wait: status %d\n", code);
    }
    return 0;
}