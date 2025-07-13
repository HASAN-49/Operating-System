#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    key_t key = 1234;
    
    int shmid = shmget(key, sizeof (int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    
    int *var = shmat(shmid, NULL, 0);
    if (var == (int *) -1) {
        perror("shmat");
        exit(1);
    }
    
    for (int i = 0; i < 10; i++) {
        printf("Before write: %d\n", *var);
        *var = 100;
        printf("After write: %d\n", *var);
        usleep(100000); // 100 ms
    }
    
    if (shmdt(var) == -1) {
        perror("shmdt");
        exit(1);
    }
    
    exit(EXIT_SUCCESS);
}
