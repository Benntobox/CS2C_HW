//
//  main.cpp
//  CS2C_Assignment6
//
//  Created by Benjamin Boyle on 11/3/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//

#include <iostream>
#include "EBookEntry.h"
#include "FHhashQPwFind.h"
#include <cstdlib>
#include <array>

using namespace std;

// ----------- prototypes -------------

int getKey( const EBookEntry & item);
// string getKey( const EBookEntry & item);

int Hash(const EBookEntry & key);
int Hash(const string & key);
int Hash( int key );

void display( const EBookEntry & item )
{
   cout << "'" << item.getTitle() << "', by ";
   cout << item.getCreator() << ", in " << item.getSubject();
   cout << ", #" << item.getETextNum() << endl;
}

int main()
{

   //...

   FHhashQPwFind<EBookEntry, int> hashTable; // for ID equality
   // FHhashQPwFind<EBookEntry, string> hashTable; // for any string equality
   EBookEntry book;
   int k;

   EBookEntryReader bookInput = EBookEntryReader("catalog-short4.txt");


   // we want two books to be identical in different ways:  ID or author
   EBookEntry::setSortType(EBookEntry::SORT_BY_ID);
   // EBookEntry::setSortType(EBookEntry::SORT_BY_CREATOR);

   cout << bookInput.getFileName() << endl;
   cout << bookInput.getNumBooks() << endl;


   //...

   // create a QP hash table of EBooks ...
   // generate some random indices into the EBookEntryReader vector ...
   // insert all books into the hash table (if SORT_BY_ID) or fewer (If SORT_BY_CREATOR) ...
   // display NUM_RANDOM_INDICES books from array ...

   //...

   int NUM_RANDOM_INDICES = 25;
   int randomIndices[NUM_RANDOM_INDICES];

   for (k = 0; k < NUM_RANDOM_INDICES; k++)
   {
      randomIndices[k] = rand() % bookInput.getNumBooks();
   }

   for (k = 0; k < NUM_RANDOM_INDICES; k++)
   {
      hashTable.insert( bookInput[ randomIndices[k] ] );
   }

   // attempt to find on the selected key
   cout << "The same random books from the hash table " << endl;
   for (int k = 0; k < NUM_RANDOM_INDICES; k++)
   {
      try
      {
         book = hashTable.find( bookInput[ randomIndices[k] ].getETextNum() );
         // book = hashTable.find( bookInput[ randomIndices[k] ].getCreator() );

         cout << book.getTitle() << book.getCreator() << book.getSubject() << endl;
         //cout << (hashTable.contains( bookInput [randomIndices[k] ])? "YES\n": "NO\n");

      }
      catch (...)
      {
         cout << "no.  ";
      }
      cout << endl;
   }

   // test known failures exceptions:
   try
   {
      //book = hashTable.find( -3 );
      // book = hashTable.find( "Jack Kerouac" );

      //...

   }
   catch (...)
   {
      cout << "no.  ";
   }

   // more failures

   try
   {

   }
   catch (...)
   {

   }

   try
   {

   }
   catch (...)
   {

   }
}


/*
 // used for author equality
 string getKey( const EBookEntry & item )
 {
 return item.getCreator() ;
 }
 */

// used for ID equality
int getKey( const EBookEntry & item)
{
   return item.getETextNum() ;
}

int Hash( const EBookEntry & item )
{
   return Hash(getKey(item));
}

int Hash( const string & key )
{
   unsigned int k, retVal = 0;
   for(k = 0; k < key.length( ); k++ )
      retVal = 37 * retVal + key[k];
   return retVal;
}

int Hash( int key )
{
   return key;
}

