#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> /* system calls: defs & decls essencials */
#define MAX_BUFF 1024

int main(int argc, char* argv[]) {
    int dest, src;
    ssize_t bytes;
    char buff[MAX_BUFF];
    src = open(argv[1], O_RDONLY, 0600);

    if (src == -1) {
        perror("Error: ");
        return -1;
    }
    dest = open(argv[2], O_CREAT | O_WRONLY, 0600);
    if (dest == -1) {
        perror("Error: ");
        return -1;
    }

    while ((bytes = read(src, buff, MAX_BUFF)) > 0)
        write(dest, buff, bytes);
    close(dest);
    close(src);
    return 0;
}
