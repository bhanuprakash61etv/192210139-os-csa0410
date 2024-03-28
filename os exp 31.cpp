#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

void read_file(char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    ssize_t bytes_read;

    printf("Reading file contents:\n");
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    if (bytes_read == -1) {
        perror("Error reading file");
        exit(EXIT_FAILURE);
    }

    close(fd);
}

void seek_and_read(char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    off_t offset = lseek(fd, 0, SEEK_END);
    if (offset == -1) {
        perror("Error seeking file");
        exit(EXIT_FAILURE);
    }

    printf("\nFile size: %ld bytes\n", (long)offset);

    // Reset file pointer to the beginning
    lseek(fd, 0, SEEK_SET);

    char buffer[1024];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("Error reading file");
        exit(EXIT_FAILURE);
    }

    printf("First %zd bytes of the file:\n", bytes_read);
    write(STDOUT_FILENO, buffer, bytes_read);

    close(fd);
}

void get_file_info(char *filename) {
    struct stat file_info;
    if (stat(filename, &file_info) == -1) {
        perror("Error getting file info");
        exit(EXIT_FAILURE);
    }

    printf("\nFile information:\n");
    printf("File size: %ld bytes\n", (long)file_info.st_size);
    printf("File permissions: %o\n", file_info.st_mode & 0777);
}

void list_directory_contents(char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    printf("\nDirectory contents of %s:\n", path);
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

int main() {
    char *filename = "example.txt";
    char *directory_path = ".";

    read_file(filename);
    seek_and_read(filename);
    get_file_info(filename);
    list_directory_contents(directory_path);

    return 0;
}
