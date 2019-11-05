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

// ----------- prototypes -------------

int getKey( const EBookEntry & item);
//string getKey( const EBookEntry & item);

int Hash(const EBookEntry & key);
int Hash(const string & key);
int Hash( int key );

void display(const EBookEntry & book);

#include "FHhashQPwFind.h"

int main()
{
   EBookEntry book;
   int k;
   int NUM_RANDOM_INDICES = 25;
   int randomIndices[NUM_RANDOM_INDICES];

   FHhashQPwFind<EBookEntry, int> hashTable; // for ID equality
   //FHhashQPwFind<EBookEntry, string> hashTable; // for any string equality

   EBookEntryReader bookInput = EBookEntryReader("catalog-short4.txt");

   // we want two books to be identical in different ways:  ID or author
   EBookEntry::setSortType(EBookEntry::SORT_BY_ID);
   //EBookEntry::setSortType(EBookEntry::SORT_BY_CREATOR);

   cout << bookInput.getFileName() << endl;
   cout << bookInput.getNumBooks() << endl;

   // create a QP hash table of EBooks ...
   // generate some random indices into the EBookEntryReader vector ...
   // insert all books into the hash table (if SORT_BY_ID) or fewer (If SORT_BY_CREATOR) ...
   // display NUM_RANDOM_INDICES books from array ...

   for (k = 0; k < bookInput.getNumBooks(); k++)
   {
      hashTable.insert(bookInput[k]);
   }

   for (k = 0; k < NUM_RANDOM_INDICES; k++)
   {
      randomIndices[k] = rand() % bookInput.getNumBooks();
      cout << randomIndices[k] << " ";
   }
   cout << endl;

   cout << "\nDisplaying random books from bookInput vector:\n" << endl;
   for (k = 0; k < NUM_RANDOM_INDICES; k++)
   {
      cout << bookInput[ randomIndices[k] ].getTitle();
      cout << endl;
   }

   cout << "\nDisplaying same books from hashTable:\n" << endl;
   for (k = 0; k < NUM_RANDOM_INDICES; k++)
   {
      cout << hashTable.find( getKey( bookInput[ randomIndices[k] ] ) ).getTitle();
      cout << endl;
   }

   // attempt to find on the selected key
   cout << "\nThe same random books from the hash table " << endl;
   for (int k = 0; k < NUM_RANDOM_INDICES; k++)
   {
      try
      {
         book = hashTable.find( bookInput[ randomIndices[k] ].getETextNum() );
         //book = hashTable.find( bookInput[ randomIndices[k] ].getCreator() );

         display(book);
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
      book = hashTable.find( -3 );
      //book = hashTable.find( "Jack Kerouac" );

      display(book);

   }
   catch (...)
   {
      cout << "no.  ";
   }

   // more failures

   try
   {
      book = hashTable.find(10000000);
      //book = hashTable.find("XXXXXXXXX");

      display(book);

   }
   catch (...)
   {
      cout << "Faioure.";
   }

   try
   {
      book = hashTable.find(hashTable.size()+3);
      //book = hashTable.find("Surge McQueen");

      display(book);
   }
   catch (...)
   {
      cout << "ALAS!";
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

void display(const EBookEntry & book)
{
   cout << "'" << book.getTitle() << "', by " << book.getCreator() << " in ";
   cout << book.getSubject() << ", #:" << book.getETextNum() << endl;
}
