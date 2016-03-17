#ifndef __STACKS_H__
#define __STACKS_H__

#include <iostream>
#include <stack>
#include <vector>
#include <memory>

using std::cout;
using std::stack;
using std::vector;
using std::pair;
using std::unique_ptr;
using std::length_error;

#include "idebug.h"

/*******************************************************************************
 * StackMax
 */
template <typename T>
class StackMax {
  stack<pair<T,T>> s;

 public:
  bool empty(void) const {
    return s.empty();
  }

  const T& max(void) const {
    if(empty() == false) {
      return s.top().second;
    }
    throw length_error("Empty stack");
  }

  T pop(void) {
    if(empty()) {
      throw length_error("Empty stack");
    }
    T ret = s.top().first;
    s.pop();
    return ret;
  }

  void push(const T &x) {
    s.emplace(x, std::max(x, empty() ? x : s.top().second));
  }
};

/*******************************************************************************
 * StackHanoi
 */
template <typename T>
class StackHanoi {
 public:
  StackHanoi(int nPegs, int nDisks)
      : nPegs(nPegs), nDisks(nDisks), currentPeg(0) {
    pegs = new stack<T>[nPegs];

    for(int i = nDisks; i > 0; i--) {
      pegs[0].push(i);
    }
    cout << endl;
  }

  void transfer(int toPeg) {
    transfer(nDisks, pegs, currentPeg, toPeg, 2, 0, "init");
  }

 private:
  stack<T> *pegs;
  int nPegs, nDisks;
  int currentPeg;

  void transfer(const int n, stack<T> *pegs,
                const int from, const int to, const int use,
                int level, string order) {
    if(n > 0) {
      transfer(n-1, pegs, from, use, to, level+1, "pre ");
      int value = pegs[from].top();
      pegs[to].push(value);
      pegs[from].pop();
      /*
      ++n_steps;
      iLog(level, "%.2d. Move %d from peg %d to peg %d",
           n_steps, value, from, to);
       */
      iLog(level, "%s\tMove %d from peg %d to peg %d",
           order.c_str(),  value, from, to);
      transfer(n-1, pegs, use, to, from, level+1, "post");
    }
  }
};

/*******************************************************************************
 * StackSunset
 */
template <typename T>
class StackSunset {
 public:
  struct Building {
    int idx;
    T height;
  };

  StackSunset(vector<T> &v) : v(v) {
  }

  stack<Building> getSunsetView() {
    stack<Building> s;
    int idx = 0;

    for(const T &height : v) {
      while(!s.empty() && height > s.top().height) {
        s.pop();
      }
      s.push({idx++, height});
    }
    return s;
  }

 private:
  vector<T> &v;
};

/*******************************************************************************
 * StackSort
 */
template <typename T>
class StackSort {
 public:
  struct Building {
    int idx;
    T height;
  };

  StackSort(vector<T> &v) : v(v) {
  }

  stack<T> sort() {
    stack<T> s;

    for(T &i : v) {
      iLog(0, "insert %d", i);
      insertSorted(s, i, 1);
    }
    return s;
  }

 private:
  vector<T> &v;

  void insertSorted(stack<T> &s, T &v, int level) {
    if(s.empty()) {
      iLog(level, "push %d to top", v);
      s.push(v);
    } else if(s.top() <= v) {
      iLog(level, "add largest to top %d", v);
      s.push(v);
    } else {
      T p = s.top(); s.pop();
      iLog(level, "popped %d", p);
      insertSorted(s, v, level+1);
      iLog(level, "push %d", p);
      s.push(p);
    }
  }
};


#endif /* __STACKS_H__ */
