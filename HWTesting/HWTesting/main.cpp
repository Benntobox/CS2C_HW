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
using namespace std;

#include "FHgraph.h"

#include "Foothill_Sort.h"

// for timing our algorithms

#include <cstdlib>
#include <time.h>

// --------------- main ---------------
//#define ARRAY_SIZE 2000
int ARRAY_SIZE = 2000;

int main()
{
    int k;
    int arrayOfInts[ARRAY_SIZE];
    
    for (k = 0; k < ARRAY_SIZE; k++)
        arrayOfInts[k] = rand()%ARRAY_SIZE;
    
    // how we time our algorithms -------------------------
    clock_t startTime, stopTime;
    startTime = clock();
    
    // sort using a home made bubble sort (in Foothill_Sort.h)
    arraySort(arrayOfInts, ARRAY_SIZE);
    
    // how we determine the time elapsed -------------------
    stopTime = clock();
    
    // report algorithm time
    cout << "\nAlgorithm Elapsed Time: "
    << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC
    << " seconds." << endl << endl;
    
    return 0;
}
