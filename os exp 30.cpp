#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    int fd;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH; 

    // Create a new file
    fd = creat("example.txt", mode);

    if (fd == -1) {
        perror("Error creating file");
        return 1;
    } else {
        printf("File created successfully\n");
        close(fd);
    }

    return 0;
}
