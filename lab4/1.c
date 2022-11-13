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
    int fd1[2], fd2[2];
    // fd1: parent[1] --> child[0]
    // fd2: parent[0] <-- child[1]

    pipe(fd1);
    pipe(fd2);

    if (fork() == 0) {
        close(fd1[1]);
        close(fd2[0]);

        char phrase[1024] = {0};
        read(fd1[0], phrase, 1024);
        printf("Parent: %s\n", phrase);

        const char* reply = "Nooooooo!";
        write(fd2[1], reply, strlen(reply));
        close(fd1[0]);
        close(fd2[1]);
        
    } else {
        close(fd1[0]);
        close(fd2[1]);
        const char* buf = "I am your father!";
        write(fd1[1], buf, strlen(buf));

        char reply[1024] = {0};
        read(fd2[0], reply, 1024);
        printf("Child: %s\n", reply);
        close(fd1[1]);
        close(fd2[0]);
        
    }

    return 0;
}
