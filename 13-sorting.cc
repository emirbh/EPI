#include <iostream>
#include <limits>

using std::cout;
using std::endl;

#include "idebug.h"
#include "sorts.h"

int main() {
  int part;
  cin >> part;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  while(part != -1) {
    cout << "Part: " << part << "----------------------------------------";
    cout << "--------------------------------" << endl;

    switch(part) {
      /* ---- 02 ------------------------------------------------------------ */
      case 2: {
        vector<int> v;
        readArray(v);
        printContainer(v);
        vector<int *> *sorted = QSortLarge<int>::sort(v);
        for_each(sorted->begin(), sorted->end(),
                 [](int *ptr) -> void { cout << *ptr << " "; } );
        cout << endl;
        break;
      }
      /* ---- 04 ------------------------------------------------------------ */
      case 4: {
        vector<string> v;
        readArray(v);
        //printContainer(v);

        vector<Groupable<string>> people(v.size()/2);
        for(int i = 0; i < (int) v.size()/2; i++) {
          Groupable<string> p;
          p.key = v[i*2];
          p.name = v[i*2+1];
          people[i] = p;
        }
        for_each(people.begin(), people.end(),
                 [](const Groupable<string> &p) -> void {
                 cout << p.key << ":" << p.name << endl; } );
        //GroupByKey<string>::group((vector<Groupable<string>> &) people);
        GroupByKey<string>::group((vector<Groupable<string>> &) people);
        break;
      }
      /* ---- 10 ------------------------------------------------------------ */
      case 10: {
        vector<vector<int>> m;
        readMatrix(m);
        printMatrix(m, "---- in --------");
        vector<pair<int, int>> intervals;
        int max = CalendarConcurrency::getMaxConcurrency(m);
        cout << "Max Concurrency = " << max << endl;
        break;
      }
      /* ---- -1 ------------------------------------------------------------ */
      default: {
        break;
      }
    }

    cin >> part;
  }
}
