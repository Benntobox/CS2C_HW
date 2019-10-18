//
//  main.cpp
//  CS2C_Assignment3
//
//  Created by Benjamin Boyle on 10/13/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//
// CS2C Assignment #3 Submission - Benny Boyle, 10/8/19

#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

// ------------------------- Global Scope Definitions --------------------------

const int MAT_SIZE = 50;

typedef float* DynMat[MAT_SIZE];

DynMat mDyn, nDyn, ansDyn;

void matMultDyn( const DynMat & matA,  const DynMat & matB, DynMat & matC, int size)
{
   int r, c, i;
   float totalVal;
   for (r = 0; r < size; r++)
   {
      for (c = 0; c < size; c++)
      {
         totalVal = 0;
         for (i = 0; i < size; i++)
         {
            totalVal += matA[r][i] * matB[i][c];
         }
         matC[r][c] = totalVal;
      }
   }
}

void matShowDyn( const DynMat & matA, int start, int size)
{
   int r, c, end;
   end = start + size;
   for(r = start; r < end; r++)
   {
      for(c = start; c < end; c++)
      {
         cout << fixed << setprecision(2) << matA[r][c] << " ";
      }
      cout << endl;
   }
   cout << endl;
}

// ------------------------------------ Main ------------------------------------

int main()
{
   int r, c;
   clock_t startTime, stopTime;
   float randFrac;
   int randRow, randCol, smallPercent;

   // non-sparse dynamic matrix
   DynMat matDyn, matDynAns;

   // allocate rows and initialize to 0
   for (r = 0; r < MAT_SIZE; r++)
   {
      float* matDynRow = new float[MAT_SIZE];
      float* matDynAnsRow = new float[MAT_SIZE];
      for (c = 0; c < MAT_SIZE; c++)
      {
         matDynRow[c] = 0;
         matDynAnsRow[c] = 0;
      }
      matDyn[r] = matDynRow;
      matDynAns[r] = matDynAnsRow;
   }

   // generate small% (bet .1 and 10%) non-default values (bet 0 and 1)
   smallPercent = MAT_SIZE/20. * MAT_SIZE;  // div by 20. means 5%, of course
   for (r = 0; r < smallPercent; r++)
   {
      randFrac = (rand() % 100);
      randRow = rand() % MAT_SIZE;
      randCol = rand() % MAT_SIZE;
      matDyn[randRow][randCol] = randFrac / 100;
   }

   // 10x10 submatrix in lower right
   matShowDyn(matDyn, MAT_SIZE - 10, 10);

   startTime = clock();  // ------------------ start
   matMultDyn(matDyn, matDyn, matDynAns, MAT_SIZE);
   stopTime = clock();  // ---------------------- stop

   matShowDyn(matDynAns, MAT_SIZE - 10, 10);
   cout << "\nSize = " <<  MAT_SIZE << " Dyn Array Mult Elapsed Time: "
   << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC
   << " seconds." << endl << endl;

   // clean up
   for (r = 0; r < MAT_SIZE; r++)
   {
      delete [] matDyn[r];
      delete [] matDynAns[r];
   }
   cout << endl;
}

/* ------------------------------------ Run -------------------------------------

 0.16 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.35 0.00
 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.72 0.00
 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00

 0.03 0.00 0.00 0.00 0.00 0.00 0.00 0.06 0.00 0.00
 0.08 0.00 0.57 0.00 0.00 0.00 0.00 0.00 0.75 0.00
 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
 0.29 0.00 0.00 0.00 0.00 0.00 0.33 0.00 0.00 0.00
 0.00 0.00 0.55 0.07 0.00 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.19 0.08 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.05 0.00 0.00 0.00 0.04 0.00 0.04
 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00


 Size = 50 Dyn Array Mult Elapsed Time: 0.00 seconds.


 Program ended with exit code: 0
 -------------------------------------------------------------------------------*/

/* ---------------------------------- Writeup -----------------------------------

 Prior to running the code, my time complexity estimation of this code is as follows:

 Upper bound O(): O(M^3)
 Estimated Θ(): Θ(M^3)

 The inside of the longest time complexity loop is inside the actual multiplication
 function, matMultDyn(), which has three for loops inside it. Each of these loops is
 iterating from 0 to MAT_SIZE, aka M, and so the time complexity will be M * M * M.

 The estimated time complexity is equal to the upper bound, because this function will
 always iterate through every single possible value from 0 to M in each loop, so there
 will be no reduction due to values of 0. If this were to utilize the sparseMatrix
 from last lab, where default values were skipped, it is likely the estimated time
 would be much shorter, but this program iterates over all values always.

 Reflection questions:

 1. The smallest value of M that gave a non-zero time was M = 110

 2.
 ------------------------------
 - Value of M --- Time taken --
 ------------------------------
 -    30      ---    0.00    --
 ------------------------------
 -    50      ---    0.00    --
 ------------------------------
 -    100     ---    0.00    --
 ------------------------------
 -    110     --—    0.01    --
 ------------------------------
 -    200     ---    0.04    --
 ------------------------------
 -    250     ---    0.07    --
 ------------------------------
 -    300     ---    0.13    --
 ------------------------------
 -    400     ---    0.38    --
 ------------------------------
 -    500     --—    0.71    --
 ------------------------------
 -    600     ---    1.20    --
 ------------------------------
 -    700     ---    1.78    --
 ------------------------------
 -    800     ---    2.95    --
 ------------------------------
 -    900     --—    4.28    --
 ------------------------------
 -    1000    ---    7.54    --
 ------------------------------
 -    1250    --—    12.37   --
 ------------------------------
 -    1500    --—    21.60   --
 ------------------------------
 -    1600    --—    28.80   --
 ------------------------------
 -    2000    --—    97.00   --
 ------------------------------


 3. After reaching almost two minutes at M = 2000, I decided that going further would
 be impractical, and it seemed like the accuracy of the time was growing questionable.
 Additionally, due to the size of the memory needed, the program was increasingly
 writing to the disk instead of using RAM, which is what I suspect caused the time to
 be significantly off what I had estimated it to be.

 4. Using the values of M as 200, 400, 800, and 1600, it can be safely estimated that
 the time increase matches the time complexity of O(M^3). When M is doubled, the
 expected time should increase by 2^3, or 8 times, and that does seem to be shown here.
 200 -> .04, 400 -> .38, 800 -> 2.95, 1600 -> 28.80, each time M is doubled, the time
 taken increase roughly 8 times. For M sizes over 1000, data was being written to disk,
 which may have had an impact on time taken, and increased variance in the results.

 -------------------------------------------------------------------------------*/
