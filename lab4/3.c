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
    int fd[2], fd_rev[2];

    // fd: parent[0] <-- child[1]
    // fd_rev: parent[1] --> child[0]

    pipe2(fd, O_NONBLOCK);
    pipe2(fd_rev, O_NONBLOCK);

    if (fork() == 0) {
        close(fd[0]);
        close(fd_rev[1]);
        int n, r;
        char buf[80] = {0};
        while(1) {
            memset(buf, 0, 80);
            n = read(STDIN_FILENO, buf, 80);
            write(fd[1], buf, n);
            memset(buf, 0, 80);
            r = read(fd_rev[0], buf, 80);
            if (r > 0) printf("Child: %s", buf);
        }
        close(fd[1]);
        close(fd_rev[0]);
    } else {
        close(fd[1]);
        close(fd_rev[0]);
        int r;

        do {
            char buf[80] = {0};
            r = read(fd[0], buf, 80);
            if (r > 0) {
                printf("Parent: %s", buf);
                write(fd_rev[1], buf, r);
            }
        } while(r);
        close(fd[0]);
        close(fd_rev[1]);
    }

    return 0;
}