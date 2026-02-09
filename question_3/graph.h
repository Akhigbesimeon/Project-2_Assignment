#ifndef GRAPH_H
#define GRAPH_H

#define NUM_HUBS 7
#define INF 99999

// Edge structure for Kruskal's algorithm
typedef struct {
    int src;
    int dest;
    int weight;
} Edge;

// Graph structure
typedef struct {
    int adjMatrix[NUM_HUBS][NUM_HUBS];
    char hubNames[NUM_HUBS];
} Graph;

// Function Prototypes

// Initialize the graph
void initGraph(Graph *g);

// Add an edge to the adjacency matrix
void addEdge(Graph *g, int srcIndex, int destIndex, int weight);

// Display the Adjacency Matrix
void printAdjMatrix(Graph *g);

// Execute Kruskal's Algorithm to find and print the MST
void runKruskalsMST(Graph *g);

#endif
