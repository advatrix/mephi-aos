#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int r;

    do {
        char buf[80] = {0};
        r = read(STDIN_FILENO, buf, 80);
        write(STDOUT_FILENO, buf, r);
    } while(r);
}
