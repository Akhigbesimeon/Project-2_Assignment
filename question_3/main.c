#include <stdio.h>
#include "graph.h"

int main() {
    Graph network;
    initGraph(&network);

    printf("--- SMART CITY FIBER-OPTIC NETWORK OPTIMIZATION ---\n");

    // Edges
    addEdge(&network, 0, 1, 6);  
    addEdge(&network, 0, 3, 5);  
    addEdge(&network, 1, 2, 11); 
    addEdge(&network, 2, 3, 17); 
    addEdge(&network, 2, 6, 25); 
    addEdge(&network, 3, 4, 22); 
    addEdge(&network, 4, 5, 10); 
    addEdge(&network, 5, 6, 22);

    

    // Adjacency Matrix
    printAdjMatrix(&network);

    // Kruskal's MST, List Links, Total Cost
    runKruskalsMST(&network);

    return 0;
}
