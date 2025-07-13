#include <stdio.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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
    
    message.type = 1;
    strcpy(message.text, "Hello Receiver!!!");
    if (msgsnd(msgid, &message, sizeof(message), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
    
    printf("Message sent...\n");
    
    exit(EXIT_SUCCESS);
}