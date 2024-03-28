#include <stdio.h>
#include <stdbool.h>

#define FRAME_SIZE 3 // Number of frames in memory

int main() {
    int page_reference[] = {1, 2, 3, 4, 1, 5, 6, 2, 7, 8, 7, 8, 9, 3, 7, 9, 3, 9};
    int n = sizeof(page_reference) / sizeof(page_reference[0]);
    int frames[FRAME_SIZE];
    int last_used[FRAME_SIZE];
    bool in_memory[FRAME_SIZE] = {false};
    int page_faults = 0;

    printf("Page reference string: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", page_reference[i]);
    }
    printf("\n");

    printf("\nSimulation of LRU Page Replacement Algorithm:\n\n");

    for (int i = 0; i < n; i++) {
        printf("Reference to page %d: ", page_reference[i]);

        bool page_found = false;
        for (int j = 0; j < FRAME_SIZE; j++) {
            if (frames[j] == page_reference[i]) {
                page_found = true;
                last_used[j] = i; // Update last used time
                printf("Page %d already in memory\n", page_reference[i]);
                break;
            }
        }

        if (!page_found) {
            printf("Page fault occurred. ");
            page_faults++;

            // Find the least recently used page in memory
            int lru_index = 0;
            for (int j = 1; j < FRAME_SIZE; j++) {
                if (last_used[j] < last_used[lru_index]) {
                    lru_index = j;
                }
            }

            frames[lru_index] = page_reference[i];
            last_used[lru_index] = i;

            printf("Page %d loaded into frame %d\n", page_reference[i], lru_index);
        }

        printf("Current frames in memory: ");
        for (int j = 0; j < FRAME_SIZE; j++) {
            if (in_memory[j]) {
                printf("%d ", frames[j]);
            } else {
                printf("- ");
            }
        }
        printf("\n\n");
    }

    printf("Total page faults: %d\n", page_faults);

    return 0;
}
