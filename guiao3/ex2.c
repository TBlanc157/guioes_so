#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int status;
    pid_t pid;
    if ((pid = fork()) == 0) {
        execlp("ls", "ls", "-i", NULL);
        _exit(-1);
    }
    else {
        pid_t terminated_pid = wait(&status);
        if (WIFEXITED(status)) printf("\n[SON] #%d acabou o processo com status %d\n", terminated_pid, WEXITSTATUS(status));
        printf("[PAI] também executei #pid=%d\n", getpid());
    }
    return 0;
}