#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    int p[2];
    char line[] = "Ayyo do a kickflip!\0";
    char buffer[20];
    ssize_t res = 0;
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
        // fechar descritor de escrita no filho
        close(p[1]);
        while ((res = read(p[0], &buffer, 5)) > 0) {
            char linha[res];
            snprintf(linha, res+1, "%s", buffer);
            printf("[FILHO]: read \"%s\" from pipe res %ld\n", linha, res);
        }
        close(p[0]);
        _exit(0);
        break;
    
    default:
        /* PAI: */
        // fechar descritor de leitura no pai
        close(p[0]);
        sleep(3);
        write(p[1], &line, strlen(line));
        printf("[PAI] wrote a \"%s\" line to pipe\n", line);
        close(p[1]);
        wait(&status);
    }

    return 0;
}