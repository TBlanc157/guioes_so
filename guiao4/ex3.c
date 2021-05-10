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
    int res = 0;

    res = dup2(fin, 0);
    res = dup2(fout, 1);
    res = dup2(ferr, 2);
    close(fin);
    close(fout);
    close(ferr);

    execl("/usr/bin/wc", "wc", NULL);
    return 0;
}