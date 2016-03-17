#ifndef __METAS_H__
#define __METAS_H__

#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::copy;
using std::back_inserter;
using std::min;
using std::max;
using std::pair;

#include "idebug.h"

/*******************************************************************************
 *  class Skyline
 */
template <typename CoordType, typename HeightType>
class Building {
 public:
  Building(CoordType left, CoordType right, HeightType height)
      : left(left), right(right), height(height) {
  }

  int idx;
  CoordType left, right;
  HeightType height;
};

/*******************************************************************************
 *  class Skyline
 */
template <typename CoordType, typename HeightType>
class Skyline {
 public:
  typedef Building<CoordType,HeightType> TBuilding;
  Skyline() {
  }

  void addBuilding(TBuilding &b) {
    b.idx = (int) buildings.size();
    buildings.push_back(b);
  }

  void calcSkyline() {
    Buildings bldgs = calcSkylineHelper(buildings, 0, buildings.size());
    for(const TBuilding &b : bldgs) {
      cout << b.left << ":" << b.right << ":" << b.height << endl;
    }
  }

 private:
  typedef vector<TBuilding> Buildings;
  Buildings buildings;

  Buildings calcSkylineHelper(Buildings &bldgs, int start, int end) {
    if(start >= end-1) {
      Buildings b;
      b.push_back(bldgs[start]);
      return b;
    }
    int mid = start + (end - start) / 2;
    iLog(0, "Split %d:%d to %d:%d:%d", start, end, start, mid, end);
    Buildings left = calcSkylineHelper(bldgs, start, mid);
    Buildings right = calcSkylineHelper(bldgs, mid, end);
    return mergeBuildings(left, right);
  }

  Buildings mergeBuildings(Buildings  &l, Buildings &r) {
    /*
     *  --L--
     *        --R--
     *
     *        --L--
     *  --R--
     *
     *  --L--
     *     --R--    merge skylines
     *
     *     --L--
     *  --R--       merge skylines
     */
    int i = 0, j = 0;
    Buildings bldgs;
    while(i < (int) l.size() && j < (int) r.size()) {
      iLog(1, "Merge [%d]=%d:%d:%d and [%d]=%d:%d:%d",
           l[i].idx, l[i].left, l[i].right, l[i].height,
           r[j].idx, r[j].left, r[j].right, r[j].height);
      if(l[i].right <= r[j].left) {
        iLog(2, "push %d", l[i].idx);
        bldgs.push_back(l[i++]);
      } else if(r[j].right <= l[i].left) {
        iLog(2, "push %d", r[j].idx);
        bldgs.push_back(r[j++]);
      } else if(l[i].left < r[j].left) {
        mergeSkyline(bldgs, l[i++], r[j++]);
      } else /* if(r.left < l.left) */ {
        mergeSkyline(bldgs, r[j++], l[i++]);
      }
    }
    copy(l.cbegin()+i, l.cend(), back_inserter(bldgs));
    copy(r.cbegin()+j, r.cend(), back_inserter(bldgs));
    return bldgs;
  }

  void mergeSkyline(Buildings &bldgs, TBuilding &l, TBuilding &r) {
    iLog(2, "Old [%d]=%d:%d:%d and [%d]=%d:%d:%d",
         l.idx, l.left, l.right, l.height,
         r.idx, r.left, r.right, r.height);

    /*
     *  --L--
     *   -R-
     *
     *  --L--
     *    --R--
     */
    TBuilding m(r.left, min(l.right, r.right), max(l.height, r.height));
    m.idx = l.idx;

    l.right = r.left;
    iLog(2, "push %d", l.idx);
    bldgs.push_back(l);

    bldgs.push_back(m);
    iLog(2, "push %d-m", m.idx);

    r.left = m.right;
    if(r.left != r.right) {
      bldgs.push_back(r);
      iLog(2, "push %d", r.idx);
    }

    iLog(3, "New [%d]=%d:%d:%d -> [%d]=%d:%d:%d-> [%d]=%d:%d:%d",
         l.idx, l.left, l.right, l.height,
         m.idx, m.left, m.right, m.height,
         r.idx, r.left, r.right, r.height);
  }
};

/*******************************************************************************
 *  class InvertedPairs
 */
template <typename T>
class InvertedPairs {
 public:
  InvertedPairs(vector<T> &v)
      : v(v) {
  }

  int getInvertedPairs(vector<pair<int,int>> &inversions) {
    return inversionsHelper(v, inversions, 0, v.size());
  }

 private:
  vector<T> &v;

  int inversionsHelper(vector<T> &v, vector<pair<int,int>> &inv,
                       int start, int end) {
    if(end - start <= 1) {
      return 0;
    }
    int mid = start + (end - start) / 2;

    iLog(0, "Split %d:%d to %d:%d:%d", start, end, start, mid, end);
    printContainer(v, "inversionsHelper");

    int inversions = inversionsHelper(v, inv, start, mid) +
                     inversionsHelper(v, inv, mid, end) +
                     merge(v, inv, start, mid, end);

    iLog(0, "Inversions %d:%d:%d = %d", start, mid, end, inversions);
    return inversions;
  }

  int merge(vector<T> &v, vector<pair<int,int>> &inv,
            int start, int mid, int end) {
    int left = start, right = mid;
    int inverted = 0;
    vector<T> sorted;

    (void) inv;

    printContainer(v, "\tmerge-pre");
    iLog(1, "Merge %d:%d:%d", start, mid, end);

    while(left < mid && right < end) {
      if(v[left] <= v[right]) {
        sorted.emplace_back(v[left++]);
      } else {
        iLog(3, "Inversion %d:%d", left, right);
        inverted++;
        inv.emplace_back(pair<int,int>{left, right});
        sorted.emplace_back(v[right++]);
      }
      printContainer(sorted, "\tsorted");
    }
    /*
    copy(v.begin() + left, v.begin() + mid, back_inserter(sorted));
    copy(v.begin() + mid, v.begin() + end, back_inserter(sorted));
     */
    if(left < mid)
      copy(v.cbegin() + left, v.cbegin() + mid, back_inserter(sorted));
    if(right < end)
      copy(v.cbegin() + mid, v.cbegin() + end, back_inserter(sorted));

    copy(sorted.cbegin(), sorted.cend(), v.begin() + start);
    printContainer(v, "\tmerge-post");

    return inverted;
  }
};

#endif /* __METAS_H__ */
