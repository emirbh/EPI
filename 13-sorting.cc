#include <iostream>
#include <limits>

using std::cout;
using std::endl;

#include "idebug.h"
#include "sorts.h"

template <typename T>
struct Person : Groupable<T> {
 public:
  string name;
};

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
        /*
         *  @TODO Complete
         */
        vector<string> v;
        readArray(v);
        //printContainer(v);
        vector<Person<string>> people(v.size()/2);
        for(int i = 0; i < (int) v.size()/2; i++) {
          Person<string> p;
          p.key = v[i*2];
          p.name = v[i*2+1];
          people[i] = p;
        }
        for_each(people.begin(), people.end(),
                 [](const Person<string> &p) -> void {
                 cout << p.key << ":" << p.name << endl; } );
        //GroupByKey<string>::group((vector<Groupable<string>> &) people);
        GroupByKey<string>::group((vector<Groupable<string>> &) people);
        break;
      }
      default: {
        break;
      }
    }

    cin >> part;
  }
}
