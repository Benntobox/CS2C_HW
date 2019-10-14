//
//  main.cpp
//  CS2C_Assignment3
//
//  Created by Benjamin Boyle on 10/13/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//

#include <iostream>
using namespace std;

const int MAT_SIZE = 10000;

typedef float* DynMat[MAT_SIZE];

DynMat mDyn, nDyn, ansDyn;

void matMultDyn( const DynMat & matA,  const DynMat & matB, DynMat & matC, int size)
{
   
}

void matShowDyn( const DynMat & matA, int start, int size)
{
   int k, j, end;
   end = start + size;
   for(k = start; k < end; k++)
   {
      const float* row = matA[k];
      for(j = start; j < end; j++)
      {
         cout << row[j] << " ";
      }
      cout << endl;
   }
   cout << endl;
}

int main()
{
   int r, c;
   clock_t startTime, stopTime;
   double randFrac;
   int randRow, randCol, smallPercent;

   // non-sparse dynamic matrix
   DynMat matDyn, matDynAns;


   // allocate rows and initialize to 0
   for (r = 0; r < MAT_SIZE; r++)
   {
      // ??
      for (c = 0; c < MAT_SIZE; c++)
      {
         // ??
      }
   }

   // generate small% (bet .1 and 10%) non-default values (bet 0 and 1)
   smallPercent = MAT_SIZE/20. * MAT_SIZE;  // div by 20. means 5%, of course
   for (r = 0; r < smallPercent; r++)
   {
      // ??
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
      // ??

      cout << endl;
}
