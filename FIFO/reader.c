#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    int fd;
    char msg[100];

    fd = open("/tmp/myfifo", O_RDONLY);  // open FIFO for reading
    read(fd, msg, sizeof(msg));          // read message from FIFO
    printf("Message received: %s\n", msg);
    close(fd);
    return 0;
}
