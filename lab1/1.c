#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

extern int errno;
// deprecated; use strerror
// extern const char * sys_errlist[] 
int main(int argc, char *argv[]) {
	const char *filename = argv[1];
	int fd = open(filename, O_RDWR);

	perror("open");
	printf("errno: %d\n", errno);
	// printf("sys_errlist[%d]: %s", errno, sys_errlist[errno]);
	printf("strerror(%d): %s", errno, strerror(errno));
	if (fd >= 0) close(fd);
	return 0;
}
