#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FRAMES 10

int main() {
    int reference_string[MAX_FRAMES], frames[MAX_FRAMES], pages;
    int page_faults = 0, frame_count = 0;

    printf("Enter number of pages: ");
    scanf("%d", &pages);

    printf("Enter the reference string: ");
    for (int i = 0; i < pages; i++) {
        scanf("%d", &reference_string[i]);
    }

    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < pages; i++) {
        bool page_found = false;
        for (int j = 0; j < frame_count; j++) {
            if (frames[j] == reference_string[i]) {
                page_found = true;
                break;
            }
        }

        if (!page_found) {
            if (frame_count < MAX_FRAMES) {
                frames[frame_count] = reference_string[i];
                frame_count++;
            } else {
                int max_future_index = -1;
                int page_to_replace;
                for (int j = 0; j < MAX_FRAMES; j++) {
                    int future_index = 0;
                    for (int k = i + 1; k < pages; k++) {
                        if (reference_string[k] == frames[j]) {
                            future_index = k;
                            break;
                        }
                    }
                    if (future_index > max_future_index) {
                        max_future_index = future_index;
                        page_to_replace = j;
                    }
                }
                frames[page_to_replace] = reference_string[i];
            }
            page_faults++;
        }
    }

    printf("Total Page Faults: %d\n", page_faults);

    return 0;
}
