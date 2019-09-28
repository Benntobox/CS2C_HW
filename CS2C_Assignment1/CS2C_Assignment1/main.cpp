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


class Sublist {
private:
    vector<double> sublist;
public:
    Sublist();
    bool showSublist();
    double sublistSum();
    Sublist operator+(int n) { sublist.push_back(n); return *this;}
};

double Sublist::sublistSum() {
    double total = 0;
    for (int i = 0; i < this->sublist.size(); i++) {
        total += this->sublist[i];
    }
    return total;
}

bool Sublist::showSublist() {
    double totalSum = this->sublistSum();
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
    bool foundPerfect;
    
    dataSet.push_back(20); dataSet.push_back(12); dataSet.push_back(22);
    dataSet.push_back(15); dataSet.push_back(25);
    dataSet.push_back(19); dataSet.push_back(29);
    dataSet.push_back(18);
    dataSet.push_back(11); dataSet.push_back(13); dataSet.push_back(17);
    
    choices.clear();
    cout << "Target time: " << TARGET << endl;
    
    choices = {};
    bool loopBreak = false;
    for (j = 0; j < dataSet.size(); j++) {
        int currElement = dataSet[j];
        for (k = 0; k < choices.size(); k++) {
            if (choices[k].sublistSum() + currElement == TARGET) {
                choices.push_back(choices[k] + currElement);
                loopBreak = true;
                break;
            }
            else if (choices[k].sublistSum() + currElement == TARGET) {
                choices.push_back(choices[k] + currElement);
            }
        }
        if (loopBreak == true) {
            break;
        }
    }
    

    iterBest->showSublist();
    
    return 0;
}
