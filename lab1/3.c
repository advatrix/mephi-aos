#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

extern int errno;

int get_permission_flag(const char *permission_codes) {
    int r = strstr(permission_codes, "r") > 0;
    int w = strstr(permission_codes, "w") > 0;

    if (r && w) return O_RDWR;
    else if (r) return O_RDONLY;
    else if (w) return O_WRONLY;
    else return -1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s file [r|w]+\n", argv[0]);
        return 1;
    }
    const char *filename = argv[1];
    int permission_flag = get_permission_flag(argv[2]);

    int fd = open(filename, O_CREAT | permission_flag, 0444);
    printf("open: %s\n", strerror(errno));

    const char * msg = "abc\nabc\nabc";
    int msg_length = 11;
    write(fd, msg, msg_length);
    printf("write: %s\n", strerror(errno));
    close(fd);
    printf("close: %s\n", strerror(errno));

    fd = open(filename, O_RDONLY);
    printf("open: %s\n", strerror(errno));
    char buf[1024];
    int r = read(fd, buf, 1024);
    printf("read: %s\n", strerror(errno));
    if (r < 0) printf("Unable to read\n");
    else printf("Message:\n%s\n(read %d bytes)\n", buf, r);
    close(fd);

    fd = open(filename, O_RDWR);
    printf("open: %s\n", strerror(errno));
    close(fd);
    printf("close: %s\n", strerror(errno));
    exit(0);
}

