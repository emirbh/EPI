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
      default: {
        break;
      }
    }

    cin >> part;
  }
}
