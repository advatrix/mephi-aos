#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char * argv[]) {
    pid_t pid;

    pid = fork();
    switch(pid) {
        case -1:
            printf("fork failed\n");
            exit(EXIT_FAILURE);
        case 0:
            execvp(argv[1], argv + 1);
        default:
            break;
    }

    exit(EXIT_SUCCESS);
}