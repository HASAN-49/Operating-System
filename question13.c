#include <stdio.h>
#include <pthread.h>

int cnt = 0;

void* increment1(void* arg) {
    for (int i = 0; i < 10; i++) {
        cnt++;
        printf("Thread 1: count = %d\n", cnt);
    }
    return NULL;
}

void* increment2(void* arg) {
    for (int i = 0; i < 10; i++) {
        cnt--;
        printf("Thread 2: count = %d\n", cnt);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    
    pthread_create(&t1, NULL, increment1, NULL);
    pthread_create(&t2, NULL, increment2, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("Final count = %d", cnt);
    
    return 0;
}