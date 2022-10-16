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

void do_write(int fd) {
    char d[80];
    printf("type what to write: ");
    scanf("%s", d);
    int r = write(fd, d, strlen(d));
    printf("read: %d error %d %s\n", r, errno, strerror(errno));
}

void do_read(int fd) {
    int n;
    printf("number of bytes to read: ");
    scanf("%d", &n);
    char *buf = calloc(n, sizeof(char));
    int r = read(fd, buf, n);
    printf("read: %d error %d %s\n", r, errno, strerror(errno));
    printf("%s\n", buf);
    printf("(read %d bytes)\n", n);
    free(buf);
}

void do_seek(int fd) {
    int offset, whence_raw, whence;
    printf("offset: ");
    scanf("%d", &offset);

    printf("whence (default: SEEK_SET):\n1 - SEEK_SET\n2 - SEEK_CUR\n3 - SEEK_END\n");
    scanf("%d", &whence_raw);

    switch (whence_raw) {
        case 2:
            whence = SEEK_CUR;
            break;
        case 3:
            whence = SEEK_END;
            break;
        default:
            whence = SEEK_SET;
            break;
    }
    int r = lseek(fd, offset, whence);
    printf("lseek: %d, error %d %s\n", r, errno, strerror(errno));
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s file [r|w]+\n", argv[0]);
        return 1;
    }
    const char *filename = argv[1];
    int permission_flag = get_permission_flag(argv[2]);

    int fd = open(filename, O_CREAT | permission_flag, 0666);
    printf("open: %d, error %d %s\n", fd, errno, strerror(errno));

    int action = 0;

    do {
        printf("choose action\n");
        printf("1 - write\n");
        printf("2 - read\n");
        printf("3 - seek\n");
        printf("* - exit\n");

        scanf("%d", &action);

        switch (action) {
            case 1:
                do_write(fd);
                break;
            case 2:
                do_read(fd);
                break;
            case 3:
                do_seek(fd);
                break;
            default:
                action = 0;
        }
    } while (action);

    int r = close(fd);
    printf("close: %d error %d %s\n", r, errno, strerror(errno));
    exit(0);
}

