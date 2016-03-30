#include <iostream>
#include <limits>

using std::cin;
using std::cout;
using std::endl;

#include "idebug.h"
#include "metas.h"

int main() {
  int part;
  cin >> part;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  while(part != -1) {
    cout << "Part: " << part << "----------------------------------------";
    cout << "--------------------------------" << endl;

    switch(part) {
      /* ---- 01 ------------------------------------------------------------ */
      case 1: {
        cout << "EPI: ";
        cout << "Skyline" << endl;
        Skyline<int,int> skyline;
        int nBuildings;
        cin >> nBuildings;
        for(int i = 0; i < nBuildings; ++i) {
          int left, right, height;
          cin >> left >> right >> height;
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          Building<int,int> b(left, right, height);
          skyline.addBuilding(b);
        }
        /*
         */
        skyline.calcSkyline();
        break;
      }
      /* ---- 02 ------------------------------------------------------------ */
      case 2: {
        cout << "EPI: ";
        cout << "Inversion Pairs" << endl;
        vector<int> v;
        readArray(v);
        InvertedPairs<int> ip(v);
        vector<pair<int,int>> inv;
        int inversions = ip.getInvertedPairs(inv);
        cout << "Inversions: " << inversions << endl;
        for_each(inv.begin(), inv.end(), [](const pair<int,int> &p) ->
                 void { cout << p.first << ":" << p.second << endl; });
        break;
      }
      /* ---- 03 ------------------------------------------------------------ */
      case 3: {
        cout << "EPI: ";
        cout << "Closest point in Cartesian Plane" << endl;
        vector<vector<int>> v;
        readMatrix(v);
        Cartesian2D<int> plane(v);
        pair<int,int> closest = plane.getClosestPair();
        cout << "Closest distance is between points " << closest.first;
        cout << " and " << closest.second << endl;
        break;
      }
      /* ---- 05 ------------------------------------------------------------ */
      case 5: {
        cout << "EPI: ";
        cout << "Cyclical Array Maximum Sub-Array Sum" << endl;
        vector<int> v;
        readArray(v);
        printContainer(v);
        int result = MaxSubArray<int>::calculate(v);
        cout << "Max = " << result << endl;
        break;
      }
      /* ---- 40 ------------------------------------------------------------ */
      case 40: {
        cout << "EPI: ";
        cout << "Maximum Sub-Array Sum" << endl;
        vector<int> v;
        readArray(v);
        printContainer(v);
        int result = MaxSubArray<int>::calculateStraight(v);
        cout << "Max = " << result << endl;
        break;
      }
      default: {
        break;
      }
    }

    cin >> part;
  }
}
