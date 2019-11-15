//
//  main.cpp
//  CS2C_Assignment7
//
//  Created by Benjamin Boyle on 11/9/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//

#include "FHvector.h"
#include "FHsort.h"
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <math.h>

using namespace std;

// shellSortX -- using shell's outer loop with given array
template <typename Comparable>
void shellSortX( FHvector<Comparable> & a, int gapArray[], int gapArraySize )
{
   int j, k, pos, arraySize, gap = 0;
   Comparable tmp;
   arraySize = a.size();

   for (j = gapArraySize - 1; j >= 0; j--) // outer gap loop
   {
      gap = gapArray[j];
      for( pos = gap ; pos < arraySize; pos++ )  // middle loop (outer of "insertion-sort")
      {
         tmp = a[pos];
         for(k = pos; k >= gap && tmp < a[k - gap]; k -= gap )   // inner loop
            a[k] = a[k - gap];
         a[k] = tmp;
      }
   }
}

// used to check if array was actually sorted
void printFirstTen(FHvector<int> & sortedArray)
{
   cout << "First 10 values of array: " << endl;
   for (int i = 0; i < 10; i++)
   {
      cout << sortedArray.at(i) << " ";
   }
   cout << endl;
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
      fhVectorOfInts1.push_back(arrayOfInts[k]);
      fhVectorOfInts2.push_back(arrayOfInts[k]);
      fhVectorOfInts3.push_back(arrayOfInts[k]);
      fhVectorOfInts4.push_back(arrayOfInts[k]);
   }

   printFirstTen(fhVectorOfInts1);

   // explicit gap array
   int gapArraySize = 21;
   int gapArray[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
      2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
      1048576};

   // sedgewick array calculation
   int sedgewickArraySize = 20;
   int sedgewickArray[sedgewickArraySize];  // to be computed using formulas
   for (k = 0; k < sedgewickArraySize; k++)
   {
      if (k%2==0) { sedgewickArray[k] = 9 * ( pow(2, k) - pow(2, (k/2)) ) + 1; }
      else { sedgewickArray[k] = 8 * pow(2, k) - 6 * pow(2, ((k+1)/2)) + 1; }
   }

   // my best attempt for gap sizes: 4^k + 3k + 1
   int myGapArraySize = 12;
   int myGapArray[myGapArraySize];
   myGapArray[0] = 1;
   for (k = 1; k < myGapArraySize; k++)
   {
      myGapArray[k] = pow(4, k) + 3*k + 1;
   }

   clock_t startTime, stopTime;

   startTime = clock();  // ------------------ start

   shellSort1(fhVectorOfInts1);  // time this

   stopTime = clock();  // ---------------------- stop
   cout << "\nShellsort1 Elapsed Time: "
   << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
   << " seconds." << endl << endl;
   printFirstTen(fhVectorOfInts1);

   startTime = clock();  // ------------------ start

   shellSortX(fhVectorOfInts2, gapArray, gapArraySize);  // time this

   stopTime = clock();  // ---------------------- stop
   cout << "\nShellsort with gapArray Elapsed Time: "
   << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
   << " seconds." << endl << endl;
   printFirstTen(fhVectorOfInts2);

   startTime = clock();  // ------------------ start

   shellSortX(fhVectorOfInts3, sedgewickArray, sedgewickArraySize);  // time this

   stopTime = clock();  // ---------------------- stop
   cout << "\nShellsort with sedgwickArray Elapsed Time: "
   << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
   << " seconds." << endl << endl;
   printFirstTen(fhVectorOfInts3);

   startTime = clock();  // ------------------ start

   shellSortX(fhVectorOfInts4, myGapArray, myGapArraySize);  // time this

   stopTime = clock();  // ---------------------- stop
   cout << "\nShellsort with myGapArray Elapsed Time: "
   << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
   << " seconds." << endl << endl;
   printFirstTen(fhVectorOfInts4);
}

/* ----------------------- Runs and Results ---------------------------
 First 10 values of array:
 16807 25249 73 43658 8930 11272 27544 878 27923 37709

 Shellsort1 Elapsed Time: 0.053239 seconds.

 First 10 values of array:
 0 0 1 2 4 5 5 5 6 6

 Shellsort with gapArray Elapsed Time: 0.118883 seconds.

 First 10 values of array:
 0 0 1 2 4 5 5 5 6 6

 Shellsort with sedgwickArray Elapsed Time: 0.028455 seconds.

 First 10 values of array:
 0 0 1 2 4 5 5 5 6 6

 Shellsort with myGapArray Elapsed Time: 0.026541 seconds.

 First 10 values of array:
 0 0 1 2 4 5 5 5 6 6
 Program ended with exit code: 0

 ------------------------------- RESULTS -------------------------------
_________________________________________________________________________
Array Size  | ShellSort1  | Explicit Gap   | Sedgewick   | MyGapSequence
5,000       | 0.0029      | 0.0063         | 0.0021      | 0.0021
10,000      | 0.0083      | 0.0134         | 0.0055      | 0.0057
20,000      | 0.0156      | 0.0464         | 0.0118      | 0.0122
50,000      | 0.0378      | 0.1069         | 0.0290      | 0.0267
100,000     | 0.0893      | 0.3412         | 0.0575      | 0.0599
131,073     | 0.3724      | 0.3609         | 0.0774      | 0.0778
150,000     | 0.1403      | 0.4717         | 0.0957      | 0.0959
200,000     | 0.2436      | 0.7487         | 0.1293      | 0.1320
500,000     | 0.5793      | 2.8844         | 0.3490      | 0.3597
524,289     | 3.0947      | 3.0977         | 0.3577      | 0.3783
1,000,000   | 1.2208      | 11.0928        | 0.7470      | 0.8270
_________________________________________________________________________

 Q: Why does Shell's gap sequence implied by shellSort1() give a different
   timing result than the explicit array described above and passed to
   shellSortX()?  Which is faster and why?

 A: shellSort1() is faster than shellSortX() with the given explicit array
   by a wide margin in general, frequently up to 3x faster, and only
   increasing as the array size increases. The reason for this is that in
   shellSort1(), the gap size is calculated off the given array size, and will
   be equal to halving the array size. shellSortX(), on the other hand, has a
   fixed set of values regardless of the size of the given array, which means
   for many array sizes, it will not align well and will waste significant
   time calculating the same values, and will likely miss up to half of them,
   thus requiring the final pass with a gap of 1 to change half or more. As
   can be seen when the array size is set to a value one higher than a value
   in the explicit array, such as 131,073 or 524,289, both shellSort1() and
   shellSortX() approach an almost equal time. This is demonstrating how the
   actual speed for both is essentially equal if the values derived from halving
   the size of the array is equal to the powers of 2. This is rarely the case,
   however, so for most array sizes, the explicit values are a poor choice, and
   highly inefficient.

-------------------------------------------------------------------- */
