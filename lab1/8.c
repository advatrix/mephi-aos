#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

extern int errno;

int copy(int src_fd, int dst_fd, int n_bytes) {
    int result = -1;
    void *src_buf = (void*)calloc(n_bytes, sizeof(char));
    int read_result = read(src_fd, src_buf, n_bytes);
    if (read_result >= 0)
        result = write(dst_fd, src_buf, n_bytes);
    free(src_buf);
    return result;
}

int main(int argc, char *argv[]) {
    int src_fd, dst_fd, n_bytes;

    if (argc != 3) {
        src_fd = 0;
        dst_fd = 1;
        n_bytes = 80;
    } else {
        const char *src_filename = argv[1];
        const char *dst_filename = argv[2];

        src_fd = open(src_filename, O_RDONLY);
        struct stat src_stat = {0};
        stat(src_filename, &src_stat);
        dst_fd = open(dst_filename, O_CREAT | O_WRONLY, src_stat.st_mode);
        n_bytes = src_stat.st_size;
    }

    copy(src_fd, dst_fd, n_bytes);
    if (argc == 3) {
        close(src_fd);
        close(dst_fd);
    }
    return 0;
}

