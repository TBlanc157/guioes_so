#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> /* system calls: defs & decls essencials */
#define MAX_BUFF 1024

ssize_t myreadln(int fd, char *line, size_t size);

int main() {
    char line[MAX_BUFF];
    ssize_t bytes, total_bytes = 0, i = 0;
    int file = open("test.txt", O_RDONLY, 0600);

    if (file == -1) {
        perror("Error: ");
    }
    while ((bytes = myreadln(file, line, MAX_BUFF)) > 0) {
        total_bytes += bytes;
        printf("\t%ld\t%ld: %s\n", bytes, i + 1, line);
        i++;
        lseek(file, total_bytes + i, SEEK_SET);
    }

    return 0;
}

ssize_t myreadln(int fd, char *line, size_t size) {
    size_t bytes, i = 0;
    char *tmp = malloc(size);
    
    if ((bytes = read(fd, tmp, size) == 0))
        return 0;

    for (; (tmp[i]) && (tmp[i] != '\n'); i++){
        line[i] = tmp[i];
    }

    line[i] = '\0';

    free(tmp);

    return i;
}
