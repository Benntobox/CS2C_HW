//
//  FHlazySearchTree.hpp
//  CS2C_Assignment4
//
//  Created by Benjamin Boyle on 10/17/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//

// File FHlazysearch_tree.h
// Template definitions for FHsearchTrees, which are general trees
#ifndef FHlazySearchTree_H
#define FHlazySearchTree_H

// ---------------------- FHs_treeNode Prototype --------------------------
template <class Comparable>
class FHlazySearchTreeNode
{
public:
   FHlazySearchTreeNode( const Comparable & d = Comparable(),
                FHlazySearchTreeNode *lt = nullptr,
                FHlazySearchTreeNode *rt = nullptr)
   : lftChild(lt), rtChild(rt), data(d), deleted(false)
   { }

   FHlazySearchTreeNode *lftChild, *rtChild;
   Comparable data;
   bool deleted;

   // for use only with AVL Trees
   virtual int getHeight() const { return 0; }
   virtual bool setHeight(int height) { return true; }
};

// ---------------------- FHsearch_tree Prototype --------------------------
template <class Comparable>
class FHlazySearchTree
{
protected:
   int mSize, mSizeHard;
   FHlazySearchTreeNode<Comparable> *mRoot;

public:
   FHlazySearchTree() { mSize = 0; mRoot = nullptr; }
   FHlazySearchTree(const FHlazySearchTree &rhs)
   { mRoot = nullptr; mSize = 0; *this = rhs; }
   ~FHlazySearchTree() { clear(); }

   const Comparable &findMin() const;
   const Comparable &findMax() const;
   const Comparable &find(const Comparable &x) const;

   bool empty() const { return (mSize == 0); }
   int size() const { return mSize; }
   int sizeHard() const { return mSizeHard; }
   void clear() { makeEmpty(mRoot); }
   void collectGarbage();
   const FHlazySearchTree & operator=(const FHlazySearchTree &rhs);


   bool insert(const Comparable &x);
   bool remove(const Comparable &x);
   bool contains(const Comparable &x) const { return find(mRoot, x) != nullptr; }

   template <class Processor>
   void traverse(Processor func) const { traverse(mRoot, func); }
   int showHeight() const { return findHeight(mRoot); }

protected:
   FHlazySearchTreeNode<Comparable> *clone( FHlazySearchTreeNode<Comparable> *root) const;
   FHlazySearchTreeNode<Comparable> *findMin(FHlazySearchTreeNode<Comparable> *root) const;
   FHlazySearchTreeNode<Comparable> *findMax(FHlazySearchTreeNode<Comparable> *root) const;
   FHlazySearchTreeNode<Comparable> *find(FHlazySearchTreeNode<Comparable> *root,
                                  const Comparable &x) const;
   bool insert(FHlazySearchTreeNode<Comparable> * &root,
               const Comparable &x);
   bool remove(FHlazySearchTreeNode<Comparable> * &root, const Comparable &x);
   bool hardRemove(FHlazySearchTreeNode<Comparable> * &root);
   void makeEmpty(FHlazySearchTreeNode<Comparable> * &subtreeToDelete);
   template <class Processor>
   void traverse(FHlazySearchTreeNode<Comparable> *treeNode,
                 Processor func, int level = -1) const;
   int findHeight(FHlazySearchTreeNode<Comparable> *treeNode, int height = -1) const;
   void collectGarbage( FHlazySearchTreeNode<Comparable>* &root);

public:
   // for exception throwing
   class EmptyTreeException {};
   class NotFoundException {};
};

// FHsearch_tree public method definitions -----------------------------
template <class Comparable>
const Comparable & FHlazySearchTree<Comparable>::findMin() const
{
   if (mRoot == nullptr)
      throw EmptyTreeException();
   return findMin(mRoot)->data;
}

template <class Comparable>
const Comparable & FHlazySearchTree<Comparable>::findMax() const
{
   if (mRoot == nullptr)
      throw EmptyTreeException();
   return findMax(mRoot)->data;
}

template <class Comparable>
const Comparable &FHlazySearchTree<Comparable>::find(
                                                  const Comparable &x) const
{
   FHlazySearchTreeNode<Comparable> *resultNode;

   resultNode = find(mRoot, x);
   if (resultNode == nullptr)
      throw NotFoundException();
   return resultNode->data;
}

template <class Comparable>
const FHlazySearchTree<Comparable> &FHlazySearchTree<Comparable>::operator=
(const FHlazySearchTree &rhs)
{
   if (&rhs != this)
   {
      clear();
      mRoot = clone(rhs.mRoot);
      mSize = rhs.size();
   }
   return *this;
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::insert(const Comparable &x)
{
   if (insert(mRoot, x))
   {
      mSize++;
      return true;
   }
   return false;
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::remove(const Comparable &x)
{
   if (remove(mRoot, x))
   {
      mSize--;
      return true;
   }
   return false;
}

template <class Comparable>
void FHlazySearchTree<Comparable>::collectGarbage()
{
   collectGarbage(mRoot);
}

template <class Comparable>
template <class Processor>
void FHlazySearchTree<Comparable>::traverse( FHlazySearchTreeNode<Comparable> *treeNode,
                                         Processor func, int level) const
{
   if (treeNode == nullptr)
      return;
   // we're not doing anything with level but its there in case we want it
   traverse(treeNode->lftChild, func, level + 1);
   func(treeNode->data);
   traverse(treeNode->rtChild, func, level + 1);
}


// FHsearch_tree private method definitions -----------------------------
template <class Comparable>
FHlazySearchTreeNode<Comparable> *FHlazySearchTree<Comparable>::clone(
                                                           FHlazySearchTreeNode<Comparable> *root) const
{
   FHlazySearchTreeNode<Comparable> *newNode;
   if (root == nullptr)
      return nullptr;

   newNode =  new FHlazySearchTreeNode<Comparable>(
                                           root->data,
                                           clone(root->lftChild), clone(root->rtChild));

   return newNode;
}

template <class Comparable>
FHlazySearchTreeNode<Comparable> *FHlazySearchTree<Comparable>::findMin(
                                                             FHlazySearchTreeNode<Comparable> *root) const
{
   if (root == nullptr)
      return nullptr;
   if (root->deleted == true)
   {
      FHlazySearchTreeNode<Comparable> *leftMin = nullptr;
      if (root->rtChild == nullptr && root->lftChild == nullptr)
         return nullptr;
      if ((leftMin = findMin(root->lftChild)))
         return leftMin;
      else
         return findMin(root->rtChild);
   }
   if (root->lftChild == nullptr)
      return root;
   return findMin(root->lftChild);
}

template <class Comparable>
FHlazySearchTreeNode<Comparable> *FHlazySearchTree<Comparable>::findMax(
                                                             FHlazySearchTreeNode<Comparable> *root) const
{
   if (root == nullptr)
      return nullptr;
   if (root->deleted == true)
   {
      FHlazySearchTreeNode<Comparable> *rightMin;
      if (root->rtChild == nullptr && root->lftChild == nullptr)
         return nullptr;
      if ((rightMin = findMin(root->rtChild)))
         return rightMin;
      else
         return findMin(root->lftChild);
   }
   if (root->rtChild == nullptr)
      return root;
   return findMin(root->rtChild);
}

template <class Comparable>
FHlazySearchTreeNode<Comparable>* FHlazySearchTree<Comparable>::find(
                                                          FHlazySearchTreeNode<Comparable> *root, const Comparable &x) const
{
   if (root == nullptr)
      return nullptr;

   if (x < root->data)
      return find(root->lftChild, x);
   if (root->data < x)
      return find(root->rtChild, x);
   if (root->deleted == true)
      return nullptr;
   return root;
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::insert(
                                          FHlazySearchTreeNode<Comparable> * &root, const Comparable &x)
{
   if (root == nullptr)
   {
      root = new FHlazySearchTreeNode<Comparable>(x, nullptr, nullptr);
      mSizeHard++;
      return true;
   }
   else if (x == root->data)
   {
      if (root->deleted == true){
         root->deleted = false;
         return true;
      }
      return false;
   }
   else if (x < root->data)
      return insert(root->lftChild, x);
   else if (root->data < x)
      return insert(root->rtChild, x);

   return false; // duplicate
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::remove(
                                          FHlazySearchTreeNode<Comparable> * &root, const Comparable &x)
{
   if (root == nullptr) { return false; }
   FHlazySearchTreeNode<Comparable>* targetNode;
   if ((targetNode = find(root, x)))
   {
      if (targetNode->deleted == true) { return false; }
      targetNode->deleted = true;
      return true;
   }
   return false;
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::hardRemove(FHlazySearchTreeNode<Comparable> * &root)
{
   FHlazySearchTreeNode<Comparable> *minNode;
   if (root == nullptr)
      return false;

   minNode = findMin(root->rtChild)? findMin(root->rtChild) : findMin(root->lftChild);
   if (minNode != nullptr)
   {
      root->data = minNode->data;
      root->deleted = false;
      minNode->deleted = true;
      return true;
   }
   return false;

/*
   if (root == NULL)
      return false;

   if (x < root->data)
      return hardRemove(root->lftChild, x);
   if (root->data < x)
      return hardRemove(root->rtChild, x);

   // found the node
   if (root->lftChild != NULL && root->rtChild !=NULL)
   {

      FHlazySearchTreeNode<Comparable> *minNode = findMin(root->rtChild)? findMin(root->rtChild): findMin(root->lftChild);
      if (minNode == nullptr) { return true; }
      root->data = minNode->data;
      root->deleted = false;
      minNode->deleted = true;
      hardRemove(root->rtChild, minNode->data);
   }
   else
   {
      std::cout << "Removed " << root->data << std::endl;
      FHlazySearchTreeNode<Comparable> *nodeToRemove = root;
      root = (root->lftChild != NULL)? root->lftChild : root->rtChild;
      delete nodeToRemove;
      mSizeHard--;
   }
   return true;
 */
}

template <class Comparable>
void FHlazySearchTree<Comparable>::makeEmpty(
                                          FHlazySearchTreeNode<Comparable> * &subtreeToDelete)
{
   if (subtreeToDelete == nullptr)
      return;

   // remove children
   makeEmpty(subtreeToDelete->lftChild);
   makeEmpty(subtreeToDelete->rtChild);

   // clear client's pointer
   subtreeToDelete->deleted = true;
   --mSize;
}

template <class Comparable>
int FHlazySearchTree<Comparable>::findHeight( FHlazySearchTreeNode<Comparable> *treeNode,
                                          int height ) const
{
   int leftHeight, rightHeight;

   if (treeNode == nullptr)
      return height;
   height++;
   leftHeight = findHeight(treeNode->lftChild, height);
   rightHeight = findHeight(treeNode->rtChild, height);
   return (leftHeight > rightHeight)? leftHeight : rightHeight;
}

template <class Comparable>
void FHlazySearchTree<Comparable>::collectGarbage( FHlazySearchTreeNode<Comparable>* &root)
{
   if (root == nullptr)
      return;

   FHlazySearchTreeNode<Comparable>* nodeToBeDeleted;
   if (root->deleted == true)
   {
      if (!hardRemove(root))
      {
         collectGarbage(root->lftChild);
         collectGarbage(root->rtChild);
         delete root;
         root = nullptr;
         mSizeHard--;
      }
      else
      {
         collectGarbage(root->lftChild);
         collectGarbage(root->rtChild);
      }
   }

}

#endif

