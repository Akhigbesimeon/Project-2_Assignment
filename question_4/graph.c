#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"

// BFS Structure  
typedef struct {
    int items[MAX_NODES];
    int front;
    int rear;
} Queue;

// Initialize Queue
void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

// Enqueue Function
void enqueue(Queue *q, int value) {
    if (q->rear == MAX_NODES - 1) return;
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}


int dequeue(Queue *q) {
    if (isEmpty(q)) return -1;
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

// Graph Functions

void initGraph(Graph *g) {
    g->numNodes = MAX_NODES;
    char names[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    
    for (int i = 0; i < MAX_NODES; i++) {
        g->nodeNames[i] = names[i];
        for (int j = 0; j < MAX_NODES; j++) {
            g->adjMatrix[i][j] = 0;
        }
    }
}

// Add Edge
void addEdge(Graph *g, int src, int dest, int weight) {
    if (src >= 0 && src < MAX_NODES && dest >= 0 && dest < MAX_NODES) {
        g->adjMatrix[src][dest] = weight;
        g->adjMatrix[dest][src] = weight;
    }
}

// Find index
int getIndex(Graph *g, char name) {
    for (int i = 0; i < MAX_NODES; i++) {
        if (g->nodeNames[i] == toupper(name)) return i;
    }
    return -1;
}

void bfsRiskAnalysis(Graph *g, char startNodeName) {
    int startNode = getIndex(g, startNodeName);
    
    if (startNode == -1) {
        printf("Error: Workstation '%c' not found in network.\n", startNodeName);
        return;
    }

    // BFS Variables
    Queue q;
    initQueue(&q);
    int visited[MAX_NODES] = {0};

    int highestRiskWeight = -1;
    int highestRiskNodeIndex = -1;

    printf("\n-- INITIATING BFS TRAVERSAL FROM NODE %c --\n", g->nodeNames[startNode]);
    
    // Start BFS
    visited[startNode] = 1;
    enqueue(&q, startNode);

    printf("Traversal Order: ");

    while (!isEmpty(&q)) {
        int current = dequeue(&q);
        printf("%c -> ", g->nodeNames[current]);

        // iterate all potential neighbors
        for (int i = 0; i < MAX_NODES; i++) {
            int weight = g->adjMatrix[current][i];
            
            if (weight > 0) {
                if (current == startNode) {
                    printf("\n   [Direct Neighbor Found]: %c (Transfer Time: %d mins)", 
                           g->nodeNames[i], weight);
                    
                    if (weight > highestRiskWeight) {
                        highestRiskWeight = weight;
                        highestRiskNodeIndex = i;
                    }
                }

                // BFS Enqueue logic
                if (!visited[i]) {
                    visited[i] = 1;
                    enqueue(&q, i);
                }
            }
        }
    }
    printf("END\n");

    printf("\n-- SECURITY RISK ANALYSIS --\n");
    if (highestRiskNodeIndex != -1) {
        printf("Suspected Breach Point: Workstation %c\n", g->nodeNames[startNode]);
        printf("Highest Exposure Risk:  Workstation %c\n", g->nodeNames[highestRiskNodeIndex]);
        printf("Reason: Highest data transfer volume (%d minutes) detected.\n", highestRiskWeight);
    } else {
        printf("No active connections found for Workstation %c.\n", startNodeName);
    }
    printf("------------------------------\n");
}
