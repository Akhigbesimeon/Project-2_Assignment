#ifndef GRAPH_H
#define GRAPH_H

#define MAX_NODES 8  
#define MAX_EDGES 50  
#define INF 99999

// Edge structure
typedef struct {
    int src;
    int dest;
    int weight;
} Edge;

// Graph structure
typedef struct {
    Edge edges[MAX_EDGES];
    int numEdges;
    int numNodes;
    char nodeNames[MAX_NODES];
} Graph;

// Function Prototypes

// Initialize graph
void initGraph(Graph *g);

// Add an edge 
void addEdge(Graph *g, int src, int dest, int weight);

// Execute Bellman-Ford Algorithm
void runBellmanFord(Graph *g, char startNodeName);

#endif
