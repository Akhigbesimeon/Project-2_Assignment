#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"

// Helper Functions 

int getIndex(Graph *g, char name) {
    for (int i = 0; i < g->numNodes; i++) {
        if (g->nodeNames[i] == toupper(name)) return i;
    }
    return -1;
}


void printPath(int parent[], int current, Graph *g) {
    if (parent[current] == -1) {
        printf("%c", g->nodeNames[current]);
        return;
    }
    printPath(parent, parent[current], g);
    printf(" -> %c", g->nodeNames[current]);
}

// Initialize Graph
void initGraph(Graph *g) {
    g->numNodes = MAX_NODES;
    g->numEdges = 0;
    char names[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    for (int i = 0; i < MAX_NODES; i++) {
        g->nodeNames[i] = names[i];
    }
}

// Add Edge
void addEdge(Graph *g, int src, int dest, int weight) {
    g->edges[g->numEdges].src = src;
    g->edges[g->numEdges].dest = dest;
    g->edges[g->numEdges].weight = weight;
    g->numEdges++;

    g->edges[g->numEdges].src = dest;
    g->edges[g->numEdges].dest = src;
    g->edges[g->numEdges].weight = weight;
    g->numEdges++;
}

// Execute Bellman-Ford Algorithm
void runBellmanFord(Graph *g, char startNodeName) {
    int src = getIndex(g, startNodeName);
    if (src == -1) {
        printf("Error: Invalid Start Node.\n");
        return;
    }

    int dist[MAX_NODES];
    int parent[MAX_NODES];

    // Initialize distances
    for (int i = 0; i < MAX_NODES; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[src] = 0;

     Relax edges |V| - 1 times
    for (int i = 1; i < g->numNodes; i++) {
        for (int j = 0; j < g->numEdges; j++) {
            int u = g->edges[j].src;
            int v = g->edges[j].dest;
            int w = g->edges[j].weight;

            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    // Check for Negative-Weight Cycles
    for (int j = 0; j < g->numEdges; j++) {
        int u = g->edges[j].src;
        int v = g->edges[j].dest;
        int w = g->edges[j].weight;

        if (dist[u] != INF && dist[u] + w < dist[v]) {
            printf("\n[CRITICAL ALERT] Negative-weight cycle detected!\n");
            printf("Risk assessment unstable due to exploitable loop.\n");
            return;
        }
    }

    // Print Results
    printf("\n-- TRANSACTION RISK ANALYSIS (FROM BRANCH %c) --\n", startNodeName);
    printf("-----------------------------------------------------\n");
    printf("| Dest | Min Cost | Shortest Path                   |\n");
    printf("|------|----------|---------------------------------|\n");

    for (int i = 0; i < g->numNodes; i++) {
        printf("|  %c   |    ", g->nodeNames[i]);
        if (dist[i] == INF) {
            printf("UNR   | Unreachable");
        } else {
            printf("%2d    | ", dist[i]);
            printPath(parent, i, g);
        }
        printf("\n");
    }
    printf("-----------------------------------------------------\n");
}
