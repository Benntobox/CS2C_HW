//
//  FHsplayTree.h
//  CS2C_Assignment5
//
//  Created by Benjamin Boyle on 10/26/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//

#ifndef FHsplayTree_h
#define FHsplayTree_h

#include <stdio.h>
#include "FHsearch_tree.h"

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
   bool contains(const Comparable &x, FHs_treeNode<Comparable>* root);
   FHs_treeNode<Comparable>* find(const Comparable &x, FHs_treeNode<Comparable>* root);

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
   if (remove(this->mRoot, x))
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
      newNode = new FHs_treeNode<Comparable>( x, root->rtChild, root);
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

   if (x != root->data) { return false; }
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
                                     FHs_treeNode<Comparable>* root)
{
   if (root == nullptr)
      return false;
   if (find(x, root) != nullptr)
      return true;
   return false;
}

template <class Comparable>
FHs_treeNode<Comparable>* FHsplayTree<Comparable>::find(const Comparable &x,
                                     FHs_treeNode<Comparable>* root)
{
   if (root == nullptr)
      return nullptr;

   splay(root, x);
   if (root->data == x)
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
                              *leftTreeMin = nullptr, *rightTreeMin = nullptr;

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
         if (rightTree == nullptr) { rightTree = root; }
         else { rightTreeMin->lftChild = root; }

         rightTreeMin = root;
         root = root->lftChild;
         rightTreeMin->lftChild = nullptr;
      }
      else if (root->data < x)
      {
         if (root->rtChild == nullptr) { break; }
         if (root->rtChild->data < x)
         {
            rotateWithRightChild(root);
            if (root->rtChild == nullptr) { break; }
         }
         if (leftTree == nullptr) { leftTree = root; }
         else { leftTreeMin->lftChild = root; }

         leftTreeMin = root;
         root = root->rtChild;
         leftTreeMin->rtChild = nullptr;
      }
      else { break; }
   }

   if (leftTree != nullptr)
   {
      FHs_treeNode<Comparable>* currNode = leftTree;
      while (currNode->rtChild != nullptr)
      {
         currNode = currNode->rtChild;
      }
      currNode->rtChild = root->lftChild;
      root->lftChild = leftTree;
   }
   if (rightTree != nullptr)
   {
      FHs_treeNode<Comparable>* currNode = rightTree;
      while (currNode->lftChild != nullptr)
      {
         currNode = currNode->lftChild;
      }
      currNode->lftChild = root->lftChild;
      root->rtChild = rightTree;
   }
}

template <class Comparable>
void FHsplayTree<Comparable>::rotateWithLeftChild( FHs_treeNode<Comparable> * & k2 )
{
   FHs_treeNode<Comparable>* k1 = k2->lftChild;
   k2->lftChild = k1->rtChild;
   k1->lftChild = k2;
   k2 = k1;
}

template <class Comparable>
void FHsplayTree<Comparable>::rotateWithRightChild( FHs_treeNode<Comparable> * & k2 )
{
   FHs_treeNode<Comparable>* k1 = k2->rtChild;
   k2->rtChild = k1->lftChild;
   k1->rtChild = k2;
   k2 = k1;
}



#endif /* FHsplayTree_h */

