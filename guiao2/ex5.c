#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

void create_son(int counter);

int main() {
    create_son(1);
    return 0;
}

void create_son(int counter){
    if (counter > 10)
        return;
    pid_t pid;
    if ((pid = fork()) == 0){
        // código filho
        printf("%d: SON #%d; MY FATHER #%d\n", counter, getpid(), getppid());
        sleep(1);
        create_son(counter+1);
        _exit(counter);
    }
    else {
        // código pai
        _exit(0);
    }
    _exit(0);
}