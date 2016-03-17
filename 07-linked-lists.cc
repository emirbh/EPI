#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#include "idebug.h"
#include "llists.h"

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
        vector<int> v;
        vector<int> v1;
        vector<int> v2;
        readArray(v);
        readArray(v1);
        readArray(v2);
        LinkedList<int> ll(v);
        LinkedList<int> ll1(v1);
        LinkedList<int> ll2(v2);
        ll.print();
        ll1.print();
        ll2.print();
        ll1.merge(ll2);
        ll1.print();
        break;
      }
      /* ---- 06 ------------------------------------------------------------ */
      case 6: {
        /*
         *  @TODO DO AGAIN, NOT GOOD
         */
        vector<int> v;
        readArray(v);
        LinkedList<int> l(v);
        l.print();
        l.sortOddEven();
        l.print();
        break;
      }
    }

    cin >> part;
  }
}

