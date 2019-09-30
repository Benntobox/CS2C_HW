//
//  mainSecond.cpp
//  CS2C_Assignment1
//
//  Created by Benjamin Boyle on 9/29/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//

#include "iTunes.h"
#include <time.h>

using namespace std;

// ---------------------------- Sublist Prototype ----------------------------

class Sublist
{
public:
    Sublist(vector<iTunesEntry> *orig = NULL) : sum(0), originalObjects (orig) { }
    Sublist addItem( int indexOfItemToAdd );
    void showSublist() const;
    int getSum() const { return sum; }
    
private:
    int sum;
    vector<iTunesEntry> *originalObjects;
    vector<int> indices;
};

// ------------------------ Sublist Method Definitions ------------------------

Sublist Sublist::addItem(int indexOfItemToAdd) {
    Sublist newSublist = Sublist(this->originalObjects);
    for (int i = 0; i < this->indices.size(); i++)
    {
        newSublist.indices.push_back(this->indices.at(i));
    }
    newSublist.indices.push_back(indexOfItemToAdd);
    newSublist.sum = this->getSum() + originalObjects->at(indexOfItemToAdd);
    return newSublist;
}

void Sublist::showSublist() const {
    for (int i = 0; i < this->indices.size(); i++) {
        int indexOfIndices = this->indices[i];
        cout << "array[" << indexOfIndices << "] = " << originalObjects->at(indexOfIndices);
        if (i < this->indices.size() - 1)
        {
            cout  << ", ";
        }
    }
    cout << endl;
}



int main()
{
    const int TARGET = 3600;
    vector<iTunesEntry> dataSet;
    vector<Sublist> choices;
    vector<Sublist>::iterator iter, iterBest;
    int k, j, numSets, max, array_size, masterSum;
    bool foundPerfect;
    
    // read the data
    iTunesEntryReader tunes_input("itunes_file.txt");
    if (tunes_input.readError())
    {
        cout << "couldn't open " << tunes_input.getFileName()
        << " for input.\n";
        exit(1);
    }
    
    // time the algorithm -------------------------
    clock_t startTime, stopTime;
    startTime = clock();
    
    // create a vector of objects for our own use:
    array_size = tunes_input.getNumTunes();
    for (int k = 0; k < array_size; k++)
        dataSet.push_back(tunes_input[k]);
    
    cout << "Target time: " << TARGET << endl;
    
    // code provided by student
    
    iterBest->showSublist();
    
    // how we determine the time elapsed -------------------
    stopTime = clock();
    // report algorithm time
    cout << "\nAlgorithm Elapsed Time: "
    << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC
    << " seconds." << endl << endl;
    
    return 0;
}
