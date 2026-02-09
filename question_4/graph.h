#ifndef GRAPH_H
#define GRAPH_H

#define MAX_NODES 7
#define MAX_NAME 10

// Graph structure
typedef struct {
    int adjMatrix[MAX_NODES][MAX_NODES]; 
    char nodeNames[MAX_NODES];           
    int numNodes;
} Graph;

// Function Prototypes

// Initialize graph
void initGraph(Graph *g);

// Add a weighted edge 
void addEdge(Graph *g, int srcIndex, int destIndex, int weight);

// BFS Logic
void bfsRiskAnalysis(Graph *g, char startNodeName);

#endif
