//
//  FHSparseMat.h
//  CS2C_Assignment2
//
//  Created by Benjamin Boyle on 10/4/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//
#include <stdio.h>
#include "FHlist.h"
#include "FHvector.h"

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

template<class Object>
class SparseMat
{
protected:
   const int MINIMUM_SIZE = 1;
   typedef FHlist< MatNode<Object> > MatRow;
   typedef FHvector<MatRow> MasterCol;

   MasterCol rows;
   Object defaultVal;
   int rowSize, colSize;
public:
   SparseMat( int r, int c, const Object & defaultVal);
   const Object & get(int r, int c) const;
   bool set(int r, int c, const Object &x);
   void clear() ;
   void showSubSquare(int start, int size);

   class BoundsViolationError {};
};

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
   FHlist<MatNode<Object>> currRow = rows.at(r);
   class FHlist<MatNode<Object>>::const_iterator iter, currRowEnd;
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
   class FHlist<MatNode<Object>>::iterator iter, currRowEnd;
   FHlist<MatNode<Object>>* currRow = &rows.at(r);
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

