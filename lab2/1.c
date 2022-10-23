#include <stdio.h>
#include <stdlib.h>

extern char **environ;

void add_string() {
    char *str = calloc(80, sizeof(char));
    printf("enter string: ");
    scanf("%s", str);

    putenv(str);
}

void print_env() {
    char *var_name = calloc(80, sizeof(char));
    printf("enter var name: ");
    scanf("%s", var_name);

    const char *value = getenv(var_name);
    if (value) {
        printf("%s\n", value);
    }
    else {
        printf("No value found\n");
    }
    free(var_name);
}

int main() {
    int r, s = 1;
    do {
        printf("0 - add string\n1 - get env var\n* - get env\n");
        s = scanf("%d", &r);
        switch(r) {
            case 0:
                add_string();
                break;
            case 1:
                print_env();
                break;
            default:
                for (char **it = environ; *it; it++) {
                    printf("%s\n", *it);
                }
                break;
        }
    } while(s);
}