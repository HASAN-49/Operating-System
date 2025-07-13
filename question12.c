#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define key 1234

struct msg_buffer {
    long type;
    char text[100];
};

int main() {
    struct msg_buffer message;
    
    int msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        sleep(1);
        if (msgrcv(msgid, &message, sizeof(message), 1, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }
        printf("Received message: %s\n", message.text);
        
    }
    else {
        message.type = 1;
        strcpy(message.text, "Hello Child!!!");
        if (msgsnd(msgid, &message, sizeof(message.text), 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
        printf("Message sent to Child\n");
        wait(NULL);
        msgctl(msgid, IPC_RMID, NULL);
    }
    
    exit(EXIT_SUCCESS);
}