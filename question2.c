#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int myPID, pid = getpid(), processor_no;
    
    printf("Parent: %d\n", pid);
    
    myPID = fork();
    
    if (myPID > 0) {
        int p = getpid();
        processor_no = sched_getcpu();
        printf("Parent: %d, (processor_no = %d) child will be orphan\n", p, processor_no);
        exit(0);
    }
    else if (myPID == 0) {
        sleep(5);
        int p = getpid(), pp = getppid();
        processor_no = sched_getcpu();
        printf("Parent: %d, Child: %d, processor_no = %d\n", pp, p, processor_no);
    }
    else {
        perror("fork");
        exit(1);
    }
    
    return 0;
}