//
//  main.cpp
//  HWTesting
//
//  Created by Benjamin Boyle on 9/25/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//

// FHgraph and djikstra algorithm
// CS 2C Foothill College

#include <iostream>
#include <string>
using namespace std;

#include "FHgraph.h"

// string is the data of the vertex; int is the cost type of edges
// --------------- main ---------------
int main()
{
    // build graph
    FHgraph<string, int> myGraph1;
    myGraph1.addEdge("v1","v2", 2);    myGraph1.addEdge("v1","v4", 1);
    myGraph1.addEdge("v2","v4", 3);    myGraph1.addEdge("v2","v5", 10);
    myGraph1.addEdge("v3","v1", 4);    myGraph1.addEdge("v3","v6", 5);
    myGraph1.addEdge("v4","v3", 2);    myGraph1.addEdge("v4","v5", 2);
    myGraph1.addEdge("v4","v6", 8);    myGraph1.addEdge("v4","v7", 4);
    myGraph1.addEdge("v5","v7", 6);
    myGraph1.addEdge("v7","v6", 1);
    
    // for debugging - only works if cout << overloaded for data type
    myGraph1.showAdjTable();
    
    // dijkstra called from inside
    myGraph1.showDistancesTo("v2");
    cout << endl;
    
    myGraph1.showShortestPath("v2", "v3");
    myGraph1.showShortestPath("v2", "v6");
    myGraph1.showShortestPath("v2", "v7");
    cout << endl;
    
    return 0;
}
