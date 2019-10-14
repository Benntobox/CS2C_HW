//
//  main.cpp
//  HWTesting
//
//  Created by Benjamin Boyle on 9/25/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//

// FHgraph and djikstra algorithm
// CS 2C Foothill College

// CS2C Assignment #2 Submission - Benny Boyle, 10/8/19

#include <stdio.h>
#include "FHlist.h"
#include "FHvector.h"
#include <iostream>
using namespace std;

// ------------------------- Defining MatNode --------------------------

template <class Object>
class MatNode
{
protected:
   int col;

public:
   Object data;
   // we need a default constructor for lists
   MatNode(int cl = 0, Object dt = Object()) : col(cl), data(dt) {}
   int getCol() const { return col; }

   // not optimized yet for set() = defaultVal;  refer to forums
   const Object & operator=( const Object &x ) { return (data = x);}
};

// ----------------------- Prototype of SparseMat ------------------------

template<class Object>
class SparseMat
{
protected:
   typedef FHlist< MatNode<Object> > MatRow;
   typedef FHvector<MatRow> MasterCol;

   MasterCol rows;
   Object defaultVal;
   int rowSize, colSize;
   const int MINIMUM_SIZE = 1;
public:
   SparseMat( int r, int c, const Object & defaultVal);
   const Object & get(int r, int c) const;
   bool set(int r, int c, const Object &x);
   void clear() ;
   void showSubSquare(int start, int size);

   class BoundsViolationError {};
};

// ------------------------ SparseMat Definitions -------------------------

template<class Object>
SparseMat<Object>::SparseMat(int r, int c, const Object & defaultVal)
{
   r >= MINIMUM_SIZE? rowSize = r : rowSize = MINIMUM_SIZE;
   c >= MINIMUM_SIZE? colSize = c : colSize = MINIMUM_SIZE;
   this->defaultVal = defaultVal;
   for (int k = 0; k < r; k++)
   {
      rows.push_back(MatRow());
   }
}

template<class Object>
const Object& SparseMat<Object>::get(int r, int c) const
{
   if (r >= rowSize || r < 0 || c >= colSize || c < 0) { throw BoundsViolationError(); }
   MatRow currRow = rows.at(r);
   class MatRow::const_iterator iter, currRowEnd;
   currRowEnd = currRow.end();
   for(iter = currRow.begin(); iter != currRowEnd; iter++)
   {
      if ((*iter).getCol() == c) { return (*iter).data; }
   }
   return defaultVal;
}

template<class Object>
bool SparseMat<Object>::set(int r, int c, const Object &x)
{
   if (r >= rowSize || r < 0 || c >= colSize || c < 0) { return false; }
   class MatRow::iterator iter, currRowEnd;
   MatRow* currRow = &rows.at(r);
   currRowEnd = currRow->end();
   for (iter = currRow->begin(); iter != currRowEnd; iter++)
   {
      if ((*iter).getCol() == c)
      {
         if (x == defaultVal) { currRow->erase(iter); }
         else { (*iter) = x; }
         return true;
      }
      else if ((*iter).getCol() > c) { break; }
   }
   if (x != defaultVal)
   {
      currRow->insert(iter, MatNode<Object>(c, x));
   }
   return true;
}

template<class Object>
void SparseMat<Object>::clear()
{
   for(int k = 0; k < rowSize; k++)
   {
      rows.at(k).clear();
   }
}

template<class Object>
void SparseMat<Object>::showSubSquare(int start, int size)
{
   int row, col;
   for(row = start; row < start+size; row++)
   {
      for (col = start; col < start+size; col++)
      {
         int matValue = this->get(row, col);
         if (to_string(matValue).size() == 1) { cout << " "; }
         cout << matValue << " ";
      }
      cout << endl;
   }
   cout << endl;
}

// ----------------------------- Main ------------------------------

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
   mat.set(9, 9, mat.get(3, 9));  // should copy the 21 here
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

   // testing clear() on above subSquare
   cout << "Testing clear():" << endl;
   mat.clear();
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

/* ---------------------------- RUNS ------------------------------
 0
 35
 21
 oops
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0 35  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0 21  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0 21  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0

 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0 99

 Value at 300, MAT_SIZE-1 is: 95
 Value at MAT_SIZE-1, 700 is: -3

 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0 -8  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0 31  0  0  0  0  0  0  0  0  0
 0  0  0  0 76 44 -7 19  0  0  0  0  0  0  0
 0  0  0  0  0 88  0  0  0  0  0  0  0  0  0
 0  0  0  0  0 31  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0

 Testing clear():
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0

 Out of bounds exception
 Out of bounds exception
 Program ended with exit code: 0
 ---------------------------------------------------------*/
