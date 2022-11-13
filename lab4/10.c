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
    char* msg = calloc(sizeof(name) + 10, sizeof(char));
    strcpy(msg, name);
    while(1) {
        char buf[10] = {0};
        int r = read(STDIN_FILENO, buf, 10);
        write(STDOUT_FILENO, strcat(msg, buf), sizeof(name) + r);
        strcpy(msg, name);
    }
}

int main() {
    int r = fork();
    do_action(r == 0 ? "[c]" : "[p]");
}