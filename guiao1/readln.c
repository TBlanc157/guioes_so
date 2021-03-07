#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> /* system calls: defs & decls essencials */
#define MAX_BUFF 1024


int get_alg(int n){
    int n_alg = 1;
    while (n >= 10){
        n_alg++;
        n /= 10;
    }
    return n_alg;
}

ssize_t myreadln(int fd, char *line, size_t size) {
    ssize_t bytes, i;

    if ((bytes = read(fd, line, size)) < 0)
        return -1;
        
    for(i = 0; i < bytes && line[i] != '\n'; i++);
    if (line[i] == '\n') i++;

    lseek(fd, (i-bytes), SEEK_CUR);
    return i;
}

int main(int argc, char **argv){
    int fd;
    if (argc == 0)
        fd = 0;
    else {
        fd = open(argv[1], O_RDONLY, 0600);
        if (fd == -1) {
            perror("Error: ");
            return -1;
        }
    }

    char buffer[MAX_BUFF];
    int nl = 1;
    ssize_t bytes;
    while((bytes = myreadln(fd, buffer, MAX_BUFF)) > 0) {
        char line[3 + get_alg(nl)];
        int size = sprintf(line, "\t%d:\t", nl);
        if (buffer[0] != '\n'){
            write(1, line, size);
            nl++;
        }
        write(1, buffer, bytes);
    }

    putchar('\n');
    close(fd);
    return 0;
}