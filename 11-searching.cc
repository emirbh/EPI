#include <iostream>
#include <limits>

using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;

#include "idebug.h"
#include "searches.h"

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
        cout << "Find first occurence" << endl;
        vector<int> v;
        readArray(v);
        printContainer(v);
        int number;
        cin >> number;
        int index = searchFirst(v, number);
        cout << "Number " << number << " found at " << index << endl;
        break;
      }
      /* ---- 02 ------------------------------------------------------------ */
      case 2: {
        cout << "EPI: ";
        cout << "Find first occurence" << endl;
        vector<int> v;
        readArray(v);
        printContainer(v);
        int number;
        cin >> number;
        int larger = searchFirstLarger(v, number);
        cout << "First larger " << larger << " than number " << number << endl;
        break;
      }
      /* ---- 04 ------------------------------------------------------------ */
      case 4: {
        /*
         *  @TODO Understand negative numbers
         */
        break;
      }
      /* ---- 07 ------------------------------------------------------------ */
      case 7: {
        /*
         *  @TODO Don't uderstand at all
         */
        break;
      }
      /* ---- 08 ------------------------------------------------------------ */
      case 8: {
        /*
         *  @TODO Don't uderstand at all
         */
        break;
      }
      /* ---- 10 ------------------------------------------------------------ */
      case 10: {
        cout << "EPI: ";
        cout << "Find in 2D" << endl;
        vector<vector<int>> m;
        readMatrix(m);
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        pair<int,int> p = searchIn2D(m, n);
        cout << "Coordinates: " << p.first << "," << p.second << endl;
        break;
      }
      default: {
        break;
      }
    }

    cin >> part;
  }
}
