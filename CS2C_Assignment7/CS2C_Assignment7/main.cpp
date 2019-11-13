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
#include <math.h>

using namespace std;

// shellSort #1 -- using shell's outer loop
template <typename Comparable>
void shellSort1( FHvector<Comparable> & a )
{
   int k, pos, arraySize, gap;
   Comparable tmp;

   arraySize = a.size();
   for (gap = arraySize/2;  gap > 0;  gap /= 2)  // outer gap loop
      for( pos = gap ; pos < arraySize; pos++ )  // middle loop (outer of "insertion-sort")
      {
         tmp = a[pos];
         for(k = pos; k >= gap && tmp < a[k - gap]; k -= gap )   // inner loop
            a[k] = a[k - gap];
         a[k] = tmp;
      }
}

// shellSortX -- using shell's outer loop with given array
template <typename Comparable>
void shellSortX( FHvector<Comparable> & a, int gapArray[], int gapArraySize )
{
   int j, k, pos, arraySize, gap = 0;
   Comparable tmp;
   arraySize = a.size();

   for (j = gapArraySize; j > 0; j--) // outer gap loop
      gap = gapArray[j];
      for( pos = gap ; pos < arraySize; pos++ )  // middle loop (outer of "insertion-sort")
      {
         tmp = a[pos];
         for(k = pos; k >= gap && tmp < a[k - gap]; k -= gap )   // inner loop
            a[k] = a[k - gap];
         a[k] = tmp;
      }
}

int main()
{
#define ARRAY_SIZE 50000
   int k;

   FHvector<int> fhVectorOfInts1;
   FHvector<int> fhVectorOfInts2;
   FHvector<int> fhVectorOfInts3;
   FHvector<int> fhVectorOfInts4;

   int arrayOfInts[ARRAY_SIZE];

   // build an array and two vector for comparing sorts
   for (k = 0; k < ARRAY_SIZE; k++)
   {
      arrayOfInts[k] = rand()%ARRAY_SIZE;
      if (k < 10) { cout << arrayOfInts[k] << " "; }
      fhVectorOfInts1.push_back(arrayOfInts[k]);
      fhVectorOfInts2.push_back(arrayOfInts[k]);
      fhVectorOfInts3.push_back(arrayOfInts[k]);
      fhVectorOfInts4.push_back(arrayOfInts[k]);
   }

   int gapArraySize = 21;
   int gapArray[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
      2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
      1048576};

   int sedgewickArraySize = 27;
   int sedgewickArray[sedgewickArraySize];  // to be computed using formulas
   int sedgewickValue;
   for (k = 0; k <= sedgewickArraySize; k++)
   {
      if (k%2==0)
      {
         sedgewickValue = 9 * ( pow(2, k) - pow(2, (k/2)) ) + 1;
      }
      else
      {
         sedgewickValue = 8 * pow(2, k) - 6 * pow(2, ((k+1)/2)) + 1;
      }
      sedgewickArray[k] = sedgewickValue;
   }

   int myGapArraySize = 1;
   int myGapArray[] = { 1 };

   clock_t startTime, stopTime;


   startTime = clock();  // ------------------ start

   shellSort1(fhVectorOfInts1);  // time this

   stopTime = clock();  // ---------------------- stop
   cout << "\nShellsort1 Elapsed Time: "
   << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
   << " seconds." << endl << endl;

   startTime = clock();  // ------------------ start

   shellSortX(fhVectorOfInts2, gapArray, gapArraySize);  // time this

   stopTime = clock();  // ---------------------- stop
   cout << "\nShellsort with gapArray Elapsed Time: "
   << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
   << " seconds." << endl << endl;

   startTime = clock();  // ------------------ start

   shellSortX(fhVectorOfInts3, sedgewickArray, sedgewickArraySize);  // time this

   stopTime = clock();  // ---------------------- stop
   cout << "\nShellsort with sedgwickArray Elapsed Time: "
   << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
   << " seconds." << endl << endl;

   cout << "Testing values before: ";
   for (k = 0; k < 10; k++)
   {
      cout << fhVectorOfInts4[k] << " ";
   }
   cout << endl;

   startTime = clock();  // ------------------ start

   shellSortX(fhVectorOfInts4, myGapArray, myGapArraySize);  // time this

   stopTime = clock();  // ---------------------- stop
   cout << "\nShellsort with myGapArray Elapsed Time: "
   << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
   << " seconds." << endl << endl;

   cout << "Testing values after: ";
   for (k = 0; k < 10; k++)
   {
      cout << fhVectorOfInts4[k] << " ";
   }
   cout << endl;

}
