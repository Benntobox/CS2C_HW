//
//  main.cpp
//  CS2C_Assignment1
//
//  Created by Benjamin Boyle on 9/26/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int TARGET = 180;
    vector<int> dataSet;
    vector<Sublist> choices;
    vector<Sublist>::iterator iter, iterBest;
    int k, j, numSets, max, masterSum;
    bool foundPerfect;
    
    dataSet.push_back(20); dataSet.push_back(12); dataSet.push_back(22);
    dataSet.push_back(15); dataSet.push_back(25);
    dataSet.push_back(19); dataSet.push_back(29);
    dataSet.push_back(18);
    dataSet.push_back(11); dataSet.push_back(13); dataSet.push_back(17);
    
    choices.clear();
    cout << "Target time: " << TARGET << endl;
    
    
    // code provided by student
    
    iterBest->showSublist();
    
    return 0;
}
