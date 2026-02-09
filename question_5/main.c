#include <stdio.h>
#include "graph.h"

// Main Function
int main() {
    Graph bankNet;
    initGraph(&bankNet);

    printf("-- BANKING SYSTEM RISK ASSESSMENT --\n");

    addEdge(&bankNet, 0, 1, 4); 
    addEdge(&bankNet, 0, 3, 16); 
    addEdge(&bankNet, 1, 2, 6);  
    addEdge(&bankNet, 1, 3, 7); 
    addEdge(&bankNet, 2, 6, 9);  
    addEdge(&bankNet, 3, 4, 7); 
    addEdge(&bankNet, 3, 5, 3);  
    addEdge(&bankNet, 4, 5, 10); 
    addEdge(&bankNet, 4, 6, 2);  
    addEdge(&bankNet, 5, 6, 10); 
    addEdge(&bankNet, 6, 7, 13);

    runBellmanFord(&bankNet, 'A');

    return 0;
}
