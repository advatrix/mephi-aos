#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <time.h>


int main() {
    int fd[2];
    pipe(fd);

    if (fork() == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execl("./4e", "./4e", NULL);
    } else {
        close(fd[1]);
        int r;
        char buf[80] = {0};
        do {
            memset(buf, 0, 80);
            r = read(fd[0], buf, 80);
            printf("%s", buf);
        } while(r);
        close(fd[0]);
    }

    return 0;
}