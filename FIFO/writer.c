#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    int fd;
    char msg[100];

    fd = open("/tmp/myfifo", O_WRONLY);  // open FIFO for writing
    printf("Enter a message to send: ");
    fgets(msg, sizeof(msg), stdin);
    write(fd, msg, sizeof(msg));         // write message into FIFO
    close(fd);
    printf("Message sent successfully!\n");
    return 0;
}
