#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

//void create_son(int counter);

int main() {
    //create_son(1);
    int status;
    pid_t res_fork;
    for (int i = 1; i <= 10; i++) {
        if ((res_fork = fork()) == 0)
            printf("[%d]-SON #%d; my father is %d\n", i, getpid(), getppid());
        else {
            wait(&status);
            //printf("[%d]-FATHER #%d; my father is %d\n", i, getpid(), getppid());
            _exit(i);
        }    
    }
    return 0;
}
/*
void create_son(int counter){
    if (counter > 10)
        return;
    pid_t pid;
    int status;
    if ((pid = fork()) == 0){
        // código filho
        printf("%d: SON #%d; MY FATHER #%d\n", counter, getpid(), getppid());
        sleep(1);
        create_son(counter+1);
        _exit(counter);
    }
    else wait(&status);
}*/