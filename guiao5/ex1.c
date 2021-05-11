#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    int p[2];
    char line[] = "Ayyo do a kickflip!\0";
    char buffer[20];
    ssize_t res;
    int status;

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
        /* FILHO: */
        // fechar descritor de leitura no filho
        close(p[0]);
        sleep(2);
        write(p[1], &line, strlen(line));
        printf("[FILHO] wrote a line to pipe\n");
        close(p[1]);
        close(p[1]);
        
        break;
    
    default:
        /* PAI: */
        // fechar descritor de escrita no pai
        res = read(p[0], &buffer, sizeof(buffer));
        printf("[PAI]: read \"%s\" from pipe res %ld\n", buffer, res);
        close(p[0]);
        _exit(0);
        wait(&status);
    }

    return 0;
}