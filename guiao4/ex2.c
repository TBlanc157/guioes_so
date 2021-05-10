#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv) {
    int fout = open("saida.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    int ferr = open("erros.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    int fin  = open("/etc/passwd", O_RDONLY);
    int res = 0, i = 0;

    res = dup2(fin, 0);
    res = dup2(fout, 1);
    res = dup2(ferr, 2);
    close(fin);
    close(fout);
    close(ferr);

    int status;
    pid_t pid;
    if ((pid = fork()) == 0) {
        char buffer;
        char line[128];
        ssize_t read_res;
        while ((read_res = read(0, &buffer, 1)) > 0) {
            line[i] = buffer;
            i++;
            if (buffer == '\n') {
                write(1, line, i);
                write(2, line, i);
                fflush(stdout);
                i = 0;
            }
        }
        _exit(1);
    }
    else
        wait(&status);
    
    return 0;
}