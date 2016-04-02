#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdarg.h>
#include <string>
#include <iostream>
#include <sstream>
#include <limits>
#include <vector>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::streamsize;
using std::vector;

void iLog(int level, const string fmt, ...) {
#if !IDEBUG
    (void) level;
    (void) fmt;
#else
    int size = ((int) fmt.size()) * 2 + 50;
    string str;
    va_list ap;

    while(1) {
        str.resize(size);
        va_start(ap, fmt);
        int n = vsnprintf((char *) str.data(), size, fmt.c_str(), ap);
        va_end(ap);
        if(n > -1 && n < size) {
            str.resize(n);
            break;
        }
        if(n > -1)
            size = n + 1;
        else
            size *= 2;
    }

    for(int ii=0; ii<level; ii++) {
        cout << "\t";
    }
    cout << str << endl;
#endif /* IDEBUG */
}

template<typename T>
string itob(T number) {
  size_t size = sizeof(T)*8;
  char* chars = new char[size+1];

  for(int ii=size-1; ii>=0; ii--) {
    chars[ii] = (number & 1) ? '1' : '0';
    number >>= 1;
  }
  chars[size] = '\0';

  return string(chars);
}

template<typename T>
void printItem(T item) {
  cout << item << " ";
}

template <typename T>
void printContainer(const T &c, const string label = "") {
  if(label != "") {
    cout << label << ": \t";
  }
  for(const auto &i : c) {
    cout << i << " ";
  }
  /*
  for(auto it = c.begin(); it != c.end(); it++) {
    cout << *it++ << " ";
  }
   */
  cout << endl;
}

template <typename T>
void readArray(vector<T> &v) {
  int n;
  cin >> n;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  for(int i = 0; i < n; i++) {
    T item;
    cin >> item;
    v.emplace_back(item);
  }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

template <typename T>
void readMatrix(vector<vector<T>> &m) {
  int r, c;
  cin >> r >> c;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  m.resize(r);
  for(int i = 0; i < r; ++i) {
    m[i].resize(c);
    for(int j = 0; j < c; ++j) {
      T item;
      cin >> item;
      m[i][j] = item;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
}

template <typename T>
void printMatrix(vector<vector<T>> m, string label="") {
  if(label != "")
    cout << label << endl;
  for(size_t i = 0; i < m.size(); i++) {
    for(size_t j = 0; j < m[i].size(); j++) {
      cout << m[i][j] << "\t ";
    }
    cout << endl;
  }
}

#endif /* __DEBUG_H__ */
