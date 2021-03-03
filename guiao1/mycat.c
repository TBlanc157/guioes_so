#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> /* system calls: defs & decls essencials */
#define MAX_BUFF 1024

int main() {
    char buff[MAX_BUFF];
    int bytes = 0;
    int write_bytes = 0;

    while ((bytes = read(0, buff, MAX_BUFF)) > 0) {
        write_bytes = write(1, buff, bytes);
    }

    if (write_bytes - bytes == 0) return 0;

    return -1;
}