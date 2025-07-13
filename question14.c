#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main () {
    int *shmaddr, shmid;
    
    key_t key = 5678;
    shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    else if (pid == 0) {
        shmaddr = shmat(shmid, NULL, 0);
        if (shmaddr == (int*) -1) {
            perror("shmat(child)");
            exit(1);
        }
        for (int i = 0; i < 10; i++) {
            printf("Child before write: shared variable = %d\n", *shmaddr);
            *shmaddr = 100;
            printf("Child after write: shared variable = %d\n", *shmaddr);
        }
        if (shmdt(shmaddr) == -1) {
            perror("shmdt(child)");
            exit(1);
        }
        // exit(0);
    }
    else {
        shmaddr = shmat(shmid, NULL, 0);
        if (shmaddr == (int *) -1) {
            perror("shmat(parent)");
            exit(1);
        }
        for (int i = 0; i < 10; i++) {
            printf("Parent before write: shared variable = %d\n", *shmaddr);
            *shmaddr = 999;
            printf("Parent after write: shared variable = %d\n", *shmaddr);
        }
        int status;
        wait(&status);
        printf("Parent final read: shared variable = %d\n", *shmaddr);
        if (shmdt(shmaddr) == -1) {
            perror("shmdt(parent)");
            exit(1);
        }
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(1);
        }
        // exit(0);
    }
    
    return 0;
}