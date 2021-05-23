#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    int fd = open("fifo", O_RDONLY, 0666);
    if (fd == -1) perror("Opening fifo");
    /*int fd_w = open("fifo", O_WRONLY, 0666);
    if (fd_w == -1) perror("Opening fifo");*/

    int fd_log = open("log", O_CREAT | O_WRONLY, 0666);
    if (fd_log == -1) perror("Opening log");
    puts("[SV] OPEN");
    char buff;
    while (read(fd, &buff, 1) > 0)
        write(fd_log, &buff, 1);
    
    //close(fd_w);
    close(fd_log);
    close(fd);
    unlink("fifo");
    puts("[SV] CLOSE");
    return 0;
}