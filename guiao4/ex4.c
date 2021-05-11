#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv) {
    int ifd;
    int ofd;
    if (argv[1][1] == 'i') {
        ifd = open(argv[2], O_RDONLY);
    } else return -1;
    if (argv[3][1] == 'o') {
        ofd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0600);
    } else return -1;
    int res;
    res = dup2(ifd, 0);
    res = dup2(ofd, 1);
    close(ifd);
    close(ofd);
    char **args = malloc(sizeof(char *) * (argc - 5));
    for (int i = 5; i < argc; i++)
        args[i-5] = argv[i];

    execvp(args[0], args);
    return 0;
}