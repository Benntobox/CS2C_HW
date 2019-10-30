//
//  main.cpp
//  CS2C_Assignment5
//
//  Created by Benjamin Boyle on 10/26/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//

#include <iostream>
#include "FHsplayTree.h"

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
   int k;
   FHsplayTree<int> searchTree;
   //FHsearch_tree<int> searchTree;
   PrintObject<int> intPrinter;

   searchTree.traverse(intPrinter);
   //cout << searchTree.showRoot() << endl;

   cout << "Initial size: " << searchTree.size() << endl;
   for (k = 1; k <= 32; k++)
      searchTree.insert(k);
   cout << "New size: " << searchTree.size() << endl;

   cout << "\nTraversal: \n";
   searchTree.traverse(intPrinter);
   cout << endl << endl;

   for (k = -1; k < 10; k++)
   {
      searchTree.contains(k);
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

   cout << "Splaying at 25 = " << searchTree.find(25) << ", Root is: " <<
   searchTree.showRoot() << endl;

   searchTree.remove(1);
   searchTree.traverse(intPrinter);
   searchTree.remove(6);
   searchTree.traverse(intPrinter);
   searchTree.remove(11);
   searchTree.remove(16);
   searchTree.remove(17);
   searchTree.remove(18);
   searchTree.remove(19);
   searchTree.remove(24);
   searchTree.remove(25);

   for (k = -1; k < 10; k++)
   {
      searchTree.contains(k);
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
