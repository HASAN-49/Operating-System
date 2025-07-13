#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main() {
    char buffer[100];
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        int fd = open("named_pipe", O_RDONLY);
        if (fd < 0) {
            perror("named_pipe");
            exit(EXIT_FAILURE);
        }
        char *msg = "Received message: ";
        read(fd, buffer, sizeof(buffer));
        write(1, msg, strlen(msg));
        write(1, buffer, strlen(buffer));
        close(fd);
    }
    else {
        char *msg = "Type a message: ";
        write(1, msg, strlen(msg));
        read(0, buffer, sizeof(buffer));
        
        int fd = open("named_pipe", O_WRONLY);
        if (fd < 0) {
            perror("named_pipe");
            exit(EXIT_FAILURE);
        }
        write(fd, buffer, strlen(buffer));
        close(fd);
    }
    
    exit(EXIT_SUCCESS);
}