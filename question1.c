#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int addition(int a, int b) {
    int res = a + b;
    return res;
}

int main() {
    pid_t child1, child2, child3;
    int pid, a = 25, b = 15;
    pid = getpid();
    printf("Parent Process: %d\n", pid);
    
    child1 = fork();
    if (child1 < 0) {
        printf("Error occurs\n");
        exit(1);
    }
    else if (child1 == 0) {
        int pid1 = getpid(), ppid = getppid();
        printf("Parent: %d, Chilld: %d, Sum = %d\n", ppid, pid1, addition(a, b));
    }
    else {
        child2 = fork();
        if (child2 < 0) {
            printf("Error occurs\n");
            exit(1);
        }
        else if (child2 == 0) {
            int pid1 = getpid(), ppid = getppid();
            printf("Parent: %d, Chilld: %d\n", ppid, pid1);
        }
        else {
            child3 = fork();
            if (child3 < 0) {
                printf("Error occurs\n");
                exit(1);
            }
            else if (child3 == 0) {
                int pid1 = getpid(), ppid = getppid();
                printf("Parent: %d, Chilld: %d\n", ppid, pid1);
            }
            else {
                wait(NULL);
                wait(NULL);
                wait(NULL);
                printf("Parent(PID: %d) finished waiting for childrens\n", getpid());
            }
        }
    }
    
    return 0;
}