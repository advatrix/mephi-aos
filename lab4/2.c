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

//void read_from_channel(int fd, char* buf, size_t nbytes) {
//    int already_read = 0;
//    do {
//        already_read += read(fd, buf + already_read, nbytes - already_read);
//        printf("already read: %d\n", already_read);
//    } while(already_read < nbytes);
//}

int main() {
    int fd[2];
    // fd1: parent[1] --> child[0]
    // fd: parent[0] <-- child[1]

//    pipe(fd1);
   // pipe2(fd, O_NONBLOCK);
    pipe(fd);

    if (fork() == 0) {
        close(fd[0]);
        int n;

        while(1) {
            char buf[80] = {0};
            n = read(STDIN_FILENO, buf, 80);
            write(fd[1], buf, n);
        }

    } else {
        close(fd[1]);
        int r;

        do {
            char buf[80] = {0};
            r = read(fd[0], buf, 80);
            printf("%s", buf);
        } while(r);
        close(fd[0]);
        close(fd[1]);
    }

    return 0;
}