#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid, ppid;
    gid_t gid;
    int fork_result;

    printf("before fork:\n");
    pid = getpid();
    ppid = getppid();
    gid = getgid();
    printf("pid=%d\nppid=%d\ngid=%d\n", pid, ppid, gid);

    fork_result = fork();
    printf("after fork:\n");
    pid = getpid();
    ppid = getppid();
    gid = getgid();
    printf("pid=%d\nppid=%d\ngid=%d\n", pid, ppid, gid);

    if (!fork_result) {
        sleep(1);
        pid = getpid();
        ppid = getppid();
        gid = getgid();
        printf("orphan pid=%d\nppid=%d\ngid=%d\n", pid, ppid, gid);
    }

    exit(EXIT_SUCCESS);
}