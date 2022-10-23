#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char * argv[], char * envp[]) {
    printf("process %s\n", argv[0]);
    printf("parameters\n");
    for (char** it = argv; *it; it++) {
        printf("%s\n", *it);
    }
    printf("env\n");
    for (char** it = envp; *it; it++) {
        printf("%s\n", *it);
    }


    exit(EXIT_SUCCESS);
}