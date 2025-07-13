#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

double avg;
int mn, mx;
int *numbers, n;

int f[100];
void* fibo(void* arg) {
    f[0] = 0;
    if (n > 1) f[1] = 1;
    for (int i = 2; i < n; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }
    return NULL;
}

void* cal_avg(void* arg) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += numbers[i];
    }
    avg = 1.0 * sum / n;
    // return NULL;
    pthread_exit(NULL);
}

void* cal_mn(void* arg) {
    mn = numbers[0];
    for (int i = 1; i < n; i++) {
        if (mn > numbers[i]) mn = numbers[i];
    }
    // return NULL;
    pthread_exit(NULL);
}

void* cal_mx(void* arg) {
    mx = numbers[0];
    for (int i = 1; i < n; i++) {
        if (mx < numbers[i]) mx = numbers[i];
    }
    // return NULL;
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) { // ./a.out 4
    if (argc < 2) {
        printf("Usage: %s num1 num2 ... numn", argv[0]);
        return 1;
    }
    
    n = argc - 1;
    numbers = malloc(n * sizeof (int));
    
    for (int i = 0; i < n; i++) {
        numbers[i] = atoi(argv[i + 1]);
    }
    
    pthread_t t1, t2, t3;
    
    pthread_create(&t1, NULL, cal_avg, NULL);
    pthread_create(&t2, NULL, cal_mn, NULL);
    pthread_create(&t3, NULL, cal_mx, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    
    printf("Avg = %.f, Mx = %d, Mn = %d\n", avg, mx, mn);
    free(numbers);
    
    return 0;
}