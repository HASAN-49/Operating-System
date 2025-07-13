#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main() {
    char buffer[100];
    char *msg = "Type a message: ";
    write(1, msg, strlen(msg));
    read(0, buffer, sizeof(buffer));
    
    int fd = open("named_pipe", O_WRONLY);
    if (fd < 0) {
        perror("Error");
        exit(1);
    }
    write(fd, buffer, sizeof(buffer));
    close(fd);
    
    // return 0;
    exit(EXIT_SUCCESS);
}