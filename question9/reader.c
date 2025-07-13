#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main() {
    int fd = open("named_pipe", O_RDONLY);
    if (fd < 0) {
        perror("Named pipe");
        exit(1);
    }
    
    char *msg = "Received message: ";
    char buffer[100];
    read(fd, buffer, sizeof(buffer));
    write(1, msg, strlen(msg));
    write(1, buffer, strlen(buffer));
    close(fd);
    
    // return 0;
    exit(EXIT_SUCCESS);
}
