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
#include <sys/stat.h>


int main(int argc, char *argv[]) {
    const char* filename = argv[1];
    char digits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    if (fork() == 0) {
        // child
        int fd = open(filename, O_RDONLY);
        int r;
        char buf[1];
        while((r = read(fd, buf, 1) > 0)) printf("%s", buf);
        close(fd);
    } else {
        // parent
        int fd = open(filename, O_WRONLY | O_CREAT, 0666);

        struct flock lock = {0};
        lock.l_type = F_WRLCK;
        fcntl(fd, F_SETLK, &lock);

        for (int i = 0; i < 100; i++) write(fd, &digits[i % 10], 1);
        close(fd);
    }
}