#ifndef __SORTS_H__
#define __SORTS_H__

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using std::cout;
using std::endl;
using std::vector;
using std::sort;
using std::unordered_map;
using std::pair;

/*******************************************************************************
 *  class QSortLarge
 */
template <typename T>
class QSortLarge {
 public:
  QSortLarge() {}

  static vector<T *> * sort(vector<T> &v) {
    vector<T *> *ptrs = (vector<T *> *) new vector<T *>();
    for(T &t : v) {
      ptrs->emplace_back(&t);
    }

    std::sort(ptrs->begin(), ptrs->end(),
      [] (const T *a, const T *b) -> bool { return *a < *b; });

    return ptrs;
  }
};

/*******************************************************************************
 *  class QSortLarge
 */
template <typename T>
struct Groupable {
 public:
  T key;
};

template <typename T>
class GroupByKey {
 public:
  GroupByKey() {
  }

  static void group(vector<Groupable<T>> &v) {
    unordered_map<T, int> group_per_key;
    /**
    for_each(v.begin(), v.end(),
             [](Groupable<T> &grp) -> void { cout << grp.key << endl; } );
     */

    /**
     *  Get counts per key
     */

    cout << "size " << v.size() << endl;
    /*
    for(const Groupable<T> &ref : v) {
      auto grpIt = group_per_key.find(ref.key);
      if(grpIt != group_per_key.end()) {
        grpIt->second++;
      } else {
        group_per_key[ref.key] = 1;
      }
    }
     */

    /*
    for_each(group_per_key.begin(), group_per_key.end(),
             [](const pair<T, int> &p) -> void {
               cout << p.first << ":" << p.second << endl; } );
     */

    /**
     *  Calculate offsets
     */
  }
 private:
};

#endif /* __SORTS_H__ */
