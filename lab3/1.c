#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

void disp(int sig) {
    switch(sig) {
        case SIGINT:
            printf("No.\n");
            break;
        default:
            signal(sig, SIG_DFL);
    }
}

int main() {
    signal(SIGINT, disp);

    while(1)
        sleep(1);

    return 0;
}