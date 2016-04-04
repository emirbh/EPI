#include <iostream>
#include <iterator>

using std::cin;
using std::cout;
using std::endl;
using std::stringstream;
using std::ostream;

#include "idebug.h"
#include "arrays.h"
#include "primitive.h"
#include "tries.h"

int main() {
  int part;
  cin >> part;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  ArrayOps<unsigned long> ulao;
  StringOps so;

  while(part != -1) {
    cout << "Part: " << part << "----------------------------------------";
    cout << "--------------------------------" << endl;

    switch(part) {
      /* ---- 01 ------------------------------------------------------------ */
      case 1: {
        cout << "EPI: ";
        cout << "Dutch Flag" << endl;
        vector<unsigned long> v;
        readArray(v);
        printContainer(v);
        int pivot = 2;
        cin >> pivot;
        ulao.dutch_flag_partition(v, pivot);
        printContainer(v);
        break;
      }
      /* ---- 02 ------------------------------------------------------------ */
      case 2: {
        cout << "EPI: ";
        cout << "Lazy Init" << endl;
        LazyInitArray<bool,12> lazyInit;
        int n;
        cin >> n;
        for(int i = 0; i < n; i++) {
          int idx;
          cin >> idx;
          lazyInit.write(idx, true);
        }
        lazyInit.write(7, true);
        lazyInit.write(1, true);
        lazyInit.write(2, true);
        lazyInit.print();
        break;
      }
      /* ---- 03 ------------------------------------------------------------ */
      case 3: {
        cout << "EPI: ";
        cout << "Running Max" << endl;
        vector<unsigned long> hSteps;
        readArray(hSteps);
        unsigned long energy;
        cin >> energy;
        unsigned long maxHeight = ulao.getRunningMax(hSteps);
        cout << "Energy = " << energy << " vs Height = " << maxHeight << endl;
        break;
      }
      /* ---- 04 ------------------------------------------------------------ */
      case 4: {
        /*
         *  @TODO Understand this
         */
        cout << "EPI: ";
        cout << "Max K Pairs" << endl;
        vector<unsigned long> v;
        readArray(v);
        vector<unsigned long> kSum = ulao.getMaxKPairs(v, 3);
        printContainer(kSum);
        break;
      }
      /* ---- 05 ------------------------------------------------------------ */
      case 5: {
        /*
         *  @TODO Understand more
         */
        cout << "EPI: ";
        cout << "0 mod n Subset Sum" << endl;
        vector<int> v;
        readArray(v);
        printContainer(v, "input");
        int long n = 0;
        cin >> n;
        (void) n;
        ArrayOps<int> iao;
        vector<int> result = iao.findZeroModN(v);
        printContainer(result, "result");
        break;
      }
      /* ---- 13 ------------------------------------------------------------ */
      case 13: {
        cout << "EPI: ";
        cout << "Rotate array" << endl;
        vector<int> v;
        readArray(v);
        printContainer(v, "in");
        int places;
        cin >> places;
        ArrayOps<int> iao;
        iao.rotateArray(v, places);
        printContainer(v, "out");
        exit(0);
        break;
      }
      /* ---- 45 ------------------------------------------------------------ */
      case 45: {
        cout << "EPI: ";
        cout << "Subset Sum" << endl;

        vector<unsigned long> v;
        readArray(v);
        printContainer(v, "input");
        unsigned long n = v.size();
        unsigned long nsum;
        cin >> nsum;

        /*
         *  General subset sum using either
         *  (i) recursive/exponential approach
         *  (ii) DP/quadratic approach
         */
        bool hasSubset = ulao.subsetSumExponential(v, n, nsum);
        /*
        bool hasSubset = ulao.subsetSumDP(v, n, nsum);
         */
        printContainer(v);
        cout << "Has subset=" << nsum << " : " << hasSubset << endl;;
        break;
      }
      /* ---- 06 ------------------------------------------------------------ */
      case 6: {
        cout << "EPI: ";
        cout << "Longest Increasing Subarray" << endl;
        vector<unsigned long> v;
        readArray(v);
        printContainer(v);
        vector<unsigned long> result = ulao.getLongestIncreasingSubarray(v);
        printContainer(result);

        /*
         *  General subset sum using either
         *  (i) recursive/exponential approach
         *  (ii) DP/quadratic approach
        unsigned long nsum;
        cin >> nsum;
        bool hasSubset = ulao.subsetSumExponential(v, n, nsum);
        bool hasSubset = ulao.subsetSumDP(v, n, nsum);
        printContainer(v);
        cout << "Has subset=" << nsum << " : " << hasSubset << endl;;
         */
        break;
      }
      /* ---- 09 ------------------------------------------------------------ */
      case 9: {
        cout << "EPI:";
        cout << "Multiply strings" << endl;
        int nRuns;
        cin >> nRuns;
        for(int i = 0; i < nRuns; ++i) {
          string s1, s2;
          cin >> s1 >> s2;
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          BigInt<string> bi1(s1);
          BigInt<string> bi2(s2);
          auto bi3 = bi1 * bi2;
          bi3.print();
        }
        break;
      }
      /* ---- 14 ------------------------------------------------------------ */
      case 14: {
        cout << "EPI:";
        cout << "Print Matrix Spiral" << endl;
        vector<vector<unsigned long>> m;
        readMatrix(m);
        ulao.printSpiral(m);
        break;
      }
      /* ---- 15 ------------------------------------------------------------ */
      case 15: {
        cout << "EPI:";
        cout << "Print Matrix Spiral" << endl;
        vector<vector<unsigned long>> m;
        readMatrix(m);
        ulao.printSpiral(m);
        break;
      }
      /* ---- 16 ------------------------------------------------------------ */
      case 16: {
        cout << "EPI:";
        cout << "Flip Region" << endl;
        vector<vector<unsigned long>> m;
        readMatrix(m);
        for(int i = 0; i < (int) m.size(); ++i) {
          printContainer(m[i]);
        }
        int x, y;
        cin >> x >> y;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << x << ":" << y << endl;
        ulao.flipRegion(m, {x, y});
        /*
         */
        break;
      }
      /* ---- 17 ------------------------------------------------------------ */
      case 17: {
        /*
         *  @TODO EPI is talking about dividing into 4 sub-arrays. Understand!
         */
        cout << "EPI:";
        cout << "Rotate Matrix" << endl;
        vector<vector<unsigned long>> m;
        readMatrix(m);
        for(int i = 0; i < (int) m.size(); ++i) {
          printContainer(m[i]);
        }
        ulao.rotateMatrix(m);
        for(int i = 0; i < (int) m.size(); ++i) {
          printContainer(m[i]);
        }
        break;
      }

      /* ---- 19 ------------------------------------------------------------ */
      case 19: {
        cout << "EPI:";
        cout << "Rotate Words" << endl;
        vector<string> v;
        readArray(v);
        stringstream stream;
        copy(v.begin(), v.end(), std::ostream_iterator<string>(stream, " "));
        string str = stream.str();
        cout << str << endl;
        so.reverseWords(str);
        break;
      }

      /* ---- 20 ------------------------------------------------------------ */
      case 20: {
        cout << "EPI:";
        cout << "Substring Search" << endl;
        string text, pattern;
        cin >> text;
        cin >> pattern;
        cout << text << endl << pattern << endl;
        pair<int,int> pos{0, 0};
        bool found;

        pos = {0, 0};
        found = so.searchBruteForce(text, pattern, pos);
        cout << "BF: Pattern is found=" << found << endl;

        pos = {0, 0};
        found = so.searchKnuthMorrisPratt(text, pattern, pos);
        cout << "KMP: Pattern is found=" << found << endl;

        pos = {0, 0};
        found = so.searchBoyerMoore(text, pattern, pos);
        cout << "BM: Pattern is found=" << found << endl;
        break;
      }

      /* ---- 21 ------------------------------------------------------------ */
      case 21: {
        cout << "EPI:";
        cout << "Remove and replace charcters" << endl;
        string text, changeTo;
        char remove, changeFrom;
        cin >> text;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> remove >> changeFrom >>  changeTo;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << text << " ";
        cout << remove << " " << changeFrom << " " << changeTo << endl;
        so.removeAndReplace(text, remove, changeFrom, changeTo);
        break;
      }

      /* ---- 40 ------------------------------------------------------------ */
      case 40: {
        cout << "LeetCode: ";
        cout << "Range sum query 2D - slow update, O(1) query" << endl;
        int nRows, nCols;
        cin >> nRows >> nCols;
        RangeSum2D<int> arr(nRows, nCols);
        // iLog(0, "rows=%d cols=%d", nRows, nCols);
        for(int i = 0; i < nRows; i++) {
          for(int j = 0; j < nCols; j++) {
            int cell;
            cin >> cell;
            // iLog(0, "update [%d:%d]=%d", i, j, cell);
            if(!arr.update(i,j,cell)) {
              cout << "Cannot update " << i << ":" << j << "=" << cell << endl;
            }
          }
        }

        arr.print();
        int nTests;
        cin >> nTests;
        for(int i = 0; i < nTests; i++) {
          int xi, yi, xj, yj;
          cin >> xi >> yi >> xj >> yj;
          int sum = arr.getSum(xi, yi, xj, yj);
          cout << "[" << xi << ":" << yi << "]->";
          cout << "[" << xj << ":" << yj << "] = " << sum << endl;
        }
        break;
      }
      /* ---- 41 ------------------------------------------------------------ */
      case 41: {
        /*
         *  @TODO
         */
        cout << "LeetCode:";
        cout << "Palindrome Pairs" << endl;
        vector<string> v;
        readArray(v);
        printContainer(v);

        vector<pair<int, int>> palindromes;
        Trie<string, int> t(26);
        for(int i = 0; i < (int) v.size(); i++) {
          int idx;
          vector<int> trace;

          int found = t.getValueByKey(v[i], idx, trace);
          if(found == t.VALUE_FOUND && so.isPalindromePair(v[i],v[idx])) {
            iLog(1, "%d=%s is found %d (at %d)", i, v[i].c_str(), found, idx);
            palindromes.push_back({idx, i});
            if(v[i].size() == v[idx].size()) {
              palindromes.push_back({i, idx});
            }
          } else if(found == t.TRACE_FOUND) {
            iLog(1, "%d=%s is trace", i, v[i].c_str(), found, idx);
            printContainer(trace, "\ttrace");
            for(const int &j : trace) {
              if(so.isPalindromePair(v[i],v[j])) {
                palindromes.push_back({i, j});
              }
            }
          }

          string str = v[i];
          //t.add(v[i], i);

          std::reverse(str.begin(), str.end());
          t.add(str, i);
        }
        for_each(palindromes.begin(), palindromes.end(),
                 [](const pair<int,int> &p) -> void {
                   cout << p.first << ":" << p.second << endl;
                 });
        t.print();
        break;
      }
      /* ---- 42 ------------------------------------------------------------ */
      /*
       *  @MAYBE take a look
       */
      case 42: {
        cout << "EPI 6.1.2:";
        cout << "4 values array sort" << endl;
        vector<string> v;
        readArray(v);
        printContainer(v);
        /*
        nValuesSort(v);
         */
        break;
      }
    }

    cin >> part;
  }
}
