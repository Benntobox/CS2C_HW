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

template<class Node>
class SparseMatrix
{

};

#endif
