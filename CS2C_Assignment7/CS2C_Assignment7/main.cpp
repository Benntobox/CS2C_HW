//
//  main.cpp
//  CS2C_Assignment7
//
//  Created by Benjamin Boyle on 11/9/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//

#include "FHvector.h"
#include <stdio.h>
#include <iostream>
#include <time.h>

using namespace std;

// shellSort #1 -- using shell's outer loop
template <typename Comparable>
void shellSortX( FHvector<Comparable> & a, int gapArray[], int gapArraySize )
{
   int j, k, pos, gap;
   Comparable tmp;

   for (j = 0; j < gapArraySize; j++)// outer gap loop
      gap = gapArray[j];
      for( pos = gap ; pos < gapArraySize; pos++ )  // middle loop (outer of "insertion-sort")
      {
         tmp = a[pos];
         for(k = pos; k >= gap && tmp < a[k - gap]; k -= gap )   // inner loop
            a[k] = a[k - gap];
         a[k] = tmp;
      }
}

int main()
{
   #define ARRAY_SIZE 31250
   int k;

   FHvector<int> fhVectorOfInts1;
   FHvector<int> fhVectorOfInts2;
   int arrayOfInts[ARRAY_SIZE];

   // build an array and two vector for comparing sorts
   for (k = 0; k < ARRAY_SIZE; k++)
   {
      arrayOfInts[k] = rand()%ARRAY_SIZE;
      fhVectorOfInts1.push_back(arrayOfInts[k]);
      fhVectorOfInts2.push_back(arrayOfInts[k]);
   }

   int gapArray[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
      2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
      1048576};
   int gapArraySize = 21;

   int sedgewickArray[30];  // to be computed using formulas

   clock_t startTime, stopTime;
   startTime = clock();  // ------------------ start

   shellSortX(fhVectorOfInts1, gapArray, gapArraySize);  // time this

   stopTime = clock();  // ---------------------- stop
   cout << "\nShellsort with gapArray Elapsed Time: "
   << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
   << " seconds." << endl << endl;

}
