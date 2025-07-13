#include <stdio.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define key 1234

struct msg_buffer {
    long type;
    char text[100];
};

int main() {
    struct msg_buffer message;
    
    int msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }
    
    if (msgrcv(msgid, &message, sizeof (message), 1, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }
    
    printf("Received message: %s\n", message.text);
    
    msgctl(msgid, IPC_RMID, NULL);
    
    exit(EXIT_SUCCESS);
}
