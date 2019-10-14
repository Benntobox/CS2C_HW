//
//  main.cpp
//  CS2C_Assignment2
//
//  Created by Benjamin Boyle on 10/4/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//

#include <iostream>
using namespace std;
#include "FHsparseMat.h"

#define MAT_SIZE 100000
typedef SparseMat<float> SpMat;

int main()
{
   SpMat mat(MAT_SIZE, MAT_SIZE, 0); // 100000 x 100000 filled with 0

   // test mutators
   mat.set(2, 5, 10);
   mat.set(2, 5, 35);   // should overwrite the 10
   mat.set(3, 9, 21);
   mat.set(MAT_SIZE, 1, 5);  // should fail silently
   //mat.set(9, 9, mat.get(3, 9));  // should copy the 21 here
   mat.set(4,4, -9);
   mat.set(4,4, 0);   // should remove the -9 node entirely
   mat.set(MAT_SIZE-1, MAT_SIZE-1, 99);

   // test accessors and exceptions
   try
   {
      cout << mat.get(7, 8) << endl;
      cout << mat.get(2, 5) << endl;
      cout << mat.get(9, 9) << endl;
      cout << mat.get(-4, 7) << endl;  // should throw an exception
   }
   catch (...)
   {
      cout << "oops" << endl;
   }

   // show top left 15x15
   mat.showSubSquare(0, 15);

   // show bottom right 15x15
   mat.showSubSquare(MAT_SIZE - 15, 15);

   // additional given tests
   mat.set(300, MAT_SIZE-1, 95);
   mat.set(MAT_SIZE-1, 700, -3);

   // check positions too hard to display with showSubSquare()
   cout << "Value at 300, MAT_SIZE-1 is: " << mat.get(300, MAT_SIZE-1) << endl;
   cout << "Value at MAT_SIZE-1, 700 is: "<< mat.get(MAT_SIZE-1, 700) << endl << endl;

   // set more positions near 500, 500
   mat.set(500, 500, -1);
   mat.set(500, 500, 44);
   mat.set(499, 500, 31);
   mat.set(501, 500, 88);
   mat.set(502, 500, 31);
   mat.set(500, 502, 19);
   mat.set(498, 498, -8);
   mat.set(500, 501, -7);
   mat.set(500, 499, 76);

   // show positions near 500, 500
   mat.showSubSquare(495, 15);

   // various illegal values tested
   if (mat.set(300, MAT_SIZE+1, 33)) { cout << "Successfully set value outside range"; }
   if (mat.set(-1, 0, 1)) { cout << "Successfully set value outside range"; }
   if (mat.set(0, -200, 0)) { cout << "Successfully set value outside range"; }

   try
   {
      cout << mat.get(4, -8) << endl;
   }
   catch (...)
   {
      cout << "Out of bounds exception" << endl;
   }

   try
   {
      cout << mat.get(9, MAT_SIZE+1) << endl;
   }
   catch (...)
   {
      cout << "Out of bounds exception" << endl;
   }
}
