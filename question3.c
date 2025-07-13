#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int myPID, pid = getpid();
    
    myPID = fork();
    if (myPID < 0) {
        perror("fork");
        return 1;
    }
    else if (myPID == 0) {
        int p = getpid(), pp = getppid();
        printf("Parent: %d, Child: %d\n", pp, p);
        exit(0);
    }
    else {
        pid = getpid();
        printf("Parent: %d, is waiting\n", pid);
        sleep(10);
        printf("Parent: %d, completed waiting\n", pid);
    }
    
    return 0;
}