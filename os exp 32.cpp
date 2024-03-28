#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file_pointer;
    char filename[] = "example.txt";
    char text_to_write[] = "Hello, World!\n";
    char buffer[100];

    file_pointer = fopen(filename, "w");
    if (file_pointer == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    printf("File created successfully.\n");

    fputs(text_to_write, file_pointer);
    printf("Text \"%s\" written to the file.\n", text_to_write);

    fclose(file_pointer);
    printf("File closed.\n");

    file_pointer = fopen(filename, "r");
    if (file_pointer == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    printf("File opened successfully for reading.\n");

    printf("Contents of the file:\n");
    while (fgets(buffer, sizeof(buffer), file_pointer) != NULL) {
        printf("%s", buffer);
    }

    fclose(file_pointer);
    printf("File closed.\n");

    return 0;
}
