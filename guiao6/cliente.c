#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    int fd = open("fifo", O_WRONLY, 0666);
    if (fd == -1) perror("Opening fifo");

    char buff;
    while (read(0, &buff, 1) > 0)
        write(fd, &buff, 1);
    close(fd);
    return 0;
}