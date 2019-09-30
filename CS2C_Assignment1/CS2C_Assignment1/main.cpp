//  main.cpp
//  CS2C_Assignment1
//
//  Created by Benjamin Boyle on 9/26/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//

// CS 2C Assignment #1 Part A - int Version
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

// ---------------------------- Sublist Prototype ----------------------------

class Sublist
{
public:
    Sublist(vector<int> *orig = NULL) : sum(0), originalObjects (orig) { }
    Sublist addItem( int indexOfItemToAdd );
    void showSublist() const;
    int getSum() const { return sum; }
    
private:
    int sum;
    vector<int> *originalObjects;
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

// ------------------------- Global Scope Definitions --------------------------

bool isTargetViable(vector<int> dataSet, int TARGET)
{
    int i, total = 0;
    for (i = 0; i < dataSet.size(); i++)
    {
        total += dataSet[i];
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
    int TARGET = 21;
    vector<int> dataSet;
    vector<Sublist> choices;
    vector<Sublist>::iterator iter, iterBest;
    bool foundPerfect = false;
    
    dataSet.push_back(20); dataSet.push_back(12); dataSet.push_back(22);
    dataSet.push_back(15); dataSet.push_back(25);
    dataSet.push_back(19); dataSet.push_back(29);
    dataSet.push_back(18);
    dataSet.push_back(11); dataSet.push_back(13); dataSet.push_back(17);
    
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
            if (iter->getSum() + dataSet[j] == TARGET)
            {
                choices.push_back(iter->addItem(j));
                iterBest = choices.end()-1;
                foundPerfect = true;
                break;
            }
            else if (iter->getSum() + dataSet[j] < TARGET)
            {
                choices.push_back(iter->addItem(j));
                /*
                if (TARGET - (choices.end()-1)->getSum() < TARGET - iterBest->getSum())
                {
                    iterBest = choices.end()-1;
                }
                */
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
            if (TARGET - iter->getSum() < TARGET - iterBest->getSum())
            {
                iterBest = iter;
            }
        }
    }
    
    cout << "Sublist ------------------------" << endl;
    cout << "sum: " << iterBest->getSum() << endl;
    iterBest->showSublist();
    return 0;
}
