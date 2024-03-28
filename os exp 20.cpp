#include <stdio.h>
#include <stdbool.h>

#define MAX_BLOCKS 100
#define MAX_PROCESS 100

// Structure to represent a memory block
struct MemoryBlock {
    int id;
    int size;
    bool allocated;
};

// Structure to represent a process
struct Process {
    int id;
    int size;
};

// Function prototypes
void worstFit(struct Process processes[], int m, struct MemoryBlock blocks[], int n);
void printMemoryMap(struct MemoryBlock blocks[], int n);

int main() {
    struct Process processes[MAX_PROCESS];
    struct MemoryBlock blocks[MAX_BLOCKS];
    int m, n;

    printf("Enter the number of processes: ");
    scanf("%d", &m);

    printf("Enter the sizes of processes:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &processes[i].size);
        processes[i].id = i + 1;
    }

    printf("Enter the number of memory blocks: ");
    scanf("%d", &n);

    printf("Enter the sizes of memory blocks:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &blocks[i].size);
        blocks[i].id = i + 1;
        blocks[i].allocated = false;
    }

    worstFit(processes, m, blocks, n);

    return 0;
}

// Function to allocate memory blocks to processes using worst fit algorithm
void worstFit(struct Process processes[], int m, struct MemoryBlock blocks[], int n) {
    for (int i = 0; i < m; i++) {
        int worstFitIdx = -1;
        for (int j = 0; j < n; j++) {
            if (!blocks[j].allocated && blocks[j].size >= processes[i].size) {
                if (worstFitIdx == -1 || blocks[j].size > blocks[worstFitIdx].size) {
                    worstFitIdx = j;
                }
            }
        }
        if (worstFitIdx != -1) {
            blocks[worstFitIdx].allocated = true;
            printf("Process %d allocated to Memory Block %d\n", processes[i].id, blocks[worstFitIdx].id);
        } else {
            printf("Process %d cannot be allocated due to insufficient memory\n", processes[i].id);
        }
    }
    printMemoryMap(blocks, n);
}

// Function to print memory map
void printMemoryMap(struct MemoryBlock blocks[], int n) {
    printf("Memory Map:\n");
    for (int i = 0; i < n; i++) {
        printf("Block %d: Size %d, ", blocks[i].id, blocks[i].size);
        if (blocks[i].allocated) {
            printf("Allocated\n");
        } else {
            printf("Free\n");
        }
    }
}

