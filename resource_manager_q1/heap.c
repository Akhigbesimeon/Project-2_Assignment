#include <stdio.h>
#include "heap.h"


// Swap two jobs in memory
static void swap(Job *a, Job *b) {
    Job temp = *a;
    *a = *b;
    *b = temp;
}

// Max-Heapify
static void maxHeapify(MaxHeap *heap, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->array[left].priority > heap->array[largest].priority)
        largest = left;

    if (right < heap->size && heap->array[right].priority > heap->array[largest].priority)
        largest = right;

    if (largest != i) {
        swap(&heap->array[i], &heap->array[largest]);
        maxHeapify(heap, largest);
    }
}

// Initialize heap function
void initHeap(MaxHeap *heap) {
    heap->size = 0;
}

// Print heap
void printHeap(MaxHeap *heap) {
    printf("Current Job Scheduler Queue:\n");
    if (heap->size == 0) {
        printf("  [Empty]\n");
        return;
    }
 
    for (int i = 0; i < heap->size; i++) {
        printf("  [%d] Job %c (Prio: %d)", i, heap->array[i].id, heap->array[i].priority);
        if (i == 0) printf(" <- ROOT (Next Execution)");
        printf("\n");
    }
    printf("----------------------------------------\n");
}

// Build Max-Heap
void buildMaxHeap(MaxHeap *heap) {
    for (int i = (heap->size / 2) - 1; i >= 0; i--) {
        maxHeapify(heap, i);
    }
}

// Insert Job
void insertJob(MaxHeap *heap, char id, int priority) {
    if (heap->size >= MAX_JOBS) {
        printf("Error: Scheduler Queue Full.\n");
        return;
    }

    int i = heap->size;
    heap->array[i].id = id;
    heap->array[i].priority = priority;
    heap->size++;

    printf(">> INSERTING: Job %c (Prio: %d)\n", id, priority);

    while (i != 0 && heap->array[(i - 1) / 2].priority < heap->array[i].priority) {
        swap(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2; 
    }
}


// Delete job by priority
void deleteJobByPriority(MaxHeap *heap, int targetPriority) {
    int i;
    int found = 0;

    for (i = 0; i < heap->size; i++) {
        if (heap->array[i].priority == targetPriority) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Job with priority %d not found.\n", targetPriority);
        return;
    }

    printf(">> ABORTING/REMOVING: Job %c (Prio: %d)\n", heap->array[i].id, heap->array[i].priority);

    heap->array[i] = heap->array[heap->size - 1];
    heap->size--;

    if (i > 0 && heap->array[i].priority > heap->array[(i - 1) / 2].priority) {
        while (i != 0 && heap->array[(i - 1) / 2].priority < heap->array[i].priority) {
            swap(&heap->array[i], &heap->array[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    } else {
        maxHeapify(heap, i);
    }
}
