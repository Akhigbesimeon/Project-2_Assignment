#include <stdio.h>
#include "graph.h"


// Main Function
int main() {
    Graph network;
    initGraph(&network);
    
    addEdge(&network, 0, 1, 6);  
    addEdge(&network, 0, 3, 5);  
    addEdge(&network, 1, 2, 11); 
    addEdge(&network, 2, 3, 17); 
    addEdge(&network, 2, 6, 25); 
    addEdge(&network, 3, 4, 22); 
    addEdge(&network, 4, 5, 10); 
    addEdge(&network, 5, 6, 22); 
    

    //  User Input Interface
    char suspect;
    printf("== ENTERPRISE CYBER INCIDENT FORENSICS ==\n");
    printf("Available Workstations: A, B, C, D, E, F, G\n");
    printf("Enter the suspected compromised workstation (ID): ");
    scanf(" %c", &suspect);

    // Perform Analysis
    bfsRiskAnalysis(&network, suspect);

    return 0;
}
