#ifndef __SEARCHES_H__
#define __SEARCHES_H__

#include <vector>
#include <algorithm>

using std::vector;
using std::pair;
using std::lower_bound;
using std::min;
using std::max;

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

/*******************************************************************************
 *
 *  findMinInCycle()
 */
template <typename T>
T findMinInCycle(vector<T> &v) {
  int l = 0, r = (int) v.size() - 1, m;
  while(r > l) {
    m = l + (r - l) / 2;
    iLog(0, "v[%d]=%d ? v[%d]=%d ? v[%d]=%d", l, v[l], m, v[m], r, v[r] );
    if(v[m] > v[r]) {
      l = m + 1;
    } else {
      r = m;
    }
  }
  return m;
}

/*******************************************************************************
 *
 *  findMinInCycle()
 */
template <typename T>
T computeCompletionSearch(vector<T> &v, T sum) {
  T sigma = 0;
  sort(v.begin(), v.end());
  printContainer(v, "in sorted");
  vector<T> prefixSum;
  partial_sum(v.cbegin(), v.cend(), std::back_inserter(prefixSum));
  printContainer(prefixSum, "prefixSum");
  vector<double> funcSigma(prefixSum.size());
  for(int i = 0; i < (int) prefixSum.size(); i++) {
    funcSigma[i] = (v.size() - 1 - i) * v[i] + prefixSum[i];
  }
  printContainer(funcSigma, "funcSigma");
  auto lower = lower_bound(funcSigma.cbegin(), funcSigma.cend(), sum);
  if(lower == funcSigma.cend()) {
    return -1;
  } else if(lower == funcSigma.cbegin()) {
    return sum/v.size();
  }
  int idx = lower - funcSigma.cbegin() - 1;
  sigma = (sum - prefixSum[idx]) / (v.size() - 1 - idx);;
  return sigma;
} 

/*******************************************************************************
 *
 *  findKthInTwoArrays()
 */
template <typename T>
T findKthInTwoArrays(vector<T> A, vector<T> B, int k) {
  /*
   *  In first k elements, we will have x items from a and k-x items from b
   */
  int b = max(0, static_cast<int>(k - B.size()));
  // Upper bound of elements we will choose in A.
  int t = min(static_cast<int>(A.size()), k);

  iLog(0, "b=%d t=%d", b, t);

  while (b < t) {
    int x = b + ((t - b) / 2);
    iLog(0, "x=%d", x);
    int A_x_1 = (x <= 0 ? numeric_limits<int>::min() : A[x - 1]);
    int A_x = (x >= A.size() ? numeric_limits<int>::max() : A[x]);
    int B_k_x_1 = (k - x <= 0 ? numeric_limits<int>::min() : B[k - x - 1]);
    int B_k_x = (k - x >= B.size() ? numeric_limits<int>::max() : B[k - x]);
    iLog(1, "A_x_1   = %d", A_x_1);
    iLog(1, "A_x     = %d", A_x);
    iLog(1, "B_k_x_1 = %d", B_k_x_1);
    iLog(1, "B_k_x   = %d", B_k_x);

    if (A_x < B_k_x_1) {
      b = x + 1;
    } else if (A_x_1 > B_k_x) {
      t = x - 1;
    } else {
      // B[k - x - 1] <= A[x] && A[x - 1] < B[k - x].
      iLog(2, "return max(%d,%d)", A_x_1, B_k_x_1);
      return max(A_x_1, B_k_x_1);
    }
    iLog(0, "b=%d t=%d", b, t);
  }

  int A_b_1 = b <= 0 ? numeric_limits<int>::min() : A[b - 1];
  int B_k_b_1 = k - b - 1 < 0 ? numeric_limits<int>::min() : B[k - b - 1];
  return max(A_b_1, B_k_b_1);
}

#endif /* __SEARCHES_H__ */
