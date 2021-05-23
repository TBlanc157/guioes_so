#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int fd = open("fifo", O_WRONLY, 0666);
    if (fd == -1) {
        perror("Open fifo: ");
        return -1;
    }
    ssize_t bytes;
    char buf;
    while ((bytes = read(0, &buf, 1)) > 0) {
        write(fd, &buf, bytes);
    }
    close(fd);
    unlink("fifo");
    return 0;
}