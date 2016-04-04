#include <iostream>
#include <limits>

using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;

#include "idebug.h"
#include "heaps.h"

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
        cout << "Merge multiple sources Flag" << endl;
        vector<vector<int>> m;
        readMatrix(m);
        HeapMerge<int> h;
        vector<int> v = h.merge(m);
        printContainer(v);
        break;
      }
      /* ---- 02 ------------------------------------------------------------ */
      case 2: {
        cout << "EPI: ";
        cout << "K-Ineasing-Decreasing Sort" << endl;
        vector<int> v;
        readArray(v);
        printContainer(v);
        HeapMerge<int> h;
        vector<int> sorted = h.sortKIncreaseDecrease(v);
        printContainer(sorted);
        break;
      }
      /* ---- 03 ------------------------------------------------------------ */
      case 3: {
        cout << "EPI: ";
        cout << "Stach using heap" << endl;
        vector<int> v;
        readArray(v);
        printContainer(v);
        HStack<int> hs;
        for(int i = 0; i < (int) v.size(); i++) {
          hs.push(v[i]);
        }
        for(int i = 0; i < (int) v.size(); i++) {
          cout << hs.pop() << " ";
        }
        cout << endl;
        break;
      }
      /* ---- 04 ------------------------------------------------------------ */
      case 4: {
        /*
         *  @TODO Understand this !
         */
        break;
      }
      /* ---- 05 ------------------------------------------------------------ */
      case 5: {
        /*
         *  @TODO Understand this !
         */
        break;
      }
      /* ---- 06 ------------------------------------------------------------ */
      case 6: {
        /*
         *  @TODO Understand this !
         */
        break;
      }
      /* ---- 08 ------------------------------------------------------------ */
      case 8: {
        cout << "EPI: ";
        cout << "Heap running medium" << endl;
        vector<int> v;
        readArray(v);
        HeapRunningMedian<int> hrm;
        for(int i = 0; i < (int) v.size(); i++) {
          double median = hrm.add(v[i]);
          cout << "Add " << v[i] << ".  Current median=" << median << endl;
        }
        break;
      }
      default: {
        break;
      }
    }

    cin >> part;
  }
}
