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
   int Hash( const EBookEntry & item ) { return getKey(item); }

   const Object find(const KeyType & key);
   int findPosKey( const KeyType & key ) const;
   int myHashKey(const KeyType & key) const;
public:
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
          && this->mArray[index].data != key )
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
   int index = findPosKey(key);
   if ( this->mArray[index].state == FHhashQP<Object>::ACTIVE )
      return this->mArray[index];
   throw FHhashQPwFind::NotFoundException();
}


#endif /* FHhashQPwFind_h */
