//
//  mainSecond.cpp
//  CS2C_Assignment1
//
//  Created by Benjamin Boyle on 9/29/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//

#include "iTunes.h"
#include <time.h>
#include <iostream>
#include <vector>

using namespace std;

// ---------------------------- Sublist Prototype ----------------------------

class Sublist
{
public:
    Sublist(vector<iTunesEntry> *orig = NULL) : time(0), originalObjects (orig) { }
    Sublist addItem( int indexOfItemToAdd );
    void showSublist() const;
    int getTime() const { return time; }
    
private:
    int time;
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
    newSublist.time = this->getTime() + originalObjects->at(indexOfItemToAdd).getTime();
    return newSublist;
}

void Sublist::showSublist() const {
    for (int i = 0; i < this->indices.size(); i++) {
        int indexOfIndices = this->indices[i];
        iTunesEntry currentSong = originalObjects->at(indexOfIndices);
        cout << "array[" << indexOfIndices << "] = " << currentSong.getTitle() << " by " <<
                            currentSong.getArtist() << "(" << currentSong.getArtist() << ") ";
        if (i < this->indices.size() - 1)
        {
            cout  << ", ";
        }
    }
    cout << endl;
}

// ------------------------- Global Scope Definitions --------------------------

int operator+(int value, iTunesEntry entry)
{
    return entry.getTime() + value;
}

int operator+(iTunesEntry entry, int value)
{
    return entry.getTime() + value;
}

bool isTargetViable(vector<iTunesEntry> dataSet, int TARGET)
{
    int i, total = 0;
    for (i = 0; i < dataSet.size(); i++)
    {
        total += dataSet[i].getTime();
    }
    if (total < TARGET)
    {
        return false;
    }
    return true;
}

// ------------------------------------ Main ------------------------------------

int main()
{
    const int TARGET = 3600;
    vector<iTunesEntry> dataSet;
    vector<Sublist> choices;
    vector<Sublist>::iterator iter, iterBest;
    int array_size;
    bool foundPerfect = false;
    
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
    
    choices.clear();
    cout << "Target time: " << TARGET << endl;
    
    if (!isTargetViable(dataSet, TARGET))
    {
        cout << "Target too high, cannot find solution" << endl;
        return 0;
    }
    
    choices.clear();
    choices.push_back(Sublist(&dataSet));
    iterBest = choices.begin();
    for (int j = 0; j < dataSet.size(); j++)
    {
        vector<Sublist> choicesCopyForIterating = choices;
        for (iter = choicesCopyForIterating.begin(); iter != choicesCopyForIterating.end(); iter++)
        {
            if (iter->getTime() + dataSet[j] == TARGET)
            {
                choices.push_back(iter->addItem(j));
                iterBest = choices.end()-1;
                foundPerfect = true;
                break;
            }
            else if (iter->getTime() + dataSet[j] < TARGET)
            {
                choices.push_back(iter->addItem(j));
            }
        }
        if (foundPerfect)
        {
            break;
        }
    }
    if (!foundPerfect)
    {
        for (iter = choices.begin(); iter != choices.end(); iter++)
        {
            if (TARGET - iter->getTime() < TARGET - iterBest->getTime())
            {
                iterBest = iter;
            }
        }
    }
    cout << "Sublist ------------------------" << endl;
    cout << "sum: " << iterBest->getTime() << endl;
    //iterBest->showSublist();
    
    // how we determine the time elapsed -------------------
    stopTime = clock();
    // report algorithm time
    cout << "\nAlgorithm Elapsed Time: "
    << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC
    << " seconds." << endl << endl;
    
    return 0;
}
