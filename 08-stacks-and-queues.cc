#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#include "stacks.h"

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
        readArray(v);
        StackMax<int> sm;
        for(int i = 0; i < (int) v.size(); i++) {
          int value = v[i];
          sm.push(value);
          int maxv = sm.max();
          cout << "Push (max) = " << value << " (" << maxv << ")" << endl;
        }
        for(int i = 0; i < (int) v.size(); i++) {
          int maxv = sm.max();
          int value = sm.pop();
          cout << "Pop (max) = " << value << " (" << maxv << ")" << endl;
        }
        break;
      }
      /* ---- 05 ------------------------------------------------------------ */
      case 5: {
        int nPegs, nDisks;
        cin >> nPegs >> nDisks;
        StackHanoi<int> sh(nPegs, nDisks);
        sh.transfer(1);
        break;
      }
      /* ---- 06 ------------------------------------------------------------ */
      case 6: {
        vector<int> v;
        readArray(v);
        StackSunset<int> s(v);
        stack<StackSunset<int>::Building> view = s.getSunsetView();
        while(!view.empty()) {
          auto b = view.top(); view.pop();
          cout << "b[" << b.idx << "]=" << b.height << endl;
        }
        break;
      }
      /* ---- 07 ------------------------------------------------------------ */
      case 7: {
        vector<int> v;
        readArray(v);
        StackSort<int> s(v);
        stack<int> sorted = s.sort();
        while(!sorted.empty()) {
          auto i = sorted.top(); sorted.pop();
          cout << i << endl;
        }
        break;
      }
      /* ---- 02 ------------------------------------------------------------ */
      case 2: {
        break;
      }
    }

    cin >> part;
  }
}
