//
//  FHSparseMat.h
//  CS2C_Assignment2
//
//  Created by Benjamin Boyle on 10/4/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//

#ifndef FHsparseMat
#define FHsparseMat

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
};

template<class Object>
SparseMat<Object>::SparseMat(int r, int c, const Object & defaultVal)
{
   rowSize = r;
   colSize = c;
   this->defaultVal = defaultVal;
   for (int k = 0; k < r; k++)
   {
      FHlist<MatNode<Object>> newRow = FHlist<MatNode<Object>>();
      rows.push_back(newRow);
   }
}

template<class Object>
const Object& SparseMat<Object>::get(int r, int c) const
{
   FHlist<MatNode<Object>> currRow = rows.at(r);
   class FHlist<MatNode<Object>>::iterator iter;
   class FHlist<MatNode<Object>>::iterator currRowEnd = currRow.end();
   for(iter = currRow.begin(); iter != currRowEnd; iter++)
   {
      if ((*iter).getCol() == c)
      {
         return (*iter).data;
      }
   }
   return defaultVal;
}

template<class Object>
bool SparseMat<Object>::set(int r, int c, const Object &x)
{
   FHlist<MatNode<Object>> currRow = rows.at(r);
   class FHlist<MatNode<Object>>::iterator iter;
   class FHlist<MatNode<Object>>::iterator currRowEnd = currRow.end();
   for(iter = currRow.begin(); iter != currRowEnd; iter++)
   {
      if ((*iter).getCol() == c)
      {
         (*iter) = x;
         return true;
      }
   }
   MatNode<Object> newNode = MatNode<Object>(c, x);
   for(iter = currRow.begin(); iter != currRowEnd; iter++)
   {
      if ((*iter).getCol() > c || iter++ == currRowEnd)
      {
         currRow.insert(iter, newNode);
         return true;
      }
   }
   return false;
}

template<class Object>
void SparseMat<Object>::clear()
{
   for(int k = 0; k < rowSize; k++)
   {
      rows.at(k).clear();
   }
}

#endif
