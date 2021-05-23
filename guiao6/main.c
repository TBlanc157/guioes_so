#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int res = mkfifo("fifo", 0666);
    if (res < 0) {
        perror("Fifo: ");
        return -1;
    }
    return 0;
}