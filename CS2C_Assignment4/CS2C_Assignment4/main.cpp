//
//  main.cpp
//  CS2C_Assignment4
//
//  Created by Benjamin Boyle on 10/17/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//
// Assignment #4 Instructor Solution
// CS 2C, Foothill College, Michael Loceff

// --------------- main ---------------

// CS 2C  Simple Search Tree Client - Lazy Deletion, int data
#include <iostream>
#include <string>
#include <stack>
#include "FHlazySearchTree.h"
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
   FHlazySearchTree<int> searchTree;
   PrintObject<int> intPrinter;

   searchTree.traverse(intPrinter);

   // testing min and max on empty tree
   try
   {
      cout << endl << "Min value of tree: " << searchTree.findMin() << endl;
      cout << "Max value of tree: " << searchTree.findMax() << endl;
   }
   catch(...)
   {
      cout << "Empty tree, no values for max or min" << endl;
   }

   cout << "\ninitial size: " << searchTree.size() << endl;
   searchTree.insert(50);
   searchTree.insert(20);
   searchTree.insert(30);
   searchTree.insert(70);
   searchTree.insert(10);
   searchTree.insert(60);
   cout << "After populating -- traversal and sizes: \n";
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
   << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << "Collecting garbage on new tree - should be no garbage." << endl;
   searchTree.collectGarbage();
   cout << "tree 1 size: " << searchTree.size()
   << "  Hard size: " << searchTree.sizeHard() << endl;

   // testing min and max on full tree
   cout << endl << "Min value of tree: " << searchTree.findMin() << endl;
   cout << "Max value of tree: " << searchTree.findMax() << endl;

   // test assignment operator
   FHlazySearchTree<int> searchTree2 = searchTree;

   cout << "\n\nAttempting 1 removal: \n";
   if (searchTree.remove(20))
      cout << "removed " << 20 << endl;
   cout << "tree 1 size: " << searchTree.size()
   << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << "Collecting Garbage - should clean 1 item. " << endl;
   searchTree.collectGarbage();
   cout << "tree 1 size: " << searchTree.size()
   << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << "Collecting Garbage again - no change expected. " << endl;
   searchTree.collectGarbage();
   cout << "tree 1 size: " << searchTree.size()
   << "  Hard size: " << searchTree.sizeHard() << endl;

   // test soft insertion and deletion:

   cout << "Adding 'hard' 22 - should see new sizes. " << endl;
   searchTree.insert(22);
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
   << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << "\nAfter soft removal. " << endl;
   searchTree.remove(22);
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
   << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << "Repeating soft removal. Should see no change. " << endl;
   searchTree.remove(22);
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
   << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << "Soft insertion. Hard size should not change. " << endl;
   searchTree.insert(22);
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
   << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << "\n\nAttempting 100 removals: \n";
   for (k = 100; k > 0; k--)
   {
      if (searchTree.remove(k))
         cout << "removed " << k << endl;
   }

   // testing min and max on soft deleted tree
   try
   {
      cout << endl << "Min value of tree: " << searchTree.findMin() << endl;
      cout << "Max value of tree: " << searchTree.findMax() << endl;
   }
   catch(...)
   {
      cout << "Empty tree, no values for max or min" << endl;
   }

   searchTree.collectGarbage();

   cout << "\nsearchTree now:\n";
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
   << "  Hard size: " << searchTree.sizeHard() << endl;

   searchTree2.insert(500);
   searchTree2.insert(200);
   searchTree2.insert(300);
   searchTree2.insert(700);
   searchTree2.insert(100);
   searchTree2.insert(600);

   cout << "\nsearchTree2:\n";
   searchTree2.traverse(intPrinter);
   cout << "\ntree 2 size: " << searchTree2.size()
   << "  Hard size: " << searchTree2.sizeHard() << endl;

   cout << endl << "Min value of tree: " << searchTree2.findMin() << endl;
   cout << "Max value of tree: " << searchTree2.findMax() << endl;

   cout << endl << "Additional Testing: " << endl;

   cout << endl << "Removing some values from searchTree2" << endl;

   searchTree2.remove(5);
   searchTree2.remove(10);
   searchTree2.remove(20);
   searchTree2.remove(25);
   searchTree2.remove(30);
   searchTree2.remove(50);
   searchTree2.remove(60);
   searchTree2.remove(70);

   cout << endl << "Min value of tree: " << searchTree2.findMin() << endl;
   cout << "Max value of tree: " << searchTree2.findMax() << endl;

   cout << endl << "Removing more values from searchTree2" << endl;

   searchTree2.remove(100);
   searchTree2.remove(200);
   searchTree2.remove(600);
   searchTree2.remove(700);

   cout << endl << "Min value of tree: " << searchTree2.findMin() << endl;
   cout << "Max value of tree: " << searchTree2.findMax() << endl;

   FHlazySearchTree<int> searchTree3 = searchTree2;
   searchTree2.collectGarbage();

   cout << endl << "Collecting garbage and adding some new values to searchTree2" << endl;

   searchTree2.insert(50);
   searchTree2.insert(20);
   searchTree2.insert(150);
   searchTree2.insert(900);

   cout << "\nsearchTree2:\n";
   searchTree2.traverse(intPrinter);
   cout << "\ntree 2 size: " << searchTree2.size()
   << "  Hard size: " << searchTree2.sizeHard() << endl;

   cout << endl << "Min value of tree: " << searchTree2.findMin() << endl;
   cout << "Max value of tree: " << searchTree2.findMax() << endl;

   cout << "\nsearchTree3:\n";
   searchTree3.traverse(intPrinter);
   cout << "\ntree 3 size: " << searchTree3.size()
   << "  Hard size: " << searchTree3.sizeHard() << endl;

   return 0;
}

/* ---------------------- Run --------------------------
 initial size: 0
 After populating -- traversal and sizes:
 10 20 30 50 60 70
 tree 1 size: 6  Hard size: 6
 Collecting garbage on new tree - should be no garbage.
 tree 1 size: 6  Hard size: 6


 Attempting 1 removal:
 removed 20
 tree 1 size: 5  Hard size: 6
 Collecting Garbage - should clean 1 item.
 tree 1 size: 5  Hard size: 5
 Collecting Garbage again - no change expected.
 tree 1 size: 5  Hard size: 5
 Adding 'hard' 22 - should see new sizes.
 10 22 30 50 60 70
 tree 1 size: 6  Hard size: 6

 After soft removal.
 10 30 50 60 70
 tree 1 size: 5  Hard size: 6
 Repeating soft removal. Should see no change.
 10 30 50 60 70
 tree 1 size: 5  Hard size: 6
 Soft insertion. Hard size should not change.
 10 22 30 50 60 70
 tree 1 size: 6  Hard size: 6


 Attempting 100 removals:
 removed 70
 removed 60
 removed 50
 removed 30
 removed 22
 removed 10

 searchTree now:

 tree 1 size: 0  Hard size: 0

 searchTree2:
 10 20 30 50 60 70 100 200 300 500 600 700
 tree 2 size: 12  Hard size: 12
 Press any key to continue . . .
 ---------------------------------------------------------------------- */
