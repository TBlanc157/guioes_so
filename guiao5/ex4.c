#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int p[2];
    //int ifd = open("/etc", O_RDONLY);    
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
            close(p[1]);
            dup2(p[0], 0);
            execlp("wc", "wc", "-l", NULL);
            close(p[0]);
            _exit(1);
            break;
        default:
            close(p[0]);
            dup2(p[1], 1);
            execlp("ls", "ls", "/etc", NULL);
            wait(NULL);
            close(p[1]);
            break;
    }
    return 0;
}