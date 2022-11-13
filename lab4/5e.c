// wc - l

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    execl("/bin/sh", "sh", "-c", "wc", "-l", (char *) NULL);
}