#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char * argv[]) {
    int src_fd, dst_fd, fork_result;
    ssize_t r;
    char* filename = "common";

    if (argc != 2) {
        printf("usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    src_fd = open(argv[1], O_RDONLY);
    fork_result = fork();

    dst_fd = open(filename, O_RDWR | O_CREAT, 0644);

    char buf[256];
    do {
        r = read(src_fd, buf, sizeof(buf));
        write(dst_fd, buf, r);
        memset(buf, '\0', sizeof(buf));
    } while (r == sizeof(buf));

    lseek(dst_fd, 0, SEEK_SET);

    if (fork_result) {
        int child_result;
        wait(&child_result);
        printf("parent result\n");
    } else {
        printf("child result\n");
    }

    do {
        r = read(dst_fd, buf, sizeof(buf));
        printf("%s", buf);
        memset(buf, '\0', sizeof(buf));
    } while(r == sizeof(buf));

    exit(EXIT_SUCCESS);
}