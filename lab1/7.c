#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

extern int errno;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    struct stat statbuf = {0};
    stat(argv[1], &statbuf);

    printf("ID of device containing file: %lu\n", statbuf.st_dev);
    printf("Inode: %lu\n", statbuf.st_ino);
    printf("File type and mode: %u\n", statbuf.st_mode);
    printf("Number of hard links: %lu\n", statbuf.st_nlink);
    printf("Owner user ID: %u\n", statbuf.st_uid);
    printf("Owner group ID: %u\n", statbuf.st_gid);
    printf("Device ID (if special file): %lu\n", statbuf.st_rdev);
    printf("Total size, bytes: %lu\n", statbuf.st_size);
    printf("I/O block size: %lu\n", statbuf.st_blksize);
    printf("Blocks: %lu\n", statbuf.st_blocks);
    printf("Time of last access: %ld\n", statbuf.st_atim.tv_sec);
    printf("Time of last modification: %ld\n", statbuf.st_mtim.tv_sec);
    printf("Time of last status change: %ld\n", statbuf.st_ctim.tv_sec);

    return 0;
}

