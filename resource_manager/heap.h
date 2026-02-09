#ifndef HEAP_H
#define HEAP_H

#define MAX_JOBS 100

// Structure 
typedef struct {
    char id;        
    int priority; 
} Job;

// Priority Queue Structure (Max-Heap)
typedef struct {
    Job array[MAX_JOBS];
    int size;
} MaxHeap;

// Function Prototypes
void initHeap(MaxHeap *heap);
void printHeap(MaxHeap *heap);

void buildMaxHeap(MaxHeap *heap);
void insertJob(MaxHeap *heap, char id, int priority);

void deleteJobByPriority(MaxHeap *heap, int priority);

#endif
