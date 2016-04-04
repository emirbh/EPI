#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#include "stacks-queues.h"

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
      /* ---- 02 ------------------------------------------------------------ */
      case 2: {
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
        printContainer(v);
        StackSort<int> s(v);
        stack<int> sorted = s.sort();
        while(!sorted.empty()) {
          auto i = sorted.top(); sorted.pop();
          cout << i << endl;
        }
        break;
      }
      /* ---- 09 ------------------------------------------------------------ */
      case 9: {
        vector<int> v;
        readArray(v);
        printContainer(v);
        QueueViaVector<int> qvv;
        for(int i = 0; i < (int) v.size(); i++) {
          qvv.enqueue(v[i]);
        }
        for(int i = 0; i < (int) v.size(); i++) {
          cout << qvv.dequeue() << " ";
        }
        cout << endl;
        break;
      }
      /* ---- 14 ------------------------------------------------------------ */
      case 14: {
        /*
         *  @TODO this is from mock interview, implement
         */
        vector<vector<int>> m;
        readMatrix(m);
        printMatrix(m);
        int t, max;
        cin >> t >> max;
        break;
      }
    }

    cin >> part;
  }
}
