#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

int main(int argc, char *argv[]) {
    FILE *file_pointer;
    char line[MAX_LINE_LENGTH];

    if (argc != 3) {
        printf("Usage: %s <pattern> <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    file_pointer = fopen(argv[2], "r");
    if (file_pointer == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    printf("Lines containing '%s' in '%s':\n", argv[1], argv[2]);
    while (fgets(line, sizeof(line), file_pointer) != NULL) {
        if (strstr(line, argv[1]) != NULL) {
            printf("%s", line);
        }
    }

    fclose(file_pointer);

    return 0;
}
