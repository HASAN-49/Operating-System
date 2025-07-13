#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/prctl.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <n> <child1> <child2> ... <childn>\n", argv[0]);
        exit(1);
    }
    int n = atoi(argv[1]);
    if (argc != n + 2) {
        printf("Enter n child\n");
        exit(1);
    }
    prctl(PR_SET_NAME, "parent_process");
    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        }
        else if (pid == 0) {
            printf("Child: %d, Name: %s, PID: %d, PPID: %d\n", i + 1, argv[i + 2], getpid(), getppid());
            exit(0);
        }
    }
    sleep(20);
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }
    return 0;
}