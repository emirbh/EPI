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
      /* ---- 05 ------------------------------------------------------------ */
      case 5: {
        cout << "EPI: ";
        cout << "Find Minimum in Cyclical Array" << endl;
        vector<int> v;
        readArray(v);
        printContainer(v);
        int min = findMinInCycle(v);
        cout << "Min = " << min << endl;
        break;
      }
      /* ---- 07 ------------------------------------------------------------ */
      case 7: {
        cout << "EPI: ";
        cout << "Completion Search" << endl;
        vector<int> v;
        readArray(v);
        printContainer(v, "in");
        int newSum;
        cin >> newSum;
        cout << "New Sum = " << newSum << endl;
        int sigma = computeCompletionSearch(v, newSum);
        cout << "Sigma = " << sigma << endl;
        break;
      }
      /* ---- 08 ------------------------------------------------------------ */
      case 8: {
        cout << "EPI: ";
        cout << "Find k-th in two arrays" << endl;
        vector<int> a, b;
        readArray(a);
        readArray(b);
        printContainer(a, "a");
        printContainer(b, "b");
        int k;
        cin >> k;
        cout << "k = " << k << endl;
        int kth = findKthInTwoArrays(a, b, k);
        cout << "k-th element = " << kth << endl;
        break;
      }
      /* ---- 09 ------------------------------------------------------------ */
      case 9: {
        cout << "EPI: ";
        cout << "Calculate Square Root" << endl;
        int i;
        double d;
        cin >> i >> d;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "root(" << i << ")=" << SquareRoot::calculate(i) << endl;
        cout << "root(" << d << ")=" << SquareRoot::calculate(d) << endl;
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
