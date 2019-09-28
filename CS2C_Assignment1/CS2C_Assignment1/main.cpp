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
        cout << "array[" << i << "] = " << originalObjects->at(i);
    }
}


int main()
{
    int TARGET = 180;
    vector<int> dataSet;
    vector<Sublist> choices;
    vector<Sublist>::iterator iter, iterBest;
    int k, j, numSets, max, masterSum;
    
    dataSet.push_back(20); dataSet.push_back(12); dataSet.push_back(22);
    dataSet.push_back(15); dataSet.push_back(25);
    dataSet.push_back(19); dataSet.push_back(29);
    dataSet.push_back(18);
    dataSet.push_back(11); dataSet.push_back(13); dataSet.push_back(17);
    
    choices.clear();
    cout << "Target time: " << TARGET << endl;
    
    choices.clear();
    choices.push_back(Sublist(&dataSet));
    iterBest = choices.begin();
    for (j = 0; j < dataSet.size(); j++)
    {
        for (iter = choices.begin(); iter != choices.end(); iter++)
        {
            if (iter->getSum() + dataSet[j] == TARGET)
            {
                choices.push_back(iter->addItem(j));
                iterBest = iter;
                break;
            }
            else if (iter->getSum() + dataSet[j] < TARGET)
            {
                choices.push_back(iter->addItem(j));
                if (TARGET - iter->getSum() < TARGET - iterBest->getSum())
                {
                    iterBest = iter;
                }
            }
        }
        if (iterBest->getSum() == TARGET) {
            break;
        }
    }
    iterBest->showSublist();
    return 0;
}
