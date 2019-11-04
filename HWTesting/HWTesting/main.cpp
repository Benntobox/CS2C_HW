// CS2C Assignment #5 Submission - Benny Boyle, 10/30/19
#include <stdio.h>
#include "FHsearch_tree.h"
#include <iostream>
using namespace std;

int main()
{
   return 0;

   1 2 3 4 5 6
   6 5 4  2 1
}













/*
// ---------------------------- Prototype of FHsplayTree ----------------------------
template <class Comparable>
class FHsplayTree : public FHsearch_tree<Comparable>
{
public:
   bool insert(const Comparable &x);
   bool remove(const Comparable &x);
   bool contains(const Comparable &x);
   const Comparable & find(const Comparable &x);
   const Comparable & showRoot();

protected:
   bool insert(const Comparable &x, FHs_treeNode<Comparable>* &root);
   bool remove(const Comparable &x, FHs_treeNode<Comparable>* &root);
   bool contains(const Comparable &x, FHs_treeNode<Comparable>* &root);
   FHs_treeNode<Comparable>* find(const Comparable &x, FHs_treeNode<Comparable>* &root);

   void splay(FHs_treeNode<Comparable> * & root, const Comparable & x);
   void rotateWithLeftChild( FHs_treeNode<Comparable> * & k2 );
   void rotateWithRightChild( FHs_treeNode<Comparable> * & k2 );

};

// ----------------  Public Declarations ------------------------
template <class Comparable>
bool FHsplayTree<Comparable>::insert( const Comparable &x )
{
   if (insert(x, this->mRoot))
   {
      this->mSize++;
      return true;
   }
   return false;
}

template <class Comparable>
bool FHsplayTree<Comparable>::remove(const Comparable &x)
{
   if (remove(x, this->mRoot))
   {
      this->mSize--;
      return true;
   }
   return false;
}

template <class Comparable>
bool FHsplayTree<Comparable>::contains(const Comparable &x)
{
   if (contains(x, this->mRoot))
   {
      return true;
   }
   return false;
}

template <class Comparable>
const Comparable &FHsplayTree<Comparable>::find(const Comparable &x)
{
   FHs_treeNode<Comparable> *resultNode;

   resultNode = find(x, this->mRoot);
   if (resultNode == nullptr)
      throw typename FHsearch_tree<Comparable>::NotFoundException();
   return resultNode->data;
}

template <class Comparable>
const Comparable & FHsplayTree<Comparable>::showRoot()
{
   if (this->mRoot == nullptr)
   {
      return FHs_treeNode<Comparable>().data;
   }
   return this->mRoot->data;
}

// ---------------  Protected Declarations -----------------------

template <class Comparable>
bool FHsplayTree<Comparable>::insert( const Comparable & x,
                                     FHs_treeNode<Comparable>* &root)
{
   if (root == nullptr)
   {
      FHs_treeNode<Comparable>* newNode;
      newNode = new FHs_treeNode<Comparable>(x, nullptr, nullptr);
      root = newNode;
      return true;
   }

   splay(root, x);

   if (x < root->data)
   {
      FHs_treeNode<Comparable>* newNode;
      newNode = new FHs_treeNode<Comparable>( x, root->lftChild, root);
      root = newNode;
      return true;
   }
   if (root->data < x)
   {
      FHs_treeNode<Comparable>* newNode;
      newNode = new FHs_treeNode<Comparable>( x, root, root->rtChild);
      root = newNode;
      return true;
   }
   return false;
}

template <class Comparable>
bool FHsplayTree<Comparable>::remove( const Comparable & x,
                                     FHs_treeNode<Comparable>* &root)
{
   if (root == nullptr) { return false; }
   FHs_treeNode<Comparable>* newRoot;

   splay(root, x);

   if (x < root->data || root->data < x) { return false; }
   if (root->lftChild == nullptr)
   {
      newRoot = root->rtChild;
   }
   else
   {
      newRoot = root->lftChild;
      splay(newRoot, x);
      newRoot->rtChild = root->rtChild;
   }
   delete root;
   root = newRoot;
   return true;
}

template <class Comparable>
bool FHsplayTree<Comparable>::contains( const Comparable & x,
                                       FHs_treeNode<Comparable>* &root)
{
   if (root == nullptr)
      return false;

   try
   {
      find(x);
   }
   catch (...)
   {
      return false;
   }
   return true;
}

template <class Comparable>
FHs_treeNode<Comparable>* FHsplayTree<Comparable>::find(const Comparable &x,
                                                        FHs_treeNode<Comparable>* &root)
{
   if (root == nullptr)
      return nullptr;

   splay(root, x);

   if (!(root->data < x || x < root->data))
   {
      return root;
   }
   return nullptr;
}

template <class Comparable>
void FHsplayTree<Comparable>::splay(FHs_treeNode<Comparable> * & root,
                                    const Comparable & x)
{
   FHs_treeNode<Comparable>* leftTree = nullptr, *rightTree = nullptr,
   *leftTreeMax = nullptr, *rightTreeMin = nullptr;

   while (root != nullptr)
   {
      if (x < root->data)
      {
         if (root->lftChild == nullptr) { break; }
         if (x < root->lftChild->data)
         {
            rotateWithLeftChild(root);
            if (root->lftChild == nullptr) { break; }
         }
         if (rightTree == nullptr) { rightTree = root; rightTreeMin = root; }
         else
         {
            rightTreeMin->lftChild = root;
         }

         rightTreeMin = root;
         root = root->lftChild;
      }
      else if (root->data < x)
      {
         if (root->rtChild == nullptr) { break; }
         if (root->rtChild->data < x)
         {
            rotateWithRightChild(root);
            if (root->rtChild == nullptr) { break; }
         }
         if (leftTree == nullptr) { leftTree = root; leftTreeMax = root; }
         else { leftTreeMax->rtChild = root; }

         leftTreeMax = root;
         root = root->rtChild;
      }
      else { break; }
   }

   if (leftTree != nullptr)
   {
      leftTreeMax->rtChild = root->lftChild;
      root->lftChild = leftTree;
   }
   if (rightTree != nullptr)
   {
      rightTreeMin->lftChild = root->rtChild;
      root->rtChild = rightTree;
   }
}

template <class Comparable>
void FHsplayTree<Comparable>::rotateWithLeftChild( FHs_treeNode<Comparable> * & k2 )
{
   FHs_treeNode<Comparable>* k1 = k2->lftChild;
   k2->lftChild = k1->rtChild;
   k1->rtChild = k2;
   k2 = k1;
}

template <class Comparable>
void FHsplayTree<Comparable>::rotateWithRightChild( FHs_treeNode<Comparable> * & k2 )
{
   FHs_treeNode<Comparable>* k1 = k2->rtChild;
   k2->rtChild = k1->lftChild;
   k1->lftChild = k2;
   k2 = k1;
}


// ---------------------------- Main ----------------------------
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


/* ------------------------------------ Runs ------------------------------------
 Starting root: 0
 Initial size: 0
 New size: 32

 Traversal:
 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32

 contains 11 --> root: 11 height: 11
 oops on find -1
 find -1 --> root: 1 height: 13
 contains 10 --> root: 10 height: 12
 oops on find 0
 find 0 --> root: 1 height: 13
 contains 9 --> root: 9 height: 13
 find 1 --> root: 1 height: 14
 contains 8 --> root: 8 height: 14
 find 2 --> root: 2 height: 15
 contains 7 --> root: 7 height: 15
 find 3 --> root: 3 height: 16
 contains 6 --> root: 6 height: 16
 find 4 --> root: 4 height: 17
 contains 5 --> root: 5 height: 17
 find 5 --> root: 5 height: 17
 contains 4 --> root: 4 height: 18
 find 6 --> root: 6 height: 16
 contains 3 --> root: 3 height: 18
 find 7 --> root: 7 height: 15
 contains 2 --> root: 2 height: 17
 find 8 --> root: 8 height: 14
 contains 1 --> root: 1 height: 16
 find 9 --> root: 9 height: 13
 oops on contains 0
 contains 0 --> root: 1 height: 15
 find 10 --> root: 10 height: 12
 oops on contains -1
 contains -1 --> root: 1 height: 14
 find 11 --> root: 11 height: 11
 oops on contains -2
 contains -2 --> root: 1 height: 13
 find 12 --> root: 12 height: 7

 Removing several nodes

 Traversal:
 4 8 9 10 12 13 14 15 20 21 22 23 26 27 28 29 30 31 32

 oops splay -1 --> root: 4 height: 5
 oops splay 0 --> root: 4 height: 5
 oops splay 1 --> root: 4 height: 5
 oops splay 2 --> root: 4 height: 5
 oops splay 3 --> root: 4 height: 5
 splay 4 --> root: 4 height: 5
 oops splay 5 --> root: 8 height: 6
 oops splay 6 --> root: 4 height: 7
 oops splay 7 --> root: 8 height: 6
 splay 8 --> root: 8 height: 6
 splay 9 --> root: 9 height: 6
 splay 10 --> root: 10 height: 6
 oops splay 11 --> root: 12 height: 5
 splay 12 --> root: 12 height: 5
 splay 13 --> root: 13 height: 6
 splay 14 --> root: 14 height: 6
 splay 15 --> root: 15 height: 7
 oops splay 16 --> root: 20 height: 8
 oops splay 17 --> root: 15 height: 7
 oops splay 18 --> root: 20 height: 8
 oops splay 19 --> root: 15 height: 7
 splay 20 --> root: 20 height: 8
 splay 21 --> root: 21 height: 9
 splay 22 --> root: 22 height: 10
 splay 23 --> root: 23 height: 11
 oops splay 24 --> root: 26 height: 12
 oops splay 25 --> root: 23 height: 11
 splay 26 --> root: 26 height: 12
 splay 27 --> root: 27 height: 13
 splay 28 --> root: 28 height: 14
 splay 29 --> root: 29 height: 15
 splay 30 --> root: 30 height: 16
 splay 31 --> root: 31 height: 17
 splay 32 --> root: 32 height: 18
 Program ended with exit code: 0
 -------------------------------------------------------------------------------*/


