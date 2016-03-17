#include <iostream>
#include <limits>
#include <unordered_map>

using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::unordered_map;
using std::min;

#include "idebug.h"
#include "hashes.h"

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
        vector<string> v;
        readArray(v);
        printContainer(v);
        const int MODULUS = 9999999;
        for(int i = 0; i < (int) v.size(); i++) {
          cout << v[i] << " : key = " << getStringKey(v[i], MODULUS) << endl;
        }
        break;
      }
      /* ---- 03 ------------------------------------------------------------ */
      case 3: {
        vector<string> v;
        readArray(v);
        printContainer(v);
        unordered_map<string,int> word_distance;
        int min_distance = numeric_limits<int>::max();
        string min_word = "NA";
        for(int i = 0; i < (int) v.size(); i++) {
          auto lastPos = word_distance.find(v[i]);
          if(lastPos != word_distance.end()) {
            if(i - word_distance[v[i]] < min_distance) {
              min_distance = i - word_distance[v[i]];
              min_word = v[i];
            }
          }
          word_distance[v[i]] = i;
        }
        cout << "Min Distance: " << min_word << ":" << min_distance << endl;
        break;
      }
      default: {
        break;
      }
    }

    cin >> part;
  }
}
