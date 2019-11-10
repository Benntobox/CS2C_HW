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

// --------------------------- Global Prototypes ---------------------------

//int getKey( const EBookEntry & item); // used for ID equality
string getKey( const EBookEntry & item); // used for title equality

int Hash(const EBookEntry & key);
int Hash(const string & key);
int Hash( int key );

// ---------------------------- Global Definitions -------------------------------
/*
 // used for ID equality
 int getKey( const EBookEntry & item)
 {
 return item.getETextNum() ;
 }
 */

// used for title equality
string getKey( const EBookEntry & item )
{
   return item.getTitle() ;
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

// --------------------------------- Main ---------------------------------

#include "FHhashQPwFind.h"

int main()
{
   EBookEntry book;
   int k;
   int NUM_RANDOM_INDICES = 25;
   int randomIndices[NUM_RANDOM_INDICES];

   //FHhashQPwFind<EBookEntry, int> hashTable; // for ID equality
   FHhashQPwFind<EBookEntry, string> hashTable; // for any string equality

   EBookEntryReader bookInput = EBookEntryReader("catalog-short4.txt");

   // we want two books to be identical in different ways:  ID or author
   //EBookEntry::setSortType(EBookEntry::SORT_BY_ID);
   EBookEntry::setSortType(EBookEntry::SORT_BY_TITLE);

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
         //book = hashTable.find( bookInput[ randomIndices[k] ].getETextNum() );
         book = hashTable.find( bookInput[ randomIndices[k] ].getTitle() );

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
      //book = hashTable.find( -3 );
      book = hashTable.find( "Jack Kerouac" );

      cout << book.getTitle() << endl;

   }
   catch (...)
   {
      cout << "Item not found\n";
   }

   // more failures

   try
   {
      //book = hashTable.find(10000000);
      book = hashTable.find("XXXXXXXXX");

      cout << book.getTitle() << endl;

   }
   catch (...)
   {
      cout << "Item not found\n";
   }

   try
   {
      //book = hashTable.find(hashTable.size()+1);
      book = hashTable.find("Surge McQueen");

      cout << book.getTitle() << endl;
   }
   catch (...)
   {
      cout << "Item not found\n";
   }

   // Testing if removed books are no longer found
   EBookEntry bookToBeRemoved = bookInput[NUM_RANDOM_INDICES-1];
   cout << "\nBook not yet removed:" << endl;
   try
   {
      book = hashTable.find( getKey(bookToBeRemoved) );
      cout << book.getTitle() << endl;
   }
   catch (...)
   {
      cout << "Item not found\n";
   }

   cout << "\nRemoving the book and trying again:" << endl;
   hashTable.remove(bookToBeRemoved);

   try
   {
      book = hashTable.find( getKey(bookToBeRemoved) );
      cout << book.getTitle() << endl;
   }
   catch (...)
   {
      cout << "Item not found\n";
   }
}
