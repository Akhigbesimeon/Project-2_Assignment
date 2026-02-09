#include <stdio.h>
#include "heap.h"

int main() {
    MaxHeap scheduler;
    initHeap(&scheduler);

    // Initial Data Set
    int priorities[] = {42, 17, 93, 28, 65, 81, 54, 60, 99, 73, 88};
    int count = sizeof(priorities) / sizeof(priorities[0]);

    printf("-- INITIALIZING CLOUD SCHEDULER --\n");
    
    // Load data and assign IDs
    for (int i = 0; i < count; i++) {
        scheduler.array[i].priority = priorities[i];
        scheduler.array[i].id = 'A' + i; 
    }
    scheduler.size = count;

    // Build the Max-Heap structure
    buildMaxHeap(&scheduler);
    printf("Status: Initial Max-Heap Built.\n");
    printHeap(&scheduler);

    // Urgent Job Arrival (Priority 100)
    printf("-- URGENT JOB ARRIVAL --\n");
    insertJob(&scheduler, 'L', 100); 
    printHeap(&scheduler);

    // Urgent Job Aborted (Remove Priority 100)
    printf("-- URGENT JOB ABORTED --\n");
    deleteJobByPriority(&scheduler, 100);
    printHeap(&scheduler);

    return 0;
}
