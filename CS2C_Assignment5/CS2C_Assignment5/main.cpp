//
//  main.cpp
//  CS2C_Assignment5
//
//  Created by Benjamin Boyle on 10/26/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//
#include "FHsplayTree.h"
#include <iostream>
using namespace std;

template <typename Object>
class PrintObject
{
public:
   void operator()(Object obj)
   {
      cout << obj << " ";
   }
};

int main()
{
   int k, k2;
   FHsplayTree<int> searchTree;
   PrintObject<int> intPrinter;

   searchTree.traverse(intPrinter);
   cout << "Starting root: " << searchTree.showRoot() << endl;

   cout << "Initial size: " << searchTree.size() << endl;
   for (k = 1; k <= 32; k++)
      searchTree.insert(k);
   cout << "New size: " << searchTree.size() << endl;

   cout << "\nTraversal: \n";
   searchTree.traverse(intPrinter);
   cout << endl << endl;

   for (k = -1; k < 13; k++)
   {
      // test contains()
      k2 = 10 - k;
      if ( !searchTree.contains( k2 ) )
         cout << " oops on contains " << k2 << endl;
      cout << "contains " << k2 << " --> root: " << searchTree.showRoot()
      << " height: " << searchTree.showHeight() << endl;

      // test find()
      try
      {
         searchTree.find(k);
      }
      catch( ... )
      {
         cout << " oops on find " << k << endl;
      }
      cout << "find " << k << " --> root: " << searchTree.showRoot()
      << " height: " << searchTree.showHeight() << endl;
   }

   // Testing remove
   cout << endl << "Removing several nodes" << endl;
   searchTree.remove(1);
   searchTree.remove(2);
   searchTree.remove(3);
   searchTree.remove(5);
   searchTree.remove(6);
   searchTree.remove(7);
   searchTree.remove(11);
   searchTree.remove(16);
   searchTree.remove(17);
   searchTree.remove(18);
   searchTree.remove(19);
   searchTree.remove(24);
   searchTree.remove(25);

   cout << "\nTraversal: \n";
   searchTree.traverse(intPrinter);
   cout << endl << endl;

   for (k = -1; k < 33; k++)
   {
      try
      {
         searchTree.find(k);
      }
      catch( ... )
      {
         cout << " oops ";
      }
      cout << "splay " << k << " --> root: " << searchTree.showRoot()
      << " height: " << searchTree.showHeight() << endl;
   }
   
   return 0;
}
