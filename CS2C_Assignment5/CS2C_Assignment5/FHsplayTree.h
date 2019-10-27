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
   if (contains(this->mRoot, x))
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


   return false;
}

template <class Comparable>
bool FHsplayTree<Comparable>::remove( const Comparable & x,
                                     FHs_treeNode<Comparable>* &root)
{


   return false;
}

template <class Comparable>
bool FHsplayTree<Comparable>::contains( const Comparable & x,
                                     FHs_treeNode<Comparable>* root)
{


   return false;
}

template <class Comparable>
FHs_treeNode<Comparable>* FHsplayTree<Comparable>::find(const Comparable &x,
                                     FHs_treeNode<Comparable>* root)
{
   FHs_treeNode<Comparable>* foundNode = nullptr;

   return foundNode;
}

template <class Comparable>
void FHsplayTree<Comparable>::splay(FHs_treeNode<Comparable> * & root,
                                    const Comparable & x)
{



}

template <class Comparable>
void FHsplayTree<Comparable>::rotateWithLeftChild( FHs_treeNode<Comparable> * & k2 )
{



}

template <class Comparable>
void FHsplayTree<Comparable>::rotateWithRightChild( FHs_treeNode<Comparable> * & k2 )
{



}

#endif /* FHsplayTree_h */

