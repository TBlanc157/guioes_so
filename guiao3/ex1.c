#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    execlp("ls", "ls", "-i", NULL);
    puts("Não executes isto bro\n");   
    return 0;
}