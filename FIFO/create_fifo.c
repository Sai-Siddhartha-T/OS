#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int res = mkfifo("/tmp/myfifo", 0666); // create FIFO with read/write permission
    if (res == 0)
        printf("FIFO created successfully.\n");
    else
        perror("Error creating FIFO");
    return 0;
}
