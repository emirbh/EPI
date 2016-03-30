#ifndef __ARRAYS_H__
#define __ARRAYS_H__

#include <vector>
#include <algorithm>
#include <queue>
#include <array>
#include <unordered_map>

using std::vector;
using std::pair;
using std::min;
using std::max;
using std::numeric_limits;
using std::swap;
using std::iota;
using std::ceil;
using std::floor;
using std::queue;
using std::array;
using std::unordered_map;

#include "idebug.h"

/******************************************************************************
 *  class ArayOps
 */
template <typename T>
class ArrayOps {
 public:
  void dutch_flag_partition(vector<T>& arr, const int& pivot_index) {
    T pivot_value = arr[pivot_index];
    int smaller = 0, equal = 0, larger = arr.size()-1;;

    /*
     *  index equal is used as curr (until larger is reached)
     */
    while (equal <= larger) {
      iLog(0, "%d/%d/%d -> %d:%d vs %d",
           smaller, equal, larger, equal, arr[equal], pivot_value);
      if(arr[equal] < pivot_value) {
          swap(arr[equal++], arr[smaller++]);
      } else if(arr[equal] == pivot_value) {
        equal++;
      } else { // if( arr[equal] > pivot_value)
        swap(arr[equal], arr[larger--]);
      }
    }
  }

  void nValuesSort(vector<T> v, vector<T> values) {
    unordered_map<T, int> offsets;

    for(int i = 0; i < (int) values.size(); i++) {
      offsets[values[i]] = 0;
    }

    for(int i = 0; i < (int) v.size(); i++) {
    }
  }

  pair<T,T> & calculateMaxProfit(vector<T> &v) {
    pair<T,T> maxDiff;
    T min = 0, diff = 0, diffMin = 0, diffMax = 0;

    for(const T &item : v) {
      if(diff < item-min) {
        diff = item-min;
        diffMin = min;
        diffMax = item;
      }
      min = min(min, item);
    }
    maxDiff[0] = diffMin;
    maxDiff[1] = diffMax;

    return maxDiff;
  }

  T getRunningMax(vector<T> &v) {
    T minValue = numeric_limits<T>::max(), maxDiff = 0;
    for(const T &i : v) {
      maxDiff = max(maxDiff, i - minValue);
      minValue = min(minValue, i);
    }
    return maxDiff;
  }

  vector<T> getMaxKPairs(vector<T> &v, const int &k) {
    vector<T> kSum(2*k, numeric_limits<T>::lowest());
    for(int i = 0; i < (int) v.size(); i++) {
      vector<T> preKSum(kSum);
      for(int j = 0, sign = -1;
          j < (int) kSum.size() && j < i;
          ++j, sign *= -1 ) {
        T diff = sign * v[i] + (j == 0 ? 0 : preKSum[j-1]);
        kSum[j] = max(diff, preKSum[j]);
      }
    }
    return kSum;
  }

  vector<T> findZeroModN(vector<T> &v) {
    vector<T> prefixSum(v);
    for(size_t i = 0; i < prefixSum.size(); ++i) {
      T prefixAdd = (i > 0) ? prefixSum[i-1] : 0;
      iLog(1, "prefixSum[%d] = %d + %d", i, prefixSum[i], prefixAdd);
      prefixSum[i] += (i > 0) ? prefixSum[i-1] : 0;
      iLog(2, "prefixSum[%d] = %d %% %d", i, prefixSum[i], v.size());
      prefixSum[i] %= v.size();
    }
    printContainer(prefixSum, "prefixSum");

    vector<T> table(v.size(), -1);
    for(size_t i = 0; i < v.size(); i++) {
      printContainer(table);
      if(prefixSum[i] == 0) {
        iLog(1, "prefixSum[%d] == 0", i);
        vector<T> ans(i+1);
        iota(ans.begin(), ans.end(), 0);
        return ans;
      } else if((int) table[prefixSum[i]] != -1) {
        vector<T> ans(i - table[prefixSum[i]]);
        iota(ans.begin(), ans.end(), table[prefixSum[i]] + 1);
        return ans;
      }
      table[prefixSum[i]] = i;
    }
    printContainer(table);
    return table;
  }

  vector<T> getLongestIncreasingSubarray(vector<T> &v) {
    vector<vector<T>> lis(v.size());
    int maxIdx = 0;
    for(size_t i = 0; i < v.size(); ++i) {
      for(size_t j = 0; j < i; ++j) {
        if(v[j] < v[i] &&
           lis[i].size() < lis[j].size()+1)
          lis[i] = lis[j];
      }
      lis[i].push_back(v[i]);

      if(lis[i].size() > lis[maxIdx].size()) {
        maxIdx = i;
      }
    }
    return lis[maxIdx];
  }


  /**
   *  Exponential, not good.
   */
  bool subsetSumExponential(vector<T> &v, size_t n, T sum) {
    if(sum == 0) {
      return true;
    }
    if(n == 0) {
      return false;
    }

    return subsetSumExponential(v, n - 1, sum) ||
           subsetSumExponential(v, n - 1, sum - v[n-1]);
  }

  bool subsetSumDP(vector<T> &v, size_t n, T sum) {
    bool subset[sum+1][n+1];

    for(size_t i = 0; i <= n; i++)
      subset[0][i] = true;
    for(size_t i = 1; i <= sum; i++)
      subset[i][0] = false;

    for(size_t i = 1; i <= sum; i++) {
      for(size_t j = 1; j <= n; j++) {
        // iLog(0, "[i=%d,j=%d]\t\t%d", i, j, subset[i][j-1]);
        subset[i][j] = subset[i][j-1];
        if(i >= v[j-1]) {
          subset[i][j] = subset[i][j] || subset[i - v[j-1]][j-1];
          // iLog(1, "[i=%d,j=%d]\t\t%d", i, j, subset[i][j]);
        }
      }
    }

    cout << "\t\t ";
    for(size_t i = 0; i < n; i++)
      cout << v[i] << "\t ";
    cout << endl;
    for(size_t i = 0; i <= sum; i++) {
      cout << i << "\t";
      for(size_t j = 0; j <= n; j++) {
        cout << subset[i][j] << "\t ";
      }
      cout << endl;
    }
    cout << endl;

    return subset[sum][n];
  }

  /*
   *  3 2 1
   *  2 1 2
   *  1 2 3
   *
   * 3 2 1 ; 2 3 ; 2 1 ; 2 ; 1
   */
  void printSpiral(vector<vector<T>> &m) {
    printOutter(m, 0);
  }

  void printOutter(vector<vector<T>> &m, int layer) {
    auto c = ceil(0.5 * m.size());
    cout << "Size: " << m.size() << " ";
    cout << " Ceil: " << c << " ";
    cout << "Layer: " << layer << endl;

    if(std::ceil(0.5 * m.size()) == layer)
      return;

    for(int i = layer; i < (int) m.size()-layer; ++i)
      cout << m[i][layer] << " ";
    for(int i = layer + 1; i < (int) m.size()-layer; ++i)
      cout << m[i][m.size()-layer-1] << " ";
    for(int i = layer+1; i < (int) m.size()-layer; ++i)
      cout << m[m.size()-layer-1][m.size()-1-i] << " ";
    for(int i = layer+1; i < (int) m.size()-layer-1; ++i)
      cout << m[m.size()-1-i][layer] << " ";
    cout << endl;

    printOutter(m, layer+1);
  }


  /*
   * 0 0 0 0 0     0 0 0 0 0
   * 1 1 0 0 0     0 0 0 0 0
   * 0 1 1 0 0 --> 0 0 0 0 0
   * 0 0 1 o 1     0 0 0 0 1
   * 0 0 0 0 1     0 0 0 0 1
   */
  void flipRegion(vector<vector<T>> &m, pair<int,int> coor) {
    const array<array<int, 2>, 4> direction = { -1, 0, 1, 0, 0, -1, 0, 1 };
    T flipValue = m[coor.first][coor.second];
    queue<pair<int, int>> q;
    q.push(coor);

    while(!q.empty()) {
      pair<int, int> pcoor = q.front();
      q.pop();

      if(m[pcoor.first][pcoor.second] != flipValue) {
        continue;
      } else {
        iLog(0, "Flip ar %d:%d", pcoor.first, pcoor.second);
        m[pcoor.first][pcoor.second] = !flipValue;
      }

      for(int i = 0; i < (int) direction.size(); ++i) {
        if(pcoor.first+direction[i][0] < 0 ||
           pcoor.first+direction[i][0] >= (int) m.size())
          continue;
        if(pcoor.second+direction[i][1] < 0 ||
           pcoor.second+direction[i][1] >= (int) m.size())
          continue;
        q.push({pcoor.first+direction[i][0], pcoor.second+direction[i][1]});
      }
    }
  }

  /*
   *  5 4 3 2 1    1 2 3 4 5
   *  4 3 2 1 2    2 1 2 3 4
   *  3 2 1 2 3 -> 3 2 1 2 3
   *  2 1 2 3 4    4 3 2 1 2
   *  1 2 3 4 5    5 4 3 2 1
   */
  void rotateMatrix(vector<vector<T>> &m) {
    int cycles = floor(0.5 * m.size());
    iLog(0, "Cycles = %d", cycles);
    for(int i = 0; i < cycles; ++i) {
      for(int j = i; j < (int) m.size()-i-1; ++j) {
        T temp = m[i][j];
        m[i][j]                       = m[m.size()-1-j][i];
        m[m.size()-1-j][i]            = m[m.size()-1-i][m.size()-1-j];
        m[m.size()-1-i][m.size()-1-j] = m[j][m.size()-1-i];
        m[j][m.size()-1-i]            = temp;
        /*
         */
      }
    }
  }
};




template <typename T, size_t N>
class LazyInitArray {
 private:
  /*
   *      0   1   2   3   4   5   6   7   8   9   10  11
   *  S   7   2   1   .   .   .   .   .   .   .   .   .
   *  P   .   2   1   .   .   .   .   0   .   .   .   .
   *  A   .   T   T   .   .   .   .   T   .   .   .   .
   */
  T A[N];
  int P[N]; // match A-index and store S-index
  size_t S[N]; // store indexes used
  int t;

  bool is_valid(const size_t &i) {
    return (0 <= P[i] && P[i] < t && S[P[i]] == i);
  }

 public:
  LazyInitArray() : t(0) {
  }

  bool read(const size_t &i, T &v) {
    if(is_valid(i)) {
      v = A[i];
      return true;
    }
    return false;
  }

  bool write(const size_t &i, const T &v) {
    if(!is_valid(i)) {
      S[t] = i;
      P[i] = t++;
      A[i] = v;
      return true;
    }
    return false;
  }

  void print() {
    cout << "S\t";
    for(size_t i = 0; i < N; i++) {
      if((int)i < t) {
        cout << S[i] << "\t";
      } else {
        cout << ".\t";
      }
    }
    cout << endl;
    cout << "P\t";
    for(size_t i = 0; i < N; i++) {
      if(is_valid(i)) {
        cout << P[i] << "\t";
      } else {
        cout << ".\t";
      }
    }
    cout << endl;
    cout << "A\t";
    for(size_t i = 0; i < N; i++) {
      if(is_valid(i)) {
        cout << A[i] << "\t";
      } else {
        cout << ".\t";
      }
    }
    cout << endl;
  }
};


/*******************************************************************************
 *  class RangeSum2D
 */
template <typename T>
class RangeSum2D {
 public:
  RangeSum2D(int nRows, int nCols)
      : nRows(nRows), nCols(nCols) {
    matrix.resize(nRows);
    for(int i = 0; i < nRows; i++) {
      matrix[i].resize(nCols, {0, 0});
      /*
      for(int j = 0; j < nCols; j++) {
        matrix[i][j] = {0, 0};
      }
      */
    }
  }

  bool update(int row, int col, T value) {
    if(row < 0 || row >= nRows || col < 0 || col >= nCols) {
      return false;
    }
    T diff = value - matrix[row][col].first;
    matrix[row][col].first += diff;
    for(int i = row; i < nRows; i++) {
      for(int j = col; j < nCols; j++) {
        matrix[i][j].second += diff;
      }
    }
    return true;
  }

  void print() {
    for(int i = 0; i < nRows; i++) {
      for(int j = 0; j < nCols; j++) {
        cout << matrix[i][j].first << ":" << matrix[i][j].second << "\t\t";
      }
      cout << endl;
    }
    cout << endl;
  }

  T getSum(int xi,int yi, int xj, int yj) {
    T sum;

    sum = matrix[xj][yj].second;
    if(yi>0)
      sum -= matrix[xj][yi-1].second;
    if(xi > 0)
      sum -= matrix[xi-1][yj].second;
    if(xi > 0 && yi > 0)
      sum += matrix[xi-1][yi-1].second;

    return sum;
  }

 private:
  /*
   *  Pair.first = cell value
   *  Pair.second = running sum
   */
  int nRows, nCols;
  vector<vector<pair<T,T>>> matrix;
};

/*******************************************************************************
 *  class NumMatrix
 */
class NumMatrix {
 public:
  NumMatrix(vector<vector<int>> &matrix) : matrix(matrix) {
  }

  void update(int row, int col, int val) {
    if(row < 0 || row >= (int) matrix.size()) {
      return;
    }
    int diff = val - matrix[row][col];
    for(int i = row; i < (int) matrix.size(); i++) {
      if(col < 0 || col >= (int) matrix[i].size()) {
        return;
      }
      for(int j = col; j < (int) matrix[i].size(); j++) {
        matrix[i][j] += diff;
      }
    }
  }

  int sumRegion(int row1, int col1, int row2, int col2) {
    int sum;

    sum = matrix[row2][col2];
    if(col1>0)
      sum -= matrix[row2][col1-1];
    if(row1 > 0)
      sum -= matrix[row1-1][col2];
    if(row1 > 0 && col1 > 0)
      sum += matrix[row1-1][col1-1];

    return sum;
  }
 private:
  vector<vector<int>> &matrix;
};

#endif /* __ARRAYS_H__ */
