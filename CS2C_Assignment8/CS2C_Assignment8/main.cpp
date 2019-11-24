//
//  main.cpp
//  CS2C_Assignment8
//
//  Created by Benjamin Boyle on 11/24/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//

#include <iostream>
#include "FHsort.h"
#include <time.h>

using namespace std;

// quickSort internal
template <typename Comparable>
void quickSortX(FHvector<Comparable> & a, int left, int right, int recLimit)
{
   Comparable pivot;
   int i, j;

   if( left + recLimit <= right )
   {
      pivot = median3(a, left, right);
      for( i = left, j = right - 1; ; )
      {
         while( a[++i] < pivot )
            ;
         while( pivot < a[--j] )
            ;
         if( i < j )
            mySwapFH(a[i], a[j]);
         else
            break;
      }

      mySwapFH(a[i], a[right - 1]);  // restore pivot

      // recursive calls on smaller sub-groups
      quickSortX(a, left, i - 1, recLimit);
      quickSortX(a, i + 1, right, recLimit);
   }
   else
      // non-recursive escape valve - insertionSort
      insertionSort(a, left, right);
}

// quickSort public driver
template <typename Comparable>
void quickSortX( FHvector<Comparable> & a , int recLimit)
{
   if (recLimit < 2) recLimit = 2;
   quickSortX(a, 0, a.size() - 1, recLimit);
}

// --------------- main ---------------
#define ARRAY_SIZE 250000

int main()
{
   int k, recLimit;
   int arrayOfInts[ARRAY_SIZE];
   FHvector<int> fhVectorOfInts;
   FHvector<int> fhVectorOfInts2;
   clock_t startTime, stopTime;

   // build both an array and a vector for comparing sorts
   for (k = 0; k < ARRAY_SIZE; k++)
   {
      arrayOfInts[k] = rand() % ARRAY_SIZE;
      fhVectorOfInts.push_back(arrayOfInts[k]);
      fhVectorOfInts2.push_back(arrayOfInts[k]);
   }

   recLimit = 15;

   startTime = clock();  // ------------------ start
   quickSort(fhVectorOfInts);
   stopTime = clock();  // ---------------------- stop
   cout << "\nquickSort Elapsed Time: "
   << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
   << " seconds." << endl << endl;


   startTime = clock();  // ------------------ start
   quickSortX(fhVectorOfInts2, recLimit);
   stopTime = clock();  // ---------------------- stop
   cout << "\nquickSortX Elapsed Time: "
   << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
   << " seconds." << endl << endl;

   for (k = 0; k < ARRAY_SIZE; k+= ARRAY_SIZE/5)
   {
      cout << "quickSort #" << k << ": " << fhVectorOfInts[k] << endl;
      cout << "quickSortX #" << k << ": " << fhVectorOfInts2[k] << endl;
   }
   return 0;
}
