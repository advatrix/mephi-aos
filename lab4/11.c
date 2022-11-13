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

void do_action(char* name) {
    char* msg = calloc(13, sizeof(char));
    strcpy(msg, name);
    struct flock r_lock = {0}, w_lock = {0};

    while(1) {
        char buf[10] = {0};

        w_lock.l_type = F_WRLCK;
        w_lock.l_whence = SEEK_SET;
        w_lock.l_len = 0;
        w_lock.l_start = 0;

        r_lock.l_type = F_RDLCK;
        r_lock.l_whence = SEEK_SET;
        r_lock.l_len = 0;
        r_lock.l_start = 0;

//        r_lock.l_type = F_WRLCK;
//        while(fcntl(STDIN_FILENO, F_SETLK, &r_lock) == -1) ;
        w_lock.l_type = F_WRLCK;
        while(fcntl(STDOUT_FILENO, F_SETLK, &w_lock) == -1) ;

        int r = read(STDIN_FILENO, buf, 10);

        write(STDOUT_FILENO, strcat(msg, buf), sizeof(name) + r);

        w_lock.l_type = F_UNLCK;
        fcntl(STDOUT_FILENO, F_SETLK, &w_lock);
//        r_lock.l_type = F_UNLCK;
//        fcntl(STDIN_FILENO, F_SETLK, &r_lock);
//        sleep(1);
        strcpy(msg, name);

    }

    free(msg);
}

int main() {
    int r = fork();
    do_action(r == 0 ? "[c]" : "[p]");
}