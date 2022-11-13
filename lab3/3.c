#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

int main() {

    signal(SIGCHLD, SIG_IGN);

    for (int i = 0; i < 10; i++) {
        if (fork() == 0) {
            // child code
            printf("child pid %d\n", getpid());
            sleep(10);
            exit(0);
        }
    }

    while(1) sleep(1);
    return 0;
}