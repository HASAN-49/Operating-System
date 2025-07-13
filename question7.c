#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int global = 20;

int main() {
    int local = 30;
    pid_t myPID;
    
    myPID = fork();
    if (myPID < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (myPID == 0) {
        local = 20, global = 30;
        printf("Parent: %d, Child: %d, Global: %d, Local: %d\n", getppid(), getpid(), global, local);
        exit(EXIT_SUCCESS);
    }
    else {
        wait(NULL);
        printf("Parent: %d, Child: %d, Global: %d, Local: %d\n", getppid(), getpid(), global, local);
        exit(EXIT_SUCCESS);
    }
    
    return 0;
}