//
//  main.cpp
//  CS2C_Assignment9
//
//  Created by Benjamin Boyle on 12/3/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//

// File FHgraph.h EXPERIMENT
// Template definitions for FHgraph.
#ifndef FHFLOWGRAPH_H
#define FHFLOWGRAPH_H
#include <limits.h>
#include <utility>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <iostream>
#include <functional>
using namespace std;

// CostType is some numeric type that expresses cost of edges
// Object is the non-graph data for a vertex
template <class Object, typename CostType>
class FHflowVertex
{
   // internal typedefs to simplify syntax
   typedef FHflowVertex<Object, CostType>* VertPtr;
   typedef map<VertPtr, CostType> EdgePairList;

public:
   static int nSortKey;
   static stack<int> keyStack;
   static enum { SORT_BY_DATA, SORT_BY_DIST } eSortType;
   static bool setNSortType( int whichType );
   static void pushSortKey() { keyStack.push(nSortKey); }
   static void popSortKey() { nSortKey = keyStack.top(); keyStack.pop(); }

   static int const INFINITY_FH = INT_MAX;  // defined in limits.h
   EdgePairList flowAdjList, resAdjList;
   Object data;
   CostType dist;
   VertPtr nextInPath;  // used for client-specific info

   FHflowVertex( const Object & x = Object() );

   void addToFlowAdjList(VertPtr neighbor, CostType cost);
   void addToResAdjList(VertPtr neighbor, CostType cost);
   bool operator<( const FHflowVertex<Object, CostType> & rhs) const;
   const FHflowVertex<Object, CostType> & operator=
   ( const FHflowVertex<Object, CostType> & rhs);
   void showFlowAdjList();
   void showResAdjList();
};

// static const initializations for Vertex --------------
template <class Object, typename CostType>
int FHflowVertex<Object, CostType>::nSortKey
= FHflowVertex<Object, CostType>::SORT_BY_DATA;

template <class Object, typename CostType>
stack<int> FHflowVertex<Object, CostType>::keyStack;
// ------------------------------------------------------

template <class Object, typename CostType>
bool FHflowVertex<Object, CostType>::setNSortType( int whichType )
{
   switch (whichType)
   {
      case SORT_BY_DATA:
      case SORT_BY_DIST:
         nSortKey = whichType;
         return true;
      default:
         return false;
   }
}

template <class Object, typename CostType>
FHflowVertex<Object, CostType>::FHflowVertex( const Object & x)
: data(x), dist((CostType)INFINITY_FH),
nextInPath(NULL)
{
   // nothing to do
}

template <class Object, typename CostType>
void FHflowVertex<Object, CostType>::addToFlowAdjList(
                        FHflowVertex<Object, CostType> *neighbor, CostType cost)
{
   flowAdjList[neighbor] = cost;
}

template <class Object, typename CostType>
void FHflowVertex<Object, CostType>::addToResAdjList(
                                                      FHflowVertex<Object, CostType> *neighbor, CostType cost)
{
   resAdjList[neighbor] = cost;
}

template <class Object, typename CostType>
bool FHflowVertex<Object, CostType>::operator<(
                                           const FHflowVertex<Object, CostType> & rhs) const
{
   switch (nSortKey)
   {
      case SORT_BY_DIST:
         return (dist < rhs.dist);
      case SORT_BY_DATA:
         return (data < rhs.data);
      default:
         return false;
   }
}

template <class Object, typename CostType>
const FHflowVertex<Object, CostType> & FHflowVertex<Object, CostType>::operator=(
                                                                         const FHflowVertex<Object, CostType> & rhs)
{
   flowAdjList = rhs.flowAdjList;
   resAdjList = rhs.resAdjList;
   data = rhs.data;
   dist = rhs.dist;
   nextInPath = rhs.nextInPath;;
   return *this;
}

template <class Object, typename CostType>
void FHflowVertex<Object, CostType>::showFlowAdjList()
{
   typename EdgePairList::iterator iter;

   cout << "Flow Adj List for " << data << ": ";
   for (iter = flowAdjList.begin(); iter != flowAdjList.end(); ++iter)
      cout << iter->first->data << "(" << iter->second << ") ";
   cout << endl;
}


template <class Object, typename CostType>
void FHflowVertex<Object, CostType>::showResAdjList()
{
   typename EdgePairList::iterator iter;

   cout << "Res Adj List for " << data << ": ";
   for (iter = resAdjList.begin(); iter != resAdjList.end(); ++iter)
      cout << iter->first->data << "(" << iter->second << ") ";
   cout << endl;
}

// ------------------------ FHflowGraph ---------------------------------------

template <class Object, typename CostType>
class FHflowGraph
{
   // internal typedefs to simplify syntax
   typedef FHflowVertex<Object, CostType> Vertex;
   typedef FHflowVertex<Object, CostType>* VertPtr;
   typedef map<VertPtr, CostType> EdgePairList;
   typedef set<VertPtr> VertPtrSet;
   typedef set<Vertex> VertexSet;

private:
   VertPtrSet vertPtrSet;
   VertexSet vertexSet;
   VertPtr startVertPtr, endVertPtr;

public:
   FHflowGraph () {}
   void addEdge(const Object &source, const Object &dest, CostType cost);
   void showFlowAdjTable();
   void showResAdjTable();
   VertPtr addToVertexSet(const Object & object);
   void clear();
   bool setStartVert(const Object &x);
   bool setEndVert(const Object &x);

   // algorithms
   CostType findMaxFlow();
   bool dijkstra(const Object & x);

private:
   VertPtr getVertexWithThisData(const Object & x);
   bool establishNextFlowPath();
   CostType getLimitingFlowOnResPath();
   bool adjustPathByCost(CostType cost);
   CostType getCostOfResEdge(VertPtr src, VertPtr dst);
   bool addCostToResEdge(VertPtr src, VertPtr dst, CostType cost);
   bool addCostToFlowEdge(VertPtr src, VertPtr dst, CostType cost);
};

template <class Object, typename CostType>
FHflowVertex<Object, CostType>* FHflowGraph<Object, CostType>::addToVertexSet(
                                                                      const Object & object)
{
   pair<typename VertexSet::iterator, bool> retVal;
   VertPtr vPtr;

   // save sort key for client
   Vertex::pushSortKey();
   Vertex::setNSortType(Vertex::SORT_BY_DATA);

   // build and insert vertex into master list
   retVal = vertexSet.insert( Vertex(object) );

   // get pointer to this vertex and put into vert pointer list
   vPtr = (VertPtr)&*retVal.first;
   vertPtrSet.insert(vPtr);

   Vertex::popSortKey();  // restore client sort key
   return vPtr;
}

template <class Object, typename CostType>
void FHflowGraph<Object, CostType>::clear()
{
   vertexSet.clear();
   vertPtrSet.clear();
}

template <class Object, typename CostType>
void FHflowGraph<Object, CostType>::addEdge(
                                        const Object &source, const Object &dest, CostType cost )
{
   VertPtr src, dst;

   // put both source and dest into vertex list(s) if not already there
   src = addToVertexSet(source);
   dst = addToVertexSet(dest);

   // add dest to source's adjacency list
   src->addToFlowAdjList(dst, 0);
   src->addToResAdjList(dst, cost);
   dst->addToResAdjList(src, 0);
}

template <class Object, typename CostType>
void FHflowGraph<Object, CostType>::showFlowAdjTable()
{
   typename VertPtrSet::iterator iter;

   cout << "------------------------ \n";
   for (iter = vertPtrSet.begin(); iter != vertPtrSet.end(); ++iter)
      (*iter)->showFlowAdjList();
   cout << endl;
}

template <class Object, typename CostType>
void FHflowGraph<Object, CostType>::showResAdjTable()
{
   typename VertPtrSet::iterator iter;

   cout << "------------------------ \n";
   for (iter = vertPtrSet.begin(); iter != vertPtrSet.end(); ++iter)
      (*iter)->showResAdjList();
   cout << endl;
}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::setStartVert(const Object &x)
{
   if ((startVertPtr = addToVertexSet(x))) { return true; }
   return false;
}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::setEndVert(const Object &x)
{
   if ((endVertPtr = addToVertexSet(x))) { return true; }
   return false;
}


/*
template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::dijkstra(const Object & x)
{
   typename VertPtrSet::iterator vIter;
   typename EdgePairList::iterator edgePrIter;
   VertPtr wPtr, sPtr, vPtr;
   CostType costVW;
   queue<VertPtr> partiallyProcessedVerts;

   sPtr = getVertexWithThisData(x);
   if (sPtr == NULL)
      return false;

   // initialize the vertex list and place the starting vert in p_p_v queue
   for (vIter = vertPtrSet.begin(); vIter != vertPtrSet.end(); ++vIter)
   {
      (*vIter)->dist = Vertex::INFINITY_FH;
      (*vIter)->nextInPath = NULL;
   }

   sPtr->dist = 0;
   partiallyProcessedVerts.push( sPtr ); // or, FHbinHeap::insert(), e.g.

   // outer dijkstra loop
   while( !partiallyProcessedVerts.empty() )
   {
      vPtr = partiallyProcessedVerts.front();
      partiallyProcessedVerts.pop();

      // inner dijkstra loop: for each vert adj to v, lower its dist to s if you can
      for (edgePrIter = vPtr->adjList.begin();
           edgePrIter != vPtr->adjList.end();
           edgePrIter++)
      {
         wPtr = edgePrIter->first;
         costVW = edgePrIter->second;
         if ( vPtr->dist + costVW < wPtr->dist )
         {
            wPtr->dist = vPtr->dist + costVW;
            wPtr->nextInPath = vPtr;

            // *wPtr now has improved distance, so add wPtr to p_p_v queue
            partiallyProcessedVerts.push(wPtr);
         }
      }
   }
   return true;
}
*/

template <class Object, typename CostType>
CostType FHflowGraph<Object, CostType>::findMaxFlow()
{
   CostType cost, totalCost = 0;

   while (true)
   {
      if (!establishNextFlowPath()) { break; }
      cost = getLimitingFlowOnResPath();
      adjustPathByCost(cost);

      totalCost += cost;
   }

   return totalCost;
}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::establishNextFlowPath()
{
   typename VertPtrSet::iterator vIter;
   typename EdgePairList::iterator edgePrIter;
   VertPtr wPtr, vPtr;
   CostType costVW;
   queue<VertPtr> partiallyProcessedVerts;

   // initialize the vertex list and place the starting vert in p_p_v queue
   for (vIter = vertPtrSet.begin(); vIter != vertPtrSet.end(); ++vIter)
   {
      (*vIter)->dist = Vertex::INFINITY_FH;
      (*vIter)->nextInPath = NULL;
   }

   partiallyProcessedVerts.push( startVertPtr ); // or, FHbinHeap::insert(), e.g.

   // outer dijkstra loop
   while( !partiallyProcessedVerts.empty() )
   {
      vPtr = partiallyProcessedVerts.front();
      partiallyProcessedVerts.pop();

      // inner dijkstra loop: for each vert adj to v, lower its dist to s if you can
      for (edgePrIter = vPtr->resAdjList.begin();
           edgePrIter != vPtr->resAdjList.end();
           edgePrIter++)
      {
         wPtr = edgePrIter->first;
         costVW = edgePrIter->second;

         if (costVW == 0) { continue; }

         wPtr->nextInPath = vPtr;

         if (wPtr == endVertPtr)
         {
            return true;
         }
      }
   }
   return false;
}

template <class Object, typename CostType>
CostType FHflowGraph<Object, CostType>::getLimitingFlowOnResPath()
{
   VertPtr vp;
   CostType flowLimit = Vertex::INFINITY_FH, tempCost;

   for (vp = endVertPtr; vp != startVertPtr; vp = vp->nextInPath)
   {
      tempCost = getCostOfResEdge(vp, vp->nextInPath);
      if (tempCost < flowLimit) { flowLimit = tempCost; }
   }
   return flowLimit;
}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::adjustPathByCost(CostType cost)
{
   VertPtr vp, src, dst;

   if (cost == 0) { return false; }

   for (vp = endVertPtr; vp != startVertPtr; vp = vp->nextInPath)
   {
      src = vp;
      dst = vp->nextInPath;
      addCostToResEdge(src, dst, cost);
      addCostToFlowEdge(src, dst, cost);
   }

   return true;
}

template <class Object, typename CostType>
CostType FHflowGraph<Object, CostType>::getCostOfResEdge(VertPtr src, VertPtr dst)
{
   typename EdgePairList::iterator iter;

   for (iter = src->resAdjList.begin(); iter != src->resAdjList.end(); ++iter)
   {
      if (iter->first == dst)
      {
         return iter->second;
      }
   }
   return 0;
}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::addCostToResEdge(VertPtr src, VertPtr dst, CostType cost)
{
   typename EdgePairList::iterator iter;

   for (iter = src->resAdjList.begin(); iter != src->resAdjList.end(); ++iter)
   {
      if (iter->first == dst)
      {
         iter->second += cost;
         return true;
      }
   }
   return false;
}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::addCostToFlowEdge(VertPtr src, VertPtr dst, CostType cost)
{
   typename EdgePairList::iterator iter;

   for (iter = src->resAdjList.begin(); iter != src->resAdjList.end(); ++iter)
   {
      if (iter->first == dst)
      {
         iter->second += cost;
         return true;
      }
   }
   for (iter = src->resAdjList.begin(); iter != src->resAdjList.end(); ++iter)
   {
      if (iter->first == dst)
      {
         iter->second += cost;
         return true;
      }
   }
   return false;
}

template <class Object, typename CostType>
FHflowVertex<Object, CostType>* FHflowGraph<Object, CostType>::getVertexWithThisData(
                                                                             const Object & x)
{
   typename VertexSet::iterator findResult;
   Vertex vert(x);

   Vertex::pushSortKey();  // save client sort key
   Vertex::setNSortType(Vertex::SORT_BY_DATA);
   findResult = vertexSet.find(vert);
   Vertex::popSortKey();  // restore client value

   if ( findResult == vertexSet.end() )
      return NULL;
   return  (VertPtr)&*findResult;     // the address of the vertex in the set of originals
}


#endif


int main()
{
   int finalFlow;

   // build graph
   FHflowGraph<string, int> myG;

   myG.addEdge("s","a", 3);    myG.addEdge("s","b", 2);
   myG.addEdge("a","b", 1);    myG.addEdge("a","c", 3); myG.addEdge("a","d", 4);
   myG.addEdge("b","d", 2);
   myG.addEdge("c","t", 2);
   myG.addEdge("d","t", 3);

   // show the original flow graph
   myG.showResAdjTable();
   myG.showFlowAdjTable();

   myG.setStartVert("s");
   myG.setEndVert("t");
   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();

   return 0;
}


