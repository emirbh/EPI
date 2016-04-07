#ifndef __INTRACTABILITY_H__
#define __INTRACTABILITY_H__

#include <vector>
#include <numeric>
#include <stack>
#include <list>
#include <unordered_set>

using std::vector;
using std::accumulate;
using std::max;
using std::stack;
using std::list;
using std::unordered_set;
using std::pair;

#include "idebug.h"

/*******************************************************************************
 *  class ElectionTie
 */
class ElectionTie {
 public:
  ElectionTie(vector<int> &v) : v(v) {
    findTieHelper();
  }

 protected:
  vector<int> & v;
  vector<vector<int>> subsets;

  void findTieHelper() {
    int totalVotes = accumulate(v.cbegin(), v.cend(), 0);
    if(totalVotes % 2) {
      return;
    }
    totalVotes >>= 1;
    iLog(0, "Total Votes %d", totalVotes);
    /*
     * DP: set up Rows=(sum+1) * Cols=(n+1) matrix
     * already done in arrays.h:subsetSumDP()
     */
    vector<vector<bool>> table(totalVotes+1, vector<bool>(v.size()+1, false));
    table[0].assign(v.size()+1, true);
    for(int i = 1; i <= (int) table.size(); i++) {
      for(int j = 1; j <= (int) table[i].size(); j++) {
        table[i][j] = table[i][j-1];
        if(i >= v[j-1])
          table[i][j] = table[i][j] || table[i-v[j-1]][j-1];
      }
    }
    cout << "\t";
    for(size_t j = 0; j < v.size(); j++) { cout << v[j] << "\t "; }
    cout << endl;
    printMatrix(table);

    /*
     *  find all subsets
     */
    int count = 0;
    for(int k = 1; k <= (int) v.size(); k++) {
      int sum = totalVotes;
      if(!table[sum][k]) continue;

      subsets.emplace_back(vector<int>{});
      int j = k-1, level = 0;
      while(sum > 0 && j >= 0) {
        subsets[count].emplace_back(v[j]);
        iLog(level, "v[%d] = %d", j, v[j]);
        sum -= v[j];
        j--;
        iLog(level++, "sum=%d j=%d", sum, j);
      }
    }
  }
};

/*******************************************************************************
 *  class Knapsack
 */
class Knapsack {
 public:
  Knapsack(vector<vector<int>> &m) : m(m) {
  }

  void pack(int weight) {
    packHelper(weight);
  }
 protected:
  vector<vector<int>> &m;

  void packHelper(int weight) {
    printMatrix(m, "value/weight");
    cout << endl;

    /*
     * DP: set up Rows=(weight+1) * Cols=(n+1) matrix
     */
    vector<vector<int>> table(weight+1, vector<int>(m.size()+1, 0));
    for(int i = 0; i <= (int) weight; i++) {
      for(int j = 0; j <= (int) m.size(); j++) {
        if(i == 0 || j == 0) {
          table[i][j] = 0;
        } else if(m[j-1][1] <= i) {
          /*
           *  value = m[j-1][0]
           *  weight = m[j-1][1]
           */
          table[i][j] = max(m[j-1][0] + table[i-m[j-1][1]][j-1],
                            table[i][j-1]);
        /*
        */
        } else {
          table[i][j] = table[i][j-1];
        }
      }
    }

    /*
    cout << "\t";
    for(size_t j = 0; j < m[0].size(); j++) { cout << m[j][0] << "\t "; }
    cout << endl;
    cout << "\t";
    for(size_t j = 0; j < m[1].size(); j++) { cout << m[j][1] << "\t "; }
    cout << endl;
     */
    printMatrix(table);
  }
};

/*******************************************************************************
 *  class ExpressionSynthesis
 */
class ExpressionSynthesis {
 public:
  ExpressionSynthesis(vector<int> &v, int &value)
      : v(v), value(value) {
  }

  bool evaluate() {
    vector<char> operators;
    vector<int> operands;
    return evaluateHelper(v, value, operands, operators, 0, 0);
  }

 protected:
  vector<int> &v;
  int value;

  /********
   *  evaluateHelper()
   */
  bool evaluateHelper(vector<int> v, int value,
                      vector<int> &operands, vector<char> &operators,
                      int cur, const int offset, int l=0) {
    for(int i=0; i<l; i++) cout <<  "\t"; printContainer(operands, "operands");
    for(int i=0; i<l; i++) cout <<  "\t"; printContainer(operators, "operators");

    cur = cur*10 + v[offset];
    if(offset == (int) v.size()-1) {
      iLog(l, "1. evaluateHelper(ofset=%d) cur=%d", offset, cur);
      operands.emplace_back(cur);
      if(evaluateSequence(operands, operators, l+1) == value) {
        auto operandIt = operands.begin();
        cout << "Expression: " << *operandIt++;
        for(const char chOperator : operators) {
          cout << ' ' << chOperator << ' ' << *operandIt++;
        }
        cout << " = " << value << endl;
        return true;
      }
      operands.pop_back();
      return false;
    }

    /*
     * invoke evaluateSequence for following
     *  (i) ++offset
     *  (ii) add operand, *, ++offset
     *  (iii) add operand, ++offset
     */
    iLog(l, "2. evaluateHelper(ofset=%d) cur=%d", offset, cur);
    if(evaluateHelper(v, value, operands, operators, cur, offset+1,l+1)) {
      return true;
    }

    iLog(l, "3. evaluateHelper(ofset=%d) cur=%d", offset, cur);
    operands.emplace_back(cur), operators.emplace_back('*');
    if(evaluateHelper(v, value, operands, operators, 0, offset+1,l+1)) {
      return true;
    }
    operands.pop_back(), operators.pop_back();

    operands.emplace_back(cur);
    if(value - evaluateSequence(operands, operators, l+1) <=
         remainingInt(v, offset + 1)) {
      iLog(l, "4. evaluateHelper(ofset=%d) cur=%d", offset, cur);
      operators.emplace_back('+');
      if(evaluateHelper(v, value, operands, operators, 0, offset+1,l+1)) {
        return true;
      }
      operators.pop_back();
    }
    operands.pop_back();
    return false;
  }

  /********
   *  evaluate()
   */
  int evaluateSequence(vector<int> operands, vector<char> operators, int l=0) {
    for(int i=0; i<l; i++)
      cout <<  "\t"; printContainer(operands, "CALCULATE operands");
    for(int i=0; i<l; i++)
      cout <<  "\t"; printContainer(operators, "CALCULATE operators");

    /*
     *  Evaluate '*' first
     */
    int operandIdx = 0;
    stack<int> tempOperands;
    tempOperands.push(operands[operandIdx++]);
    for(const char &chOperator : operators) {
      if(chOperator == '*') {
        int product = tempOperands.top() * operands[operandIdx++];
        tempOperands.pop();
        tempOperands.push(product);
      } else {
        tempOperands.push(operands[operandIdx++]);
      }
    }

    /*
     *  Sum up operands
     */
    int sum = 0;
    while(!tempOperands.empty()) {
      sum += tempOperands.top();
      tempOperands.pop();
    }

    iLog(l, "Return sum=%d", sum);
    return sum;
  }

  /********
   *
   */
  int remainingInt(const vector<int>& digits, int idx) {
    int val = 0;
    for (int i = idx; i < (int) digits.size(); ++i) {
      val = val * 10 + digits[i];
    }
    return val;
  }

};

/*******************************************************************************
 *  class MultiplicationMinimum
 */
class MultiplicationMinimum {
 public:
  MultiplicationMinimum(int exp) {
   list<int> l = getMultMinHelper(exp);
   printContainer(l);
  }

 protected:
  list<int> getMultMinHelper(int n) {
    list<int> init_list;
    init_list.emplace_back(1) ;

    list<list<int>> exp_lists;
    exp_lists.emplace_back(init_list);
    list<int> min_exp;
    int shortest_size = numeric_limits<int>::max() ;

    while (exp_lists.empty () == false) {
      list<int> exp = exp_lists .  front () ;
      exp_lists .  pop_front () ;
      for (const int &i : exp) {
        for (const int &j : exp) {
          int sum = i + j ;
          if (shortest_size > (int) exp.size() + 1) {
            if (sum == n) {
              min_exp = exp;
              min_exp.emplace_back(sum) ;
              shortest_size = exp.size() + 1;
            } else if (sum < n && sum > exp.back()) {
              list<int> ext = exp;
              ext .  emplace_back(sum) ;
              exp_lists.emplace_back(ext) ;
            }
          }
        }
      }
    }
    return min_exp;
  }
};

/*******************************************************************************
 *  class MostEvenSplit
 */
template <typename T>
class MostEvenSplit {
 public:
  static pair<T,T> calculate(vector<T> &v) {
    int sum = accumulate(v.cbegin(), v.cend(), 0);
    unordered_set<T> isOk;
    for(const T &item : v) {
      for(int i = sum/2; i >= item; i--) {
        iLog(0, "Item %d\tCheck %d", item, i);
        if(isOk.find(i - item) == isOk.end()) {
          iLog(1, "Add %d to isOk", i);
          isOk.emplace(i);
        }
      } 
    }
    for(int i = sum/2; i > 0; i--) {
      iLog(0, "Check if %d exists", i);
      if(isOk.find(i) != isOk.end()) {
        return pair<T,T>{sum - i,i};
      }
    }
    return pair<T,T>{sum,0};
  }
 protected:
};

#endif /* __INTRACTABILITY_H__ */
