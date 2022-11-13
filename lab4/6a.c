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
    int fd = open(argv[1], O_RDONLY);
    char buf[256];
    int r = read(fd, buf, 256);
    printf("Read %d bytes from channel: %s", r, buf);
    close(fd);
}