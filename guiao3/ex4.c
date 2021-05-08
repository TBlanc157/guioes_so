#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    char *path = "/home/blanc/uni/2ano_2sem/so/guioes/guiao3/ex3.out";
    strcpy(argv[0], "ex3.out");
    execv(path, argv);
    return 0;
}