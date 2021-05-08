#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    for (int i = 0; argv != NULL && *argv != NULL; i++)
        printf("[arg %d] \"%s\"\n", i, *argv++);
    return 0;    
}