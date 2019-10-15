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
      randCol = rand() % MAT_SIZE;
      randRow = rand() % MAT_SIZE;
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
