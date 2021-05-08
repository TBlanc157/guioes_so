#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int status;
    pid_t pid;
    for (int i = 1; i < argc; i++) {
        if ((pid = fork()) == 0) {
            execlp(argv[i], argv[i], NULL);
            _exit(-1);
        }
        else {
            wait(&status);
            if (status == -1)
                puts("Não foi possível executar o programa");
        }
    }
    return 0;
}