#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int p[2];
    char buff;
    if (pipe(p) == -1) {
        perror("pipe");
        return -1;
    }
    switch (fork()) {
        case -1:
            perror("pipe");
            return -1;
            break;
        case 0:
            close(p[0]);
            dup2(p[1], 1);
            execlp("wc", "wc", NULL);
            close(p[1]);
            _exit(1);
            break;
        default:
            close(p[1]);
            dup2(p[0], 0);
            while(read(p[0],&buff,1)) write(1,&buff,1);
            close(p[0]);
            wait(NULL);
            break;
    }
    return 0;
}