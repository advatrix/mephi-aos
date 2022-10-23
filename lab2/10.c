#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char * argv[], char * envp[]) {
    int fr = fork();

    if (fr) {
        printf("parent process\n");
        printf("parameters\n");
        for (char** it = argv; *it; it++) {
            printf("%s\n", *it);
        }
        printf("env\n");
        for (char** it = envp; *it; it++) {
            printf("%s\n", *it);
        }

    } else {
        int er = execvp(argv[1], argv + 1);
        printf("unable to exec: %d\n", er);
    }

    exit(EXIT_SUCCESS);
}
