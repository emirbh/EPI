#ifndef __SEARCHES_H__
#define __SEARCHES_H__

#include <vector>
#include <algorithm>

using std::vector;
using std::pair;

#include "idebug.h"

/*******************************************************************************
 *  searchFirst()
 */
template <typename T>
int searchFirst(vector<T> &v, T k) {
  unsigned int m, l = 0, r = v.size()-1, result = -1;
  while (l <= r) {
    m = l + (r - l)/2;
    iLog(0, "v[%d]=%d ? v[%d]=%d ? v[%d]=%d", l, v[l], m, v[m], r, v[r] );
    if (v[m] > k) {
      r = m - 1;
      iLog(1, "v[%d] = %d", r, v[r]);
    } else if (v[m] == k) {
      result = m;
      r = m - 1;
      iLog(1, "v[%d] = %d", r, v[r]);
    } else { // if (v[m] < k)
      l = m + 1;
      iLog(1, "v[%d] = %d", l, v[l]);
    }
  }
  return result;
}

/*******************************************************************************
 *  searchFirstLarger()
 */
template <typename T>
int searchFirstLarger(vector<T> &v, T k) {
  unsigned int m, l = 0, r = v.size()-1, result = -1;
  while (l <= r) {
    m = l + (r - l)/2;
    iLog(0, "v[%d]=%d ? v[%d]=%d ? v[%d]=%d", l, v[l], m, v[m], r, v[r] );
    if (v[m] > k) {
      result = m;
      r = m - 1;
      iLog(1, "v[%d] = %d", r, v[r]);
    } else { // if (v[m] < k)
      l = m + 1;
      iLog(1, "v[%d] = %d", l, v[l]);
    }
  }
  return v[result];
}

/*******************************************************************************
 *  searchIn2D()
 */
template <typename T>
pair<int,int> searchIn2D(vector<vector<T>> vv, T &x) {
  int row = static_cast<int>(vv.size()-1),
      col = static_cast<int>(vv[row].size()-1);
  int m, l = 0, r = row;

  /*
   *  find row
   */
  while(l < r) {
    m = l + (r - l)/2;
    if(x <= vv[m][col]) {
      break;
    } else {
      l = m + 1;
    }
  }
  if(m > row)
    return {-1, -1};

  row = m;
  l = 0;
  r = col = static_cast<int>(vv[row].size()-1);

  /*
   *  find col
   */
  while(l < r) {
    m = l + (r - l)/2;

    if(x < vv[row][m]) {
      r = m - 1;
    } else if( x > vv[row][m]) {
      l = m + 1;
    } else {
      return {row, m};
    }
  }

  return {-1, -1};
}

#endif /* __SEARCHES_H__ */
