//Pavithra Deepu E
// S3 CSE AI 47
//Implementation of Memory allocation using Best-Fit Strategy

#include <stdio.h>

void implementBestFit(int blockSize[], int blocks, int processSize[], int processes) {
    // This will store the block id of the allocated block to a process
    int allocation[processes];
    int occupied[blocks];
    
    // Initially assigning -1 to all allocation indexes
    // means nothing is allocated currently
    for (int i = 0; i < processes; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < blocks; i++) {
        occupied[i] = 0; // Initially, all blocks are unoccupied
    }

    // Pick each process and find suitable blocks according to its size
    // and assign to it
    for (int i = 0; i < processes; i++) {
        int indexPlaced = -1;

        for (int j = 0; j < blocks; j++) {
            // If the block is large enough and not occupied
            if (blockSize[j] >= processSize[i] && !occupied[j]) {
                // Place it at the first block that fits the process
                if (indexPlaced == -1) {
                    indexPlaced = j;
                }
                // If any future block is smaller than the current
                // block where the process is placed, change the block
                // to minimize waste (Best Fit)
                else if (blockSize[j] < blockSize[indexPlaced]) {
                    indexPlaced = j;
                }
            }
        }

        // If we were successfully able to find a block for the process
        if (indexPlaced != -1) {
            // Allocate this block to the process
            allocation[i] = indexPlaced;
            // Mark the block as occupied
            occupied[indexPlaced] = 1;
        }
    }

    // Print the allocation details
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < processes; i++) {
        printf("%d \t\t\t %d \t\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1); // Block index is 1-based in the output
        } else {
            printf("Not Allocated\n");
        }
    }
}

// Driver code
int main() {
    int blocks, processes;

    // Input number of blocks and processes
    printf("Enter number of blocks: ");
    scanf("%d", &blocks);
    printf("Enter number of processes: ");
    scanf("%d", &processes);

    // Dynamically allocate arrays for block sizes and process sizes
    int blockSize[blocks], processSize[processes];

    // Input the block sizes
    printf("Enter the block sizes:\n");
    for (int i = 0; i < blocks; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    // Input the process sizes
    printf("Enter the process sizes:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    // Call the Best Fit function
    implementBestFit(blockSize, blocks, processSize, processes);
    
    return 0;
}
