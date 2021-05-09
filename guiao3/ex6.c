#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int status;
    pid_t pid;
    if ((pid = fork()) == 0) {
        execvp(argv[1], argv + 1);
        _exit(-1);
    }
    else {
        wait(&status);
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
    }
    return 0;
}