#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, i, total_movement = 0;
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    int requests[n];

    printf("Enter the request queue: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    for (i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    int index = -1;
    for (i = 0; i < n; i++) {
        if (requests[i] >= head) {
            index = i;
            break;
        }
    }

    printf("Enter the size of the disk: ");
    int disk_size;
    scanf("%d", &disk_size);

    printf("Move from %d to %d\n", head, requests[index]);
    total_movement += abs(head - requests[index]);
    head = requests[index];

    for (i = index + 1; i < n; i++) {
        printf("Move from %d to %d\n", head, requests[i]);
        total_movement += abs(head - requests[i]);
        head = requests[i];
    }
    printf("Move from %d to %d\n", head, disk_size - 1);
    total_movement += (disk_size - 1) - head;
    head = disk_size - 1;

    
    printf("Move from %d to 0\n", head);
    total_movement += head;
    head = 0;

    for (i = 0; i < index; i++) {
        printf("Move from %d to %d\n", head, requests[i]);
        total_movement += abs(head - requests[i]);
        head = requests[i];
    }

    printf("Total head movement: %d\n", total_movement);

    return 0;
}
