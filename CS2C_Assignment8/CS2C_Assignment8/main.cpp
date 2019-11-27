//
//  main.cpp
//  CS2C_Assignment8
//
//  Created by Benjamin Boyle on 11/24/19.
//  Copyright © 2019 Benjamin Boyle. All rights reserved.
//

#include <iostream>
#include "FHsort.h"
#include <time.h>

using namespace std;

// --------------------------- quickSortX Definiton ---------------------------

// quickSortX internal
template <typename Comparable>
void quickSortX(FHvector<Comparable> & a, int left, int right, int recLimit)
{
   Comparable pivot;
   int i, j;

   if( left + recLimit <= right )
   {
      pivot = median3(a, left, right);
      for( i = left, j = right - 1; ; )
      {
         while( a[++i] < pivot )
            ;
         while( pivot < a[--j] )
            ;
         if( i < j )
            mySwapFH(a[i], a[j]);
         else
            break;
      }

      mySwapFH(a[i], a[right - 1]);  // restore pivot

      // recursive calls on smaller sub-groups
      quickSortX(a, left, i - 1, recLimit);
      quickSortX(a, i + 1, right, recLimit);
   }
   else
      // non-recursive escape valve - insertionSort
      insertionSort(a, left, right);
}

// quickSortX public driver
template <typename Comparable>
void quickSortX( FHvector<Comparable> & a , int recLimit)
{
   if (recLimit < 2) recLimit = 2;
   quickSortX(a, 0, a.size() - 1, recLimit);
}

// ------------------------------ main ------------------------------
#define ARRAY_SIZE 40000

int main()
{
   int k, recLimit;
   int arrayOfInts[ARRAY_SIZE];
   FHvector<int> fhVectorOfInts;
   FHvector<int> fhVectorOfInts2;
   clock_t startTime, stopTime;

   // build both an array and a vector for comparing sorts
   for (k = 2; k < ARRAY_SIZE; k++)
   {
      arrayOfInts[k] = rand() % ARRAY_SIZE;
      fhVectorOfInts.push_back(arrayOfInts[k]);
      fhVectorOfInts2.push_back(arrayOfInts[k]);
   }

   cout << "Recursion Limit: quickSortX Sort Time" << endl;

   for (recLimit = 2; recLimit <= 300; recLimit+=2)
   {
      fhVectorOfInts2 = fhVectorOfInts;

      startTime = clock();  // ------------------ start
      quickSortX(fhVectorOfInts2, recLimit);
      stopTime = clock();  // ---------------------- stop
      cout << "\n" << recLimit << ": "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds.";
   }
   cout << endl << endl;
   quickSort(fhVectorOfInts);

   for (k = 0; k < ARRAY_SIZE; k+= ARRAY_SIZE/5)
   {
      cout << "quickSort #" << k << ": " << fhVectorOfInts[k] << endl;
      cout << "quickSortX #" << k << ": " << fhVectorOfInts2[k] << endl;
   }
   return 0;
}


/* ------------------------------ RUN -------------------------------------
 Recursion Limit: quickSortX Sort Time

 2: 0.009804 seconds.
 4: 0.00962 seconds.
 6: 0.009366 seconds.
 8: 0.009938 seconds.
 10: 0.010438 seconds.
 12: 0.012521 seconds.
 14: 0.011253 seconds.
 16: 0.012416 seconds.
 18: 0.013135 seconds.
 20: 0.013657 seconds.
 22: 0.013398 seconds.
 24: 0.013995 seconds.
 26: 0.012656 seconds.
 28: 0.010631 seconds.
 30: 0.010289 seconds.
 32: 0.010918 seconds.
 34: 0.01088 seconds.
 36: 0.010446 seconds.
 38: 0.010838 seconds.
 40: 0.01101 seconds.
 42: 0.01128 seconds.
 44: 0.01087 seconds.
 46: 0.011288 seconds.
 48: 0.011465 seconds.
 50: 0.014629 seconds.
 52: 0.012953 seconds.
 54: 0.012211 seconds.
 56: 0.012074 seconds.
 58: 0.012176 seconds.
 60: 0.012205 seconds.
 62: 0.012336 seconds.
 64: 0.012925 seconds.
 66: 0.013031 seconds.
 68: 0.013179 seconds.
 70: 0.013364 seconds.
 72: 0.014132 seconds.
 74: 0.016476 seconds.
 76: 0.013918 seconds.
 78: 0.013705 seconds.
 80: 0.013959 seconds.
 82: 0.014432 seconds.
 84: 0.014857 seconds.
 86: 0.014885 seconds.
 88: 0.014686 seconds.
 90: 0.015577 seconds.
 92: 0.015311 seconds.
 94: 0.015198 seconds.
 96: 0.015822 seconds.
 98: 0.016299 seconds.
 100: 0.015927 seconds.
 102: 0.015836 seconds.
 104: 0.015819 seconds.
 106: 0.016336 seconds.
 108: 0.01654 seconds.
 110: 0.017427 seconds.
 112: 0.016914 seconds.
 114: 0.017084 seconds.
 116: 0.016959 seconds.
 118: 0.017686 seconds.
 120: 0.017639 seconds.
 122: 0.017631 seconds.
 124: 0.018484 seconds.
 126: 0.018022 seconds.
 128: 0.021146 seconds.
 130: 0.020484 seconds.
 132: 0.018623 seconds.
 134: 0.020908 seconds.
 136: 0.019747 seconds.
 138: 0.020028 seconds.
 140: 0.018677 seconds.
 142: 0.019553 seconds.
 144: 0.019084 seconds.
 146: 0.019819 seconds.
 148: 0.022414 seconds.
 150: 0.021595 seconds.
 152: 0.022026 seconds.
 154: 0.020345 seconds.
 156: 0.020596 seconds.
 158: 0.020206 seconds.
 160: 0.020315 seconds.
 162: 0.020439 seconds.
 164: 0.020918 seconds.
 166: 0.022252 seconds.
 168: 0.021763 seconds.
 170: 0.021497 seconds.
 172: 0.02201 seconds.
 174: 0.022462 seconds.
 176: 0.023421 seconds.
 178: 0.022804 seconds.
 180: 0.022424 seconds.
 182: 0.022897 seconds.
 184: 0.022737 seconds.
 186: 0.022954 seconds.
 188: 0.022745 seconds.
 190: 0.02532 seconds.
 192: 0.027053 seconds.
 194: 0.025031 seconds.
 196: 0.024645 seconds.
 198: 0.023563 seconds.
 200: 0.023679 seconds.
 202: 0.026538 seconds.
 204: 0.024601 seconds.
 206: 0.02574 seconds.
 208: 0.024709 seconds.
 210: 0.024477 seconds.
 212: 0.02478 seconds.
 214: 0.026032 seconds.
 216: 0.025428 seconds.
 218: 0.030959 seconds.
 220: 0.026897 seconds.
 222: 0.026266 seconds.
 224: 0.026238 seconds.
 226: 0.02594 seconds.
 228: 0.02626 seconds.
 230: 0.027254 seconds.
 232: 0.027108 seconds.
 234: 0.027061 seconds.
 236: 0.030219 seconds.
 238: 0.028345 seconds.
 240: 0.030745 seconds.
 242: 0.027805 seconds.
 244: 0.031792 seconds.
 246: 0.031735 seconds.
 248: 0.031198 seconds.
 250: 0.028197 seconds.
 252: 0.028612 seconds.
 254: 0.031008 seconds.
 256: 0.032749 seconds.
 258: 0.029256 seconds.
 260: 0.03192 seconds.
 262: 0.032224 seconds.
 264: 0.030192 seconds.
 266: 0.031076 seconds.
 268: 0.030501 seconds.
 270: 0.030672 seconds.
 272: 0.031108 seconds.
 274: 0.030394 seconds.
 276: 0.03068 seconds.
 278: 0.03159 seconds.
 280: 0.033969 seconds.
 282: 0.031543 seconds.
 284: 0.032111 seconds.
 286: 0.034888 seconds.
 288: 0.032974 seconds.
 290: 0.031963 seconds.
 292: 0.034461 seconds.
 294: 0.03676 seconds.
 296: 0.036105 seconds.
 298: 0.032825 seconds.
 300: 0.037677 seconds.

 quickSort #0: 0
 quickSortX #0: 0
 quickSort #8000: 8035
 quickSortX #8000: 8035
 quickSort #16000: 16085
 quickSortX #16000: 16085
 quickSort #24000: 24110
 quickSortX #24000: 24110
 quickSort #32000: 32241
 quickSortX #32000: 32241
 Program ended with exit code: 0

 ------------------------------ RESULTS -----------------------------------

 +-----+--------+--------+---------+---------+---------+
 |     | 40,000 | 80,000 | 150,000 | 250,000 | 500,000 |
 +-----+--------+--------+---------+---------+---------+
 | 2   | .0118  | .0222  | .0394   | .0673   | .1634   |
 +-----+--------+--------+---------+---------+---------+
 | 4   | .0103  | .0228  | .0407   | .0706   | .1414   |
 +-----+--------+--------+---------+---------+---------+
 | 6   | .0092  | .0216  | .0387   | .0684   | .1406   |
 +-----+--------+--------+---------+---------+---------+
 | 8   | .0087  | .0231  | .0399   | .0649   | .1437   |
 +-----+--------+--------+---------+---------+---------+
 | 10  | .0088  | .0228  | .0412   | .0677   | .1484   |
 +-----+--------+--------+---------+---------+---------+
 | 12  | .0088  | .0218  | .0386   | .0655   | .1534   |
 +-----+--------+--------+---------+---------+---------+
 | 14  | .0091  | .0203  | .0400   | .0674   | .1501   |
 +-----+--------+--------+---------+---------+---------+
 | 16  | .0096  | .0206  | .0414   | .0677   | .1537   |
 +-----+--------+--------+---------+---------+---------+
 | 18  | .0092  | .0232  | .0385   | .0673   | .1701   |
 +-----+--------+--------+---------+---------+---------+
 | 20  | .0090  | .0230  | .0403   | .0674   | .1655   |
 +-----+--------+--------+---------+---------+---------+
 | 24  | .0099  | .0225  | .0386   | .0706   | .1491   |
 +-----+--------+--------+---------+---------+---------+
 | 28  | .0105  | .0229  | .0403   | .0690   | .1572   |
 +-----+--------+--------+---------+---------+---------+
 | 32  | .0098  | .0238  | .0426   | .0695   | .1574   |
 +-----+--------+--------+---------+---------+---------+
 | 36  | .0099  | .0245  | .0448   | .0726   | .1631   |
 +-----+--------+--------+---------+---------+---------+
 | 40  | .0102  | .0227  | .0440   | .0758   | .1633   |
 +-----+--------+--------+---------+---------+---------+
 | 60  | .0117  | .0264  | .0505   | .0943   | .1847   |
 +-----+--------+--------+---------+---------+---------+
 | 80  | .0135  | .0288  | .0567   | .0958   | .2042   |
 +-----+--------+--------+---------+---------+---------+
 | 100 | .0150  | .0320  | .0645   | .1088   | .2313   |
 +-----+--------+--------+---------+---------+---------+
 | 140 | .0193  | .0383  | .0754   | .1254   | .2700   |
 +-----+--------+--------+---------+---------+---------+
 | 180 | .0228  | .0499  | .0872   | .1816   | .3053   |
 +-----+--------+--------+---------+---------+---------+
 | 220 | .0264  | .0565  | .1008   | .1724   | .3621   |
 +-----+--------+--------+---------+---------+---------+
 | 260 | .0298  | .0611  | .1131   | .1896   | .4030   |
 +-----+--------+--------+---------+---------+---------+
 | 300 | .0344  | .0691  | .1318   | .2128   | .4427   |
 +-----+--------+--------+---------+---------+---------+

 ---------------------------- ANALYSIS -------------------------------

 Based off the above results, it seems like the length of time the sorting
 takes initially gets faster, but then takes longer as the recursion limit is
 set to a higher value. Starting at 2, the time taken is relatively fast. As
 the limit moves through the 10-20 range, the time taken decreases by a
 relatively small amount, but still significant. Gradually moving through the
 20's into the 30's and beyond, the sort time continues to grow at a relatively
 consistent speed. As the limit moves into the hundreds, it starts to increase
 in search time faster. Most array sizes were at their lowest time around the
 10-16 range, 12 being the most commonly lowest.

 It is difficult to draw too many strong conclusions about the data because as
 can be seen in the table there is a fair amount of fluctuation in the increase
 and decrease of times, even between two similar values. However, it seems safe
 to conclude that the sort time is lowest in a range of 4-30, and is lowest
 around 12-16, and gradually increases in sort time beyond 30, accelerating
 slowly as it passes into the hundreds. From this, then, we can assess the
 suggested 15 limit as a safe bet for being close to the best possible time for
 the algorithm. Comparing this test to using insertionSort() directly, or
 rather using quickSortX() with a limit value equal to the array size, results
 in sort times over 100 times slower, demonstrating the huge time saving the
 quickSort method results in.

 ---------------------------------------------------------------------*/


