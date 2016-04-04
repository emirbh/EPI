#include <iostream>
#include <limits>

using std::cin;
using std::cout;
using std::endl;

#include "idebug.h"
#include "intractability.h"

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
        cout << "Electtion Tie" << endl;
        vector<int> v;
        readArray(v);
        ElectionTie et(v);
        break;
      }
      /* ---- 02 ------------------------------------------------------------ */
      case 2: {
        cout << "EPI: ";
        cout << "Knapsack problem" << endl;
        vector<vector<int>> m;
        readMatrix(m);
        int weight;
        cin >> weight;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Knapsack knapsack(m);
        knapsack.pack(weight);
        break;
      }
      /* ---- 09 ------------------------------------------------------------ */
      case 9: {
        cout << "EPI: ";
        cout << "Expression Synthesis" << endl;
        vector<int> v;
        readArray(v);
        int value;
        cin >> value;
        ExpressionSynthesis es(v, value);
        es.evaluate();
        break;
      }
      /* ---- 10 ------------------------------------------------------------ */
      case 10: {
        cout << "EPI: ";
        cout << "Multiplication Minimum" << endl;
        /*
         *  @TODO try to understand this better
         */
        int exp;
        cin >> exp;
        MultiplicationMinimum mm(exp);
        break;
      }
      default: {
        break;
      }
    }

    cin >> part;
  }
}
