//
//  main.cpp
//  CS2C_Assignment1
//
//  Created by Benjamin Boyle on 9/26/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//

#include <iostream>
#include <vector>
#include <time.h>

using namespace std;


class Sublist
{
private:
    vector<double> sublist;
    double sublistSum;
public:
    Sublist() { sublist = {}; sublistSum = 0; }
    bool showSublist();
    double getSublistSum() { return sublistSum; }
    Sublist addItem(double);
};

Sublist Sublist::addItem(double newVal)
{
    Sublist newSublist = *this;
    newSublist.sublist.push_back(newVal);
    newSublist.sublistSum += newVal;
    return newSublist;
}

bool Sublist::showSublist()
{
    double totalSum = this->sublistSum;
    cout << "array[" << totalSum << "] = " << totalSum << endl;
    return true;
}

int main()
{
    int TARGET = 180;
    vector<int> dataSet;
    vector<Sublist> choices;
    vector<Sublist>::iterator iter, iterBest;
    int k, j, numSets, max, masterSum;
    bool foundPerfect = false;
    
    dataSet.push_back(20); dataSet.push_back(12); dataSet.push_back(22);
    dataSet.push_back(15); dataSet.push_back(25);
    dataSet.push_back(19); dataSet.push_back(29);
    dataSet.push_back(18);
    dataSet.push_back(11); dataSet.push_back(13); dataSet.push_back(17);
    
    choices.clear();
    cout << "Target time: " << TARGET << endl;
    
    choices = {};
    Sublist emptyList = Sublist();
    choices.push_back(emptyList);
    iterBest = choices.begin();
    for (j = 0; j < dataSet.size(); j++)
    {
        int currElement = dataSet[j];
        for (iter = choices.begin(); iter != choices.end(); iter++)
        {
            if (iter->getSublistSum() + currElement == TARGET)
            {
                Sublist newListing = iter->addItem(currElement);
                choices.push_back(newListing);
                foundPerfect = true;
                iterBest = iter;
                break;
            }
            else if (iter->getSublistSum() + currElement <= TARGET)
            {
                choices.push_back(iter->addItem(currElement));
                if (TARGET - iter->getSublistSum() < TARGET - iterBest->getSublistSum()) {
                    iterBest = iter;
                }
            }
        }
        if (foundPerfect == true)
        {
            break;
        }
    }
    
    
    iterBest->showSublist();
    
    return 0;
}
