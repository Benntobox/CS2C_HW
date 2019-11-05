//
//  FHhashQPwFind.h
//  CS2C_Assignment6
//
//  Created by Benjamin Boyle on 11/3/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//

#ifndef FHhashQPwFind_h
#define FHhashQPwFind_h

#include "FHhashQP.h"
#include <stdio.h>

template <class Object, typename KeyType>
class FHhashQPwFind: public FHhashQP<Object>
{
protected:
   int findPosKey( const KeyType & key ) const;
   int myHashKey(const KeyType & key) const;
public:
   
   typename FHhashQP<EBookEntry>::HashEntry searchResult;
   const Object find(const KeyType & key);
   class NotFoundException {};
};

template <class Object, typename KeyType>
int FHhashQPwFind<Object, KeyType>::myHashKey(const KeyType & key) const
{
   int hashVal;

   hashVal = Hash(key) % this->mTableSize;
   if(hashVal < 0)
      hashVal += this->mTableSize;

   return hashVal;
}

template <class Object, typename KeyType>
int FHhashQPwFind<Object, KeyType>::findPosKey( const KeyType & key ) const
{
   int kthOddNum = 1;
   int index = myHashKey(key);

   while ( this->mArray[index].state != FHhashQP<Object>::EMPTY
          && Hash(this->mArray[index].data) != key )
   {
      index += kthOddNum;  // k squared = (k-1) squared + kth odd #
      kthOddNum += 2;   // compute next odd #
      if ( index >= this->mTableSize )
         index -= this->mTableSize;
   }

   return index;
}

template <class Object, typename KeyType>
const Object FHhashQPwFind<Object, KeyType>::find(const KeyType & key)
{
   searchResult = this->mArray[findPosKey(key)];
   if ( searchResult.state == FHhashQP<Object>::ACTIVE )
      return searchResult.data;
   throw FHhashQPwFind::NotFoundException();
}


#endif /* FHhashQPwFind_h */
