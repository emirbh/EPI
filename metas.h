#ifndef __METAS_H__
#define __METAS_H__

#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <cmath>
#include <tuple>
#include <stack>

using std::cout;
using std::endl;
using std::vector;
using std::copy;
using std::back_inserter;
using std::min;
using std::max;
using std::pair;
using std::array;
using std::sqrt;
using std::pow;
using std::tuple;
using std::get;
using std::abs;
using std::stack;
using std::partial_sum;
using std::upper_bound;

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

 protected:
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
    iLog(0, "-> Split Done for %d:%d", start, mid);
    Buildings right = calcSkylineHelper(bldgs, mid, end);
    iLog(0, "-> Split Done for %d:%d", mid, end);
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

    iLog(2, "New [%d]=%d:%d:%d -> [%d]=%d:%d:%d-> [%d]=%d:%d:%d",
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

/*******************************************************************************
 *  class MaxSubArray
 */
template <typename T>
class MaxSubArray {
 public:
  static T calculateCircular(vector<T> v) {
    /*
     *  calculate maximum from 0 to i
     */
    vector<T> max_begin;
    T sum;
    sum = v[0];
    max_begin.emplace_back(sum);
    for(int i = 1; i < static_cast<int>(v.size()); i++) {
      sum += v[i];
      max_begin.emplace_back(max(sum,v[i]));
    }

    /*
     *  calculate maximum from i+1 to n
     */
    vector<T> max_end;
    sum = 0;
    for(int i = static_cast<int>(v.size()-2); i >= 0; i--) {
      sum += v[i+1];
      max_end.emplace_back(max(sum, v[i+1]));
    }

    /*
     *  calculate circular maximum
     */
    printContainer(max_begin, "max_begin");
    printContainer(max_end, "max_end");
    T max_circular = 0;
    for(int i = static_cast<int>(v.size()-2); i >= 0; i--) {
      if(max_begin[i] + max_end[i] > max_circular) {
        iLog(1, "New maximum at %d = %d + %d", i, max_begin[i], max_end[i]);
      }
      max_circular = max(max_circular, max_begin[i] + max_end[i]);
    }
    iLog(0, "Max circular %d", max_circular);

    return max_circular;
  }

  static T calculateStraight(vector<T> v) {
    int minSum = 0, maxSum = numeric_limits<T>::min();
    int sum = 0, minIdx = -1, maxIdx = -1;
    for(int i = 0; i < static_cast<int>(v.size()); i++) {
      sum += v[i];
      if(sum < minSum) {
        iLog(1, "New Min at %d: %d", i, sum);
        minSum = sum; minIdx = i;
      }
      if(sum - minSum > maxSum) {
        iLog(1, "New Max at %d: %d", i, sum - minSum);
        maxSum = sum - minSum, maxIdx = i;
      }
    }
    iLog(0, "MaxSum[%d:%d] = %d", minIdx+1, maxIdx+1, maxSum);
    return maxSum;
  }

  static T calculate(vector<T> v) {
    T circular = calculateCircular(v);
    T straight = calculateStraight(v);
    iLog(0, "circular=%d straight=%d", circular, straight);
    return max(circular, straight);
  }

 protected:
};

/*******************************************************************************
 *  class Cartesian2D
 */
template <typename T>
class Cartesian2D {
 public:
  Cartesian2D(vector<vector<T>> &pts) {
    for(int i = 0; i < (int) pts.size(); i++) {
      points.emplace_back(Point{i, pts[i][0], pts[i][1]});
    }
    for_each(points.cbegin(), points.cend(), [](const Point &pt) -> void {
        iLog(0, "%d = %d:%d", pt.idx, pt.x, pt.y);
        } );
  }

  pair<int,int> getClosestPair() {
    iLog(0, "Start");
    Distance maxDist = getClosestPairHelper(points, 0, points.size());
    return pair<int,int>{get<0>(maxDist),get<1>(maxDist)};
  }

 protected:
  struct Point {
    int idx;
    T x, y;
  };
  typedef vector<Point> Points;
  typedef tuple<int,int,double> Distance;

  Points points;

  /*
   *  initDistance()
   */
  Distance initDistance() {
    return Distance{-1,-1,numeric_limits<double>::max()};
  }

  /*
   *  calculateDistance()
   */
  double calculateDistance(Point &p1, Point &p2) {
    double dist = sqrt( pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) );
    iLog(0, "....%d:%d:%d to %d:%d:%d distance %f",
         p1.idx, p1.x, p1.y, p2.idx, p2.x, p2.y,
         dist);
    return dist;
  }

  Distance getClosestPairHelper(Points pts, int start, int end, int level=0) {
    int mid = start + (end - start) / 2;
    iLog(level, "Split %d:%d into %d:%d:%d", start, end, start, mid, end);

    if(end - start <= 3) {
      return getClosestBrute(pts, start, end);
    }

    Distance left = getClosestPairHelper(pts, 0, mid, level++);
    iLog(level, "-> Done Split %d:%d -> maxDist=%f", start, mid, get<2>(left));
    Distance right = getClosestPairHelper(pts, mid, end, level++);
    iLog(level, "-> Done Split %d:%d -> maxDist=%f", mid, end, get<2>(right));
    Distance minDist = get<2>(left) < get<2>(right) ? left : right;
    iLog(level, "minDistance %d:%d -> %f", get<0>(minDist), get<1>(minDist),
         get<2>(minDist));

    /*
     *  Account for "merge", or better compare all points (if any) in the
     *  radius of current minimum x coordinate
     */
    Points remain;
    for(const Point &pt : pts) {
      if(abs(pt.x - pts[mid].x) < get<2>(minDist)) {
        remain.emplace_back(pt);
      }
    }
    if(remain.size() > 0) {
      sort(remain.begin(), remain.end(),
           [](const Point &pt1, const Point & pt2) -> bool {
             return pt1.y < pt2.y;
           });
      Distance remainDist = getClosestBrute(remain, 0, remain.size());
      if(get<0>(remainDist) >= 0 && get<1>(remainDist) >= 0 &&
         get<2>(remainDist) < get<2>(minDist)) {
        minDist = remainDist;
        iLog(level, "Got new minimum distance from remaininig %d:%d -> %f",
             get<0>(minDist), get<1>(minDist), get<2>(minDist));
      }
    }

    return minDist;
  }

  Distance getClosestBrute(Points pts, int start, int end) {
    Distance minDist = initDistance();
    for(int i = start; i < end; i++) {
      for(int j = i+1; j < end; j++) {
        double distance = calculateDistance(pts[i], pts[j]);
        if(distance < get<2>(minDist)) {
          get<0>(minDist) = pts[i].idx;
          get<1>(minDist) = pts[j].idx;
          get<2>(minDist) = distance;
        }
      }
    }
    if(get<0>(minDist) >= 0 && get<1>(minDist) >= 0) {
      iLog(1, "Brute distance %d:%d -> %f", start, end, get<2>(minDist));
    }
    return minDist;
  }
};

/*******************************************************************************
 *  class LargestRectangle
 */
class LargestRectangle {
 public:
  static int calculate(vector<int> A) {
    stack<int> s;
    vector<int> L, R;

    for(int i = 0; i < (int) A.size(); i++) {
      while(!s.empty() && A[s.top()] >= A[i]) {
        s.pop();
      }
      L.emplace_back(s.empty() ? -1 : s.top());
      s.push(i);
    }

    while(!s.empty()) s.pop();

    for(int i = (int) A.size()-1; i >= 0; i--) {
      while(!s.empty() && A[s.top()] >= A[i]) {
        s.pop();
      }
      R.emplace_back(s.empty() ? A.size() - 1 : s.top());
      s.push(i);
    }

    printContainer(L, "L");
    printContainer(R, "R");

    int maxRect = 0;
    for(int i = 0; i < (int) A.size(); i++) {
      if(maxRect < A[i] * (R[i] - L[i] - 1)) {
        iLog(1, "New max at %d = %d (%d * (%d - %d - 1))",
             i, A[i] * (R[i] - L[i] - 1), A[i], R[i], L[i]);
      }
      maxRect = std::max(maxRect, A[i] * (R[i] - L[i] - 1));
    }

    return maxRect;
  }
};

/*******************************************************************************
 *  namespace LongestSubarrayEqualLessThanK
 */
namespace LongestSubarrayEqualLessThanK {
  template <typename T>
  pair<T,T> calculate(vector<T> v, T k) {
    vector<T> prefixSum;
    partial_sum(v.cbegin(), v.cend(), back_inserter(prefixSum));
    printContainer(prefixSum, "prefixSum");

    vector<T> minPrefixSum(prefixSum);
    for(int i = (int) v.size()-2; i>= 0; i--) {
      minPrefixSum[i] = min(minPrefixSum[i], minPrefixSum[i+1]);
    }
    printContainer(minPrefixSum, "minPrefixSum");

    pair<T,T> idxes{0,
                    upper_bound(minPrefixSum.cbegin(),minPrefixSum.cend(),k)
                        - minPrefixSum.cbegin() + 1};
    /*
     *  @TODO finish this
     */
    for(int i = 0; i < (int) prefixSum.size(); i++) {
    }
    return idxes;
  }
};

/*******************************************************************************
 *  class FloydWarshallAllPairsShortestPaths
 */
namespace FloydWarshallAllPairsShortestPaths {
  vector<vector<int>> calculate(vector<vector<int>> &m) {
    /*
     */
    int maxInt = numeric_limits<int>::max();
    /*
     *  allocate matrix
     */
    vector<vector<int>> asp(m.size(), vector<int>(m.size(), maxInt));
    /*
     *  Set path to self to 0
     */
    for(int i = 0; i < (int) m.size(); i++) {
      asp[i][i] = 0;
    }
    /*
     *  Set weights
     */
    for(int i = 0; i < (int) m.size(); i++) {
      asp[m[i][0]][m[i][1]] = m[i][2];
    }
    printMatrix(asp, "initialized matrix");
    /*
     *  Calculate
     */
    for(int k = 0; k < (int) m.size(); k++) {
      for(int i = 0; i < (int) m.size(); i++) {
        for(int j = 0; j < (int) m.size(); j++) {
          if(!(asp[i][k] != maxInt && asp[k][j] != maxInt)) {
            continue;
          }
          iLog(0, "%d:%d:%d\t->\t%d + %d < %d ?", i, j, k,
               asp[i][k], asp[k][j], asp[i][j]);
          if(asp[i][k] + asp[k][j] < asp[i][j]) {
            asp[i][j] = asp[i][k] + asp[k][j];
          }
        }
      }
    }
    printMatrix(asp, "calculated matrix");
    return asp;
  }
};

#endif /* __METAS_H__ */
