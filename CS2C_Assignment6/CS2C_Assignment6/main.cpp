//
//  main.cpp
//  CS2C_Assignment6
//
//  Created by Benjamin Boyle on 11/3/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//

#include <iostream>
#include "EBookEntry.h"
#include <cstdlib>
#include <array>

using namespace std;

// ------------------------------ Prototypes ------------------------------

int getKey( const EBookEntry & item);
// string getKey( const EBookEntry & item);

int Hash(const EBookEntry & key);
int Hash(const string & key);
int Hash( int key );

// --------------------------------- Main ---------------------------------

#include "FHhashQPwFind.h"

int main()
{
   EBookEntry book;
   int k;
   int NUM_RANDOM_INDICES = 25;
   int randomIndices[NUM_RANDOM_INDICES];

   FHhashQPwFind<EBookEntry, int> hashTable; // for ID equality
   // FHhashQPwFind<EBookEntry, string> hashTable; // for any string equality

   EBookEntryReader bookInput = EBookEntryReader("catalog-short4.txt");

   // we want two books to be identical in different ways:  ID or author
   EBookEntry::setSortType(EBookEntry::SORT_BY_ID);
   // EBookEntry::setSortType(EBookEntry::SORT_BY_TITLE);

   cout << bookInput.getFileName() << endl;
   cout << bookInput.getNumBooks() << endl;

   // Inserting books into hashTable
   for (k = 0; k < bookInput.getNumBooks(); k++)
   {
      hashTable.insert(bookInput[k]);
   }

   // Generating random numbers into randomIndices array
   for (k = 0; k < NUM_RANDOM_INDICES; k++)
   {
      randomIndices[k] = rand() % bookInput.getNumBooks();
   }

   cout << "\nDisplaying random books from bookInput vector:\n" << endl;
   for (k = 0; k < NUM_RANDOM_INDICES; k++)
   {
      cout << "#:" << randomIndices[k] << " " << bookInput[ randomIndices[k] ].getTitle();
      cout << endl << endl;
   }

   // attempt to find on the selected key
   cout << "\nThe same random books from the hash table \n" << endl;
   for (int k = 0; k < NUM_RANDOM_INDICES; k++)
   {
      try
      {
         book = hashTable.find( bookInput[ randomIndices[k] ].getETextNum() );
         // book = hashTable.find( getKey( bookInput[ randomIndices[k] ] ));

         cout << "#:" << randomIndices[k] << " " << book.getTitle() << endl;
      }
      catch (...)
      {
         cout << "Item not found\n";
      }
      cout << endl;
   }

   // test known failures exceptions:
   try
   {
      book = hashTable.find( -3 );
      // book = hashTable.find( "Jack Kerouac" );

      cout << book.getTitle() << endl;

   }
   catch (...)
   {
      cout << "Item not found\n";
   }

   // more failures

   try
   {
      book = hashTable.find(10000000);
      // book = hashTable.find("XXXXXXXXX");

      cout << book.getTitle() << endl;

   }
   catch (...)
   {
      cout << "Item not found\n";
   }

   try
   {
      book = hashTable.find(1);
      // book = hashTable.find("Surge McQueen");

      cout << book.getTitle() << endl;
   }
   catch (...)
   {
      cout << "Item not found\n";
   }
}

// ---------------------------- Global Definitions -------------------------------
/*
 // used for title equality
 string getKey( const EBookEntry & item )
 {
    return item.getTitle() ;
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
