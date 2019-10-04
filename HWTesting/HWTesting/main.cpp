//
//  main.cpp
//  HWTesting
//
//  Created by Benjamin Boyle on 9/25/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//

// FHgraph and djikstra algorithm
// CS 2C Foothill College

#include <iostream>
using namespace std;
#include "FHvector.h"
#include <vector>
#include <string>
using namespace std;

#include "FHvector.h"

// --------------- main ---------------
#define MAX_SIZE 100000

int main()
{
   int k;
   double avg;

   // use [] to write to a pre-allocated FHvector
   FHvector<int> vectorOf_FH_ints(MAX_SIZE);

   for (k = 0; k < MAX_SIZE; k++)
      vectorOf_FH_ints[k] = k;

   for (k = 0, avg = 0.; k < MAX_SIZE; k++)
      avg += vectorOf_FH_ints[k];
   avg /= MAX_SIZE;
   cout << endl << "The average is: " << avg << endl;

   // use push_back() to write to an initially empty FHvector
   FHvector<int> vectorOf_FH_ints2;

   for (k = 0; k < MAX_SIZE; k++)
      vectorOf_FH_ints2.push_back(k);

   for (k = 0, avg = 0.; k < MAX_SIZE; k++)
      avg += vectorOf_FH_ints2[k];
   avg /= MAX_SIZE;
   cout << endl << "The average is: " << avg << endl;

   // chop off 50,000 items from the array:
   cout << endl << "Size before: " << vectorOf_FH_ints2.size() << endl;
   vectorOf_FH_ints2.resize(50000);
   cout << endl << "Size after: " << vectorOf_FH_ints2.size() << endl;

   // test front and back
   cout << endl << "First item: " << vectorOf_FH_ints2.front() << endl;
   cout << endl << "Last item: " << vectorOf_FH_ints2.back() << endl;

   // test pop_back() - should leave 30,000 elements in the vector
   for (k = 0; k < 20000; k++)
      vectorOf_FH_ints2.pop_back();
   cout << endl << "Last item after pop_backs: " << vectorOf_FH_ints2.back() << endl;

   // test range checking
   try
   {
      vectorOf_FH_ints2[0] = 27;
      vectorOf_FH_ints2[30001] = 27;
      vectorOf_FH_ints2[0] = -27;     // should never be reached
   }
   catch (FHvector<int>::OutOfBoundsException &e)
   {
      cout << "out-of-bounds detected \n";
   }
   cout << endl << "First item still 27? : " << vectorOf_FH_ints2.front() << endl;

   // test iterators
   FHvector<int>::iterator iter;
   for (iter = vectorOf_FH_ints2.begin(); iter != vectorOf_FH_ints2.end(); iter++)
   {
      if ( *iter % 5000 == 0)
         cout << *iter << endl;
   }

   cout << endl << "------------ end of FHvector test --------------- \n\n";

   return 0;
}

