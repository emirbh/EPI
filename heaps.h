#ifndef __HEAPS_H__
#define __HEAPS_H__

#include <iostream>
#include <cmath>
#include <string>
#include <queue>

using std::cout;
using std::endl;
using std::stringstream;
using std::priority_queue;
using std::length_error;
using std::greater;
using std::less;
using std::pair;

#include "idebug.h"

/*******************************************************************************
 *  class Heap
 */
template<typename T>
class Heap {
 public:
  int size;
  int count;
  T* data;

  const int NO_PARENT = -1;
  const int NO_CHILD = -1;

  /**************************************************************************
   *  Constructor
   */
  Heap(int n) : size(n), count(0) {
    data = new T[size];
  }

  ~Heap() {
    delete [] data;
  }

  /**************************************************************************
   *  add()
   */
  bool add(T item) {
    iLog(0, "add %d", item);
    if(count == size) {
        return false;
    }
    data[count++] = item;
    bubbleUp( count-1);
    return true;
  }

  /**************************************************************************
   *  extractMin()
   */
  T extractMin() {
    T minEl = -1;

    if(this->count <= 0) { return -1; }

    minEl = data[0];
    iLog(1, "Extract %d -------------------------------------------", minEl);
    showTree("Before Extraction");
    data[0] = data[--count];
    showArray("Before BubbleDown");
    showTree("Before BubbleDown");
    bubbleDown(0);
    showArray("After BubbleDown");
    return minEl;
  }

  /**************************************************************************
   *  operator[]
   */
  T& operator [](int idx) {
    return this->data[idx];
  }

  /**************************************************************************
   *  showTree()
   */
  void showTree(string comment = "") {
    int level = 0;
    int pow2 = pow(2, level);
    int ii = 0;

    iLog(0, comment + ":\tTREE");
    while(ii < count) {
      for(int jj = 0; jj < pow2 && ii < count; jj++, ii++) {
        iLog(level+1, "Node %d", data[ii]);
      }
      level++;
      pow2 = pow(2, level);
    }
  }

  /**************************************************************************
   *  showArray()
   */
  void showArray(string comment = "") {
    stringstream items;
    iLog(0, comment + ":\tARRAY");
    for(int ii = 0; ii < count; ii++) {
      items << data[ii] << " ";
    }
    iLog(0, items.str());
  }

 private:
  /**************************************************************************
   *  bubbleUp()
   */
  void bubbleUp(int idx) {
    int parentIdx = NO_PARENT;
    if((parentIdx = getParent(idx)) == NO_PARENT) { return; }

    if(this->data[parentIdx] > this->data[idx]) {
      iLog(1, "Bubble up %d", data[idx]);
      swap(parentIdx, idx);
      bubbleUp(parentIdx);
    }
  }

  /**************************************************************************
   *  bubbleDown()
   */
  void bubbleDown(int idx) {
    int childIdx = getChild(idx, true);
    int minIdx = idx;

    for(int ii = 0;
        ii < 2 && childIdx != NO_CHILD && childIdx+ii < this->count;
        ii++) {
      if(data[childIdx+ii] < data[minIdx]) {
        minIdx = childIdx+ii;
      }
    }

    if(minIdx != idx) {
      iLog(1, "Bubble down %d", data[idx]);
      swap(idx, minIdx);
      bubbleDown(minIdx);
    }
  }

  /**************************************************************************
   *  swap()
   */
  void swap(int idx1, int idx2) {
    iLog(2, "Swap %d and %d",  data[idx1], data[idx2]);
    T v = this->data[idx1];
    this->data[idx1] = this->data[idx2];
    this->data[idx2] = v;
  }

  /**************************************************************************
   *  getParent()
   */
  int getParent(int idx) {
    if(idx == 0) { return NO_PARENT; }
    else { return idx/2; }
  }

  /**************************************************************************
   *  getChild()
   */
  int getChild(int idx, bool left) {
    /*
    if(left) { return idx*2; }
    else { return idx*2+1; }
    */
    int childIdx = NO_CHILD;

    if(left) { childIdx = idx*2+1; }
    else { childIdx = idx*2+2; }

    if( childIdx >= count) {
      childIdx = NO_CHILD;
      iLog(1, "Node %d [%d] : %s child is NONE",
           data[idx], idx, left ? "left" : "right");
    } else {
      iLog(1, "Node %d [%d] : %s child is %d [%d]",
           data[idx], idx, left ? "left" : "right", data[childIdx], childIdx);
    }

    return childIdx;
  }
};

/*******************************************************************************
 *  class HeapMerge
 */
template <typename T>
class HeapMerge {
 public:
  HeapMerge() {
  }

  /*****************************************************************************
   *  merge()
   */
  vector<T> merge(vector<vector<T>> &m) {
    vector<T> v;
    struct Min {
      T v;
      int idx;
      bool operator<(const Min &r) const {
        return v > r.v;
      };
    };
    priority_queue<Min, vector<Min>> h;
    vector<int> sourceIdx(m.size());

    for(const vector<T> &v : m) {
      printContainer(v);
    }
    /*
     *  Initialize heap
     */
    iLog(0, "Initialize heap");
    for(int i = 0; i < (int) m.size(); i++) {
      iLog(1, "Add {%d, %d}", m[i][0], i);
      h.push({m[i][0], i});
      sourceIdx[i] = 1;
    }
    /*
     *  Extract minimums and fill into return vector
     */
    iLog(0, "Extract mins and add to v");
    while(!h.empty()) {
      Min minv = h.top(); h.pop();
      iLog(1, "Got {%d, %d}", minv.v, minv.idx);
      v.emplace_back(minv.v);
      if(sourceIdx[minv.idx] < (int) m[minv.idx].size()) {
        h.push({m[minv.idx][sourceIdx[minv.idx]++], minv.idx});
      }
    }
    return v;
  }

  /********
   *  sortKIncreaseDecrease()
   */
  vector<T> sortKIncreaseDecrease(vector<T> &v) {
    vector<vector<T>> m;
    int startIdx = 0;
    bool increasing = true;
    for(size_t i = 1; i <= v.size(); i++) {
      if(i == v.size() ||
         (!increasing && v[i-1] <  v[i]) ||
         ( increasing && v[i-1] >= v[i]) ) {
        if(increasing) {
          m.emplace_back(v.cbegin() + startIdx, v.cbegin() + i);
        } else {
          m.emplace_back(v.crbegin() + v.size() - i,
                         v.crbegin() + v.size() - startIdx);
        }
        startIdx = i;
        increasing = !increasing;
      }
    }
    return merge(m);
  }

 protected:
};

/*******************************************************************************
 *  Class HStack
 */
template <typename T>
class HStack {
  struct OrderedValue {
    unsigned int order;
    T value;

    bool operator <(const OrderedValue &that) const {
      return order < that.order;
    }
  };
  unsigned int order;
  priority_queue<OrderedValue, vector<OrderedValue>> heap;

 public:
  HStack() : order(0) {}

  void push(T &value) {
    heap.emplace(OrderedValue{ order++, value });
  }

  T pop() {
    if (heap.empty()) {
      throw length_error("Stack empty.");
    }
    T value = heap.top().value;
    heap.pop();
    return value;
  }

  T & peek() {
    return heap.top();
  }
};

/*******************************************************************************
 *  class HeapRunningMedian
 */
template <typename T>
class HeapRunningMedian {
 private:
  priority_queue<T, vector<T>, greater<T>> higher;
  priority_queue<T, vector<T>, less<T>> lower;
 public:
  HeapRunningMedian() {
  }

  double add(const T &v) {
    if(!lower.empty() && v > lower.top()) {
      iLog(1, "Add %d to higher", v);
      higher.emplace(v);
    } else {
      iLog(1, "Add %d to lower", v);
      lower.emplace(v);
    }

    if(lower.empty()) {
      return higher.top();
    } else if(higher.empty()) {
      return lower.top();
    }

    if(lower.size() > higher.size() + 1) {
      higher.emplace(lower.top());
      lower.pop();
    } else if(higher.size() > lower.size() + 1) {
      lower.emplace(higher.top());
      higher.pop();
    }

    double median;
    if(lower.size() == higher.size()) {
      iLog(2, "Same sizes, (%d+%d)/2", lower.top(), higher.top());
      median = 0.5 * (double) (lower.top() + higher.top());
    } else {
      median = higher.size() > lower.size() ? higher.top() : lower.top();
    }

    return median;
  }
};

#endif /* __HEAPS_H__ */
