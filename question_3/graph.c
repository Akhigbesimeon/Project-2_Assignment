#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

typedef struct {
    int parent;
    int rank;
} Subset;

// Find set of an element i
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union of two sets x and y
void unionSets(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Comparator for qsort
int compareEdges(const void* a, const void* b) {
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight - b1->weight;
}

// Graph Functions

void initGraph(Graph *g) {
    char names[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    for (int i = 0; i < NUM_HUBS; i++) {
        g->hubNames[i] = names[i];
        for (int j = 0; j < NUM_HUBS; j++) {
            g->adjMatrix[i][j] = 0; 
        }
    }
}

void addEdge(Graph *g, int src, int dest, int weight) {
    g->adjMatrix[src][dest] = weight;
    g->adjMatrix[dest][src] = weight;
}

void printAdjMatrix(Graph *g) {
    printf("\n1. Adjacency Matrix Representation:\n");
    printf("   ");
    for (int i = 0; i < NUM_HUBS; i++) printf(" %c ", g->hubNames[i]);
    printf("\n");
    
    for (int i = 0; i < NUM_HUBS; i++) {
        printf(" %c ", g->hubNames[i]);
        for (int j = 0; j < NUM_HUBS; j++) {
            printf("%2d ", g->adjMatrix[i][j]);
        }
        printf("\n");
    }
    printf("-------------------------------------------------\n");
}

void runKruskalsMST(Graph *g) {
    Edge edges[NUM_HUBS * NUM_HUBS];
    int edgeCount = 0;

    // Get edges from Matrix
    for (int i = 0; i < NUM_HUBS; i++) {
        for (int j = i + 1; j < NUM_HUBS; j++) {
            if (g->adjMatrix[i][j] != 0) {
                edges[edgeCount].src = i;
                edges[edgeCount].dest = j;
                edges[edgeCount].weight = g->adjMatrix[i][j];
                edgeCount++;
            }
        }
    }

    // Sort all edges in non-decreasing order of their weight
    qsort(edges, edgeCount, sizeof(Edge), compareEdges);

    //  Allocate memory for creating V subsets
    Subset* subsets = (Subset*)malloc(NUM_HUBS * sizeof(Subset));
    for (int v = 0; v < NUM_HUBS; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    Edge mstEdges[NUM_HUBS - 1]; 
    int e = 0;
    int i = 0;
    int totalCost = 0;

    printf("\n2. executing Kruskal's Algorithm (MST):\n");
    printf("-------------------------------------------------\n");
    printf("| Source | Dest | Cost | Action             |\n");
    printf("|--------|------|------|--------------------|\n");

    // Iterate through sorted edges
    while (e < NUM_HUBS - 1 && i < edgeCount) {
        Edge next_edge = edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        printf("|   %c    |   %c  |  %2d  | ", 
               g->hubNames[next_edge.src], 
               g->hubNames[next_edge.dest], 
               next_edge.weight);

        if (x != y) {
            mstEdges[e++] = next_edge;
            totalCost += next_edge.weight;
            unionSets(subsets, x, y);
            printf("Selected (Safe)      |\n");
        } else {
            printf("Discarded (Cycle)    |\n");
        }
    }
    printf("-------------------------------------------------\n");

    // Final Output
    printf("\n3. Selected Fiber-Optic Links (MST):\n");
    for (int j = 0; j < e; j++) {
        printf("   * Hub %c <--> Hub %c (Cost: %dM)\n", 
               g->hubNames[mstEdges[j].src], 
               g->hubNames[mstEdges[j].dest], 
               mstEdges[j].weight);
    }

    printf("\n4. Total Installation Cost: $%d Million\n", totalCost);
    free(subsets);
}
