#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

extern int errno;

int copy(int n_bytes) {
    int src_fd = STDIN_FILENO;
    int dst_fd = STDOUT_FILENO;

    int result = -1;
    void *src_buf = (void*)calloc(n_bytes, sizeof(char));
    int read_result = read(src_fd, src_buf, n_bytes);
    if (read_result >= 0)
        result = write(dst_fd, src_buf, n_bytes);
    free(src_buf);
    return result;
}

int main(int argc, char *argv[]) {
    int n_bytes;

    if (argc != 3) {
        printf("usage: source_filename destination_filename\n");
        exit(EXIT_FAILURE);
    }

    const char *src_filename = argv[1];
    const char *dst_filename = argv[2];

    int src_fd = open(src_filename, O_RDONLY);
    struct stat src_stat = {0};
    stat(src_filename, &src_stat);
    int dst_fd = open(dst_filename, O_CREAT | O_WRONLY, src_stat.st_mode);
    n_bytes = src_stat.st_size;

    dup2(src_fd, STDIN_FILENO);
    dup2(dst_fd, STDOUT_FILENO);

    copy(n_bytes);

    close(src_fd);
    close(dst_fd);
    return 0;
}

