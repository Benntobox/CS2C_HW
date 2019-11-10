// CS2C Assignment #6 Submission - Benny Boyle, 11/5/19
#include <iostream>
#include <cstdlib>
#include <array>
#include <stdio.h>

#include "FHhashQP.h"
#include "EBookEntry.h"

using namespace std;


// --------------------------- Global Prototypes ---------------------------

int getKey( const EBookEntry & item); // used for ID equality
// string getKey( const EBookEntry & item); // used for title equality

int Hash(const EBookEntry & key);
int Hash(const string & key);
int Hash( int key );

// ---------------------------- Global Definitions -------------------------------

// used for ID equality
int getKey( const EBookEntry & item)
{
   return item.getETextNum() ;
}

/*
 // used for title equality
 string getKey( const EBookEntry & item )
 {
 return item.getTitle() ;
 }
 */

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

// ---------------------- FHhashQPwFind Prototype ----------------------

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

// -------------------- FHhashQPwFind Definitions -----------------------

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
          && getKey(this->mArray[index].data) != key )
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


// --------------------------------- Main ---------------------------------

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
         // book = hashTable.find( bookInput[ randomIndices[k] ].getTitle() );

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
      book = hashTable.find(hashTable.size()+1);
      // book = hashTable.find("Surge McQueen");

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

/* ------------------------------------ Runs ------------------------------------
 catalog-short4.txt
 550

 Displaying random books from bookInput vector:

 #:307 Blackwood's Edinburgh Magazine, Volume 58, Number 358, August 1845

 #:199 The War in the Air; Vol. 1
 The Part played in the Great War by the Royal Air Force

 #:473 The Iraq Study Group Report

 #:358 Histoire du Canada depuis sa découverte jusqu'à nos jours. Tome III

 #:30 Forever

 #:322 C'est la loi!

 #:244 Buttered Side Down: Stories

 #:528 A Confederate Girl's Diary

 #:273 Sleepy-Time Tales: the Tale of Fatty Coon

 #:59 College Teaching
 Studies in Methods of Teaching in the College

 #:490 Le Tour du Monde; Scandinavie
 Journal des voyages et des voyageurs; 2. sem. 1860

 #:215 Blackwood's Edinburgh Magazine, Volume 59, No. 363, January, 1846

 #:142 Poems

 #:192 The Pecan and its Culture

 #:437 Left Guard Gilbert

 #:403 Fruits of Queensland

 #:177 Shipwreck in the Sky

 #:379 A Pessimist
 In Theory and Practice

 #:240 Old Groans and New Songs
 Being Meditations on the Book of Ecclesiastes

 #:312 The Flower Basket
 A Fairy Tale

 #:303 Wilson's Tales of the Borders and of Scotland, Volume VI

 #:469 Correspondance de Voltaire avec le roi de Prusse

 #:309 The Arrow-Maker
 A Drama in Three Acts

 #:507 Der Judenstaat. English

 #:510 Surpreza
 Entre-acto original


 The same random books from the hash table

 #:307 Blackwood's Edinburgh Magazine, Volume 58, Number 358, August 1845

 #:199 The War in the Air; Vol. 1
 The Part played in the Great War by the Royal Air Force

 #:473 The Iraq Study Group Report

 #:358 Histoire du Canada depuis sa découverte jusqu'à nos jours. Tome III

 #:30 Forever

 #:322 C'est la loi!

 #:244 Buttered Side Down: Stories

 #:528 A Confederate Girl's Diary

 #:273 Sleepy-Time Tales: the Tale of Fatty Coon

 #:59 College Teaching
 Studies in Methods of Teaching in the College

 #:490 Le Tour du Monde; Scandinavie
 Journal des voyages et des voyageurs; 2. sem. 1860

 #:215 Blackwood's Edinburgh Magazine, Volume 59, No. 363, January, 1846

 #:142 Poems

 #:192 The Pecan and its Culture

 #:437 Left Guard Gilbert

 #:403 Fruits of Queensland

 #:177 Shipwreck in the Sky

 #:379 A Pessimist
 In Theory and Practice

 #:240 Old Groans and New Songs
 Being Meditations on the Book of Ecclesiastes

 #:312 The Flower Basket
 A Fairy Tale

 #:303 Wilson's Tales of the Borders and of Scotland, Volume VI

 #:469 Correspondance de Voltaire avec le roi de Prusse

 #:309 The Arrow-Maker
 A Drama in Three Acts

 #:507 Der Judenstaat. English

 #:510 Surpreza
 Entre-acto original

 Item not found
 Item not found
 Item not found

 Book not yet removed:
 The Higher Powers of Mind and Spirit

 Removing the book and trying again:
 Item not found
 Program ended with exit code: 0
 -------------------------------------------------------------------------------*/


