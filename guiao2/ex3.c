#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
    pid_t pid;
    int status;
    
    for (int i = 1; i < 11; i++){
        printf("ITERAÇÃO: %d \n", i);
        if ((pid = fork()) == 0){
            // código filho
            printf("SON #%d; FATHER #%d\n", getpid(), getppid());
            sleep(1);
            _exit(i);
        }
        else {
            // código pai
            pid_t terminated_pid = wait(&status);
            if (WIFEXITED(status))
                printf("FATHER: SON #%d; exit status: %d\n", terminated_pid, WEXITSTATUS(status));
            else 
                printf("Unknown error.\n");
        }
    }
    return 0;
}