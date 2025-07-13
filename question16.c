#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int cnt;
pthread_mutex_t key;

void* increment1(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&key);
        cnt++;
        printf("Thread 1: counter = %d\n", cnt);
        pthread_mutex_unlock(&key);
    }
    pthread_exit(0);
}

void* increment2(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&key);
        cnt--;
        printf("Thread 2: counter = %d\n", cnt);
        pthread_mutex_unlock(&key);
    }
    pthread_exit(EXIT_SUCCESS);
}

int main() {
    pthread_t t1, t2;
    
    pthread_create(&t1, NULL, increment1, NULL);
    pthread_create(&t2, NULL, increment2, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("Final count = %d\n", cnt);
    
    return 0;
}