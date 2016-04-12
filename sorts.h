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
using std::max;

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
  T name;
};

template <typename T>
class GroupByKey {
 public:
  GroupByKey() {
  }

  static void group(vector<Groupable<T>> &v) {
    unordered_map<T, int> group_per_key;
    /*
    for_each(v.begin(), v.end(),
             [](Groupable<T> &grp) -> void { cout << grp.key << endl; } );
     */

    /**
     *  Get counts per key
     */

    cout << "size " << v.size() << endl;
    for(const Groupable<T> &ref : v) {
      auto grpIt = group_per_key.find(ref.key);
      if(grpIt != group_per_key.end()) {
        grpIt->second++;
      } else {
        group_per_key[ref.key] = 1;
      }
    }

    /**
     *  Calculate offsets
     */
    unordered_map<T,int> key_to_offset;
    int offset = 0;
    for(const pair<T,int> &p : group_per_key) {
      key_to_offset[p.first] = offset;
      offset += p.second;
    }

    /*
     */
    cout << "Offsets & Counts -----------------------" << endl;
    for_each(key_to_offset.begin(), key_to_offset.end(),
             [&group_per_key](const pair<T, int> &p) -> void {
               cout << p.first << "=" << p.second << ":";
               cout << group_per_key[p.first] <<  endl;
               } );

    /**
     *  re-rder
     */
    while(key_to_offset.size()) {
      auto from = key_to_offset.begin();
      iLog(0, "Process group %s with offset %d",
           from->first.c_str(), from->second);
      int from_offset = from->second;
      auto to = key_to_offset.find(v[from_offset].key);
      iLog(1, "swap from:[%d]=%s:%s with to:[%d]=%s:%s",
           from->second,
           v[from->second].key.c_str(), v[from->second].name.c_str(),
           to->second,
           v[to->second].key.c_str(), v[to->second].name.c_str());
      swap(v[from->second], v[to->second]);
      if(--group_per_key[to->first]) {
        to->second++;
        iLog(2, "New to->second %s->%d", to->first.c_str(), to->second);
      } else {
        iLog(2, "Done with to %s", to->first.c_str());
        key_to_offset.erase(to);
      }
      for_each(v.begin(), v.end(),
               [](Groupable<T> &grp) -> void {
                 cout << "\t\t" << grp.key << ":" << grp.name << endl; } );
    }

    cout << "Sorted ---------------------------------" << endl;
    for_each(v.begin(), v.end(),
             [](Groupable<T> &grp) -> void {
               cout << grp.key << ":" << grp.name << endl; } );
    /*
     */
  }
 private:
};

/*******************************************************************************
 *  class CalendarConcurrency
 */
class CalendarConcurrency {
 public:
  struct TimePoint {
    int time;
    bool isStart;

    bool operator < (const TimePoint &that) const {
      return time != that.time ?  time < that.time : (isStart && !that.isStart);
    }
  };

  static int getMaxConcurrency(vector<vector<int>> &m) {
    vector<TimePoint> points;
    for_each(m.cbegin(), m.cend(),
        [&points](const vector<int> &v) -> void {
          points.emplace_back(TimePoint{v[0], true});
          points.emplace_back(TimePoint{v[1], false});
        });
    sort(points.begin(), points.end());

    int maxConcurr = 0, concurr = 0;
    for(const TimePoint &pt : points) {
      if(pt.isStart) {
        maxConcurr = max(++concurr, maxConcurr);
      } else {
        --concurr;
      }
    }
    return maxConcurr;
  }

 private:
};

#endif /* __SORTS_H__ */
