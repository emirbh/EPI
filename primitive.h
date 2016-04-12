#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include <iostream>
#include <algorithm>
#include <string>
#include <array>
#include <unordered_map>
#include <cmath>

using std::cout;
using std::endl;
using std::string;
using std::min;
using std::max;
using std::pair;
using std::array;
using std::unordered_map;
using std::log2;

#include "idebug.h"

template <typename T>
class PrimitiveOps {
 public:
  PrimitiveOps() {}

  static short parity(T &x) {
    short result = 0;
    iLog(0, "x=%d, [%s] result=%d", x, itob(x).c_str(), result);
    while (x) {
      iLog(1, "\tPRE: x=%s, x&1=%d, result=%d", itob(x).c_str(), x&1, result);

      result ^= 1;
      x &= (x - 1);

      iLog(2, "\tPOST: x=%s, x&1=%d, result=%d", itob(x).c_str(), x&1, result);
    }
    iLog(0, "Parity = %d", result);
    return result;
  }

  T swapBits(T number, const int& i, const int& j) {
    iLog(0, "Compare bits %d:%d and %d:%d",
          i, (number >> i) & 1, j, (number >> j) & 1);
    if (((number >> i) & 1) != ((number >> j) & 1)) {
      iLog(0, "Different bits %d:%d and %d:%d",
            i, (number >> i) & 1, j, (number >> j) & 1);
      T bits = (((T) 1) << i) | (((T) 1) << j);
      iLog(0, "Bits are %d [%s]", bits, itob(bits).c_str());
      number ^= bits;
    }
    return number;
  }

  T reverseBits(T nr) {
    size_t size = sizeof(T) * 8;
    for(unsigned int ii=0; ii<size/2; ii++) {
      nr = swapBits(nr, ii, size-ii-1);
    }
    return nr;
  }

  T closestLarger(T x) {
    for(int i = 1; i < 63; ++i) {
      if(((x >> i) & 1) ^ ((x >> (i + 1)) & 1)) {
        iLog(0, "bits %d and %d are different.", i, i+1);
        x ^= ((1UL << i) | (1UL << (i + 1)));
        return x;
      }
    }
    return x;
  }

  vector<vector<T>> generatePowerSet(vector<T> &v) {
    vector<vector<T>> powerSet;
    for(int i = 0; i < (int) v.size(); i++) {
      vector<T> subSet;
      T bitset = v[i];
      iLog(0, "Bitset %d [%s]", bitset, itob(bitset).c_str());
      while(bitset) {
        subSet.emplace_back(log2(bitset & ~(bitset - 1)));
        bitset &= (bitset - 1);
      }
      powerSet.emplace_back(subSet);
    }
    return powerSet;
  }

  string intToString(int i) {
    bool is_negative = false;
    if (i < 0) {
      is_negative = true;
      i = -i;
    }

    string s;
    while (i > 0) {
      s.push_back('0' + i % 10);
      i /= 10;
    }
    if (s.empty()) {
      return {"0"};
    }
    if (is_negative) {
      s.push_back('-');
    }
    reverse(s.begin(), s.end());
    return s;
  }

  int stringToInt(string s) {
    int i = 0;
    bool is_negative = s[0] == '-';
    for (size_t cntr = is_negative ? 1 : 0; cntr<s.size(); cntr++) {
      if( !isdigit(s[cntr])) {
        throw std::invalid_argument("Invalid input: non-digit string");
      }
      i = i*10 + (s[cntr] - '0');
    }
    return is_negative ? -i : i;
  }

  string convert_base(const string& strValue, const int& base1,
                      const int& base2) {
    bool is_negative = strValue.front() == '-';
    int iValue = 0;
    for(int ii = is_negative ? 1 : 0; ii<(int)strValue.size(); ii++) {
      iValue *= base1;
      iValue += isdigit(strValue[ii]) ?
        strValue[ii] - '0' : strValue[ii] - 'A' + 10;
    }

    string result;
    while (iValue > 0) {
      int remainder = iValue % base2;
      result.push_back(
          remainder >=  10 ? 'A' + remainder - 10 : '0' + remainder);
      iValue /= base2;
    }
    if(result.size() <= 0) {
      return {"0"};
    }
    if(is_negative) {
      result.push_back('-');
    }
    std::reverse(result.begin(), result.end());
    return result;
  }

  T convertExcelColumnID(string col) {
    int res = 0;
    for(const char & c : col) {
      res = res * 10 + (c - 'A' + 1);
    }
    return res;
  }

  T gcd( T t1, T t2 ) {
    iLog(0, "GCD for %d:%d", t1, t2);
    if(t1 == 0) {
      return t2;
    } else if(t2 == 0) {
      return t1;
    } else if((t1 % 2) && !(t2 % 2)) {
      return gcd(t1, t2 >> 1);
    } else if(!(t1 % 2) && (t2 %2)) {
      return gcd(t1 >> 1, t2);
    } else if(t1 > t2) {
      return gcd(t1 - t2, t2);
    } else {
      return gcd(t1, t2 - t1);
    }
  }

  struct Rectangle {
    T x, y, width, height;
  };

  bool is_intersect( Rectangle &r1, Rectangle &r2) {
    /*
     *  ______
     *  |    |
     *  |  __|__
     *  |  | | |
     *  ---|-- |
     *     |   |
     *     -----
     *
     */
    return r1.x <= r2.x + r2.width  && r1.x + r1.width  >= r2.x &&
           r1.y <= r2.y + r2.height && r2.y + r1.height >= r2.y;
  }

  Rectangle intersection_rectangle(Rectangle &r1, Rectangle &r2) {
    if(is_intersect(r1, r2)) {
      return {
        max(r1.x, r2.x),
        max(r1.y, r2.y),
        min(r1.x + r1.width, r2.x + r2.width) - max(r1.x, r2.x),
        min(r1.y + r1.height, r2.y + r2.height) - max(r1.y, r2.y)
        };
    } else {
      return {0, 0, 0, 0};
    }
  }

  unsigned multiply(unsigned x, unsigned y) {
    unsigned sum = 0;
    while (x) {
      // Examines each bit of x.
      if (x & 1) {
        sum = add(sum, y);
      }
      x >>= 1, y <<= 1;
    }
    return sum;
  }

  static unsigned add(unsigned a, unsigned b) {
    unsigned sum = 0, carryin = 0, k = 1, temp_a = a, temp_b = b;
    while (temp_a || temp_b) {
      iLog(0, "sum = %d, carryin = %d, k = %d, temp_a = %d, temp_b = %d",
           sum, carryin, k, temp_a, temp_b);
      unsigned ak = a & k, bk = b & k;
      unsigned carryout = (ak & bk) | (ak & carryin) | (bk & carryin);
      iLog(1, "ak = %d carryout = %d", ak, carryout);
      sum |= (ak ^ bk ^ carryin);
      carryin = carryout << 1, k <<= 1, temp_a >>= 1, temp_b >>= 1;
    }
    return sum | carryin;
  }
  
  T divide(T x, T y, int level = 0) {
    iLog(level, "%d / %d", x, y);
    if(x < y) {
      return 0;
    }

    int power = 0;
    while((1 << power) * y <= x) {
      power++;
    }
    T part = 1 << (power - 1);

    iLog(level, "power=%d part=%d part*y = %d", power, part, part*y);

    return part + divide(x - part * y, y, level + 1);
  }
};

/******************************************************************************* *  class BigInt
 */
template <typename T>
class BigInt {
 public:
  BigInt(int length) : sign(1), digits(length, 0) {
  }

  BigInt(T &d) : digits(d) {
  }

  /*
   *    this * that
   *       j * i
   *      12 * 13
   *   -----
   *      36
   *     12
   *   -----
   *     156
   */
  BigInt operator*(const BigInt & n) const {
    BigInt result(digits.size() + n.digits.size());
    int carry = 0;
    printContainer(digits);
    printContainer(n.digits);
    for(int j = (int) digits.size()-1; j >= 0; --j) {
      for(int i = (int) n.digits.size()-1; i >= 0; --i) {
        int inti = digits[i] - 48, intj = n.digits[j] - 48;
        int mult = carry + inti * intj;
        iLog(i+j, "%d + (%d = %d + %d * %d)",
             result.digits[i+j], mult, carry, inti, intj);
        result.digits[i+j] += mult % 10;
        carry /= 10;

        if(result.digits[i+j] < 48)
          result.digits[i+j] += 48;
      }
    }
    result.sign = sign * n.sign;
    return result;
  }

  void print() {
    if(sign == -1)
      cout << "-";
    printContainer(digits);
  }

 private:
  int sign;
  T digits;
};

/*******************************************************************************
 *  class StringOps
 */
class StringOps {
 public:
  /*****************************************************************************
   * searchBruteForce()
   */
  bool searchBruteForce(string text, string pattern, pair<int,int> &pos) {
    /*
     *  pos.first   position of pattern in string (-1 if none)
     *  pos.second  current text position
     */
    bool found = false;
    int i, j, ts = text.size(), ps = pattern.size();
    for(i = pos.second, j = 0; !found && i < ts-ps && j < ps; ++i) {
      if(text[i] == pattern[j]) {
        j++;
      } else if(j > 0) {
        i -= j;
        j = 0;
      }
    }
    if(j == ps) {
      pos.first = i-j;
      pos.second = i;
      found = true;
    }
    return found;
  }

  /*****************************************************************************
   * searchKuthMorrisPratt()
   */
  bool searchKnuthMorrisPratt(string text, string pattern, pair<int,int> &pos) {
    bool found = false;
    int i, j, ts = text.size(), ps = pattern.size();

#ifdef PRODUCTION
    /*
     *  build dfa
     */
    vector<vector<int>> dfa(RADIX, vector<int>(ps));
    dfa[pattern[0]-'a'][0] = 1;
    for(int X = 0, j = 1; j < ps; ++j) {
      for(int c = 0; c < RADIX; ++c) {
        dfa[c][j] = dfa[c][X];
      }
      dfa[pattern[j] - 'a'][j] = j + 1;
      X = dfa[pattern[j] - 'a'][X];
    }

    for(int i = 0; i < (int) dfa.size(); ++i) {
      printContainer(dfa[i]);
    }

    /*
     *  run search
     */
    for(i = pos.second, j = 0; i < ts && j < ps; ++i) {
      j = dfa[text[i] - 'a'][j];
    }
    if(j == ps) {
      pos.first = i-j;
      pos.second = i;
      found = true;
    }

#else
    /*
     *  for learning purposes, I am going to limits of rows
     *  in dfa only to characters that actualy exists and will than index
     *  thm for easier access
     */

    /*
     *  build dfa
     */
    unordered_map<char,int> mapCharToRow;
    int rowCount = 0;
    for(int i = 0; i < ps; ++i) {
      if(mapCharToRow.find(pattern[i]) == mapCharToRow.end()) {
        iLog(0, "map %c = row %d", pattern[i], rowCount);
        mapCharToRow[pattern[i]] = rowCount++;
      }
    }

    vector<vector<int>> dfa(rowCount, vector<int>(ps));
    dfa[mapCharToRow[pattern[0]]][0] = 1;
    for(int X = 0, j = 1; j < ps; ++j) {
      for(int c = 0; c < rowCount; ++c) {
        dfa[c][j] = dfa[c][X];
        iLog(0, "dfa[%d][%d] = dfa[%d][%d] = %d", c, j, c, X, dfa[c][X]);
      }
      iLog(1, "dfa[%d][%d] = %d", mapCharToRow[pattern[j]], j, j + 1);
      dfa[mapCharToRow[pattern[j]]][j] = j + 1;
      iLog(1, "X = dfa[%d][%d] = %d",
           mapCharToRow[pattern[j]], X, dfa[mapCharToRow[pattern[j]]][X]);
      X = dfa[mapCharToRow[pattern[j]]][X];
    }

    for(int i = 0; i < rowCount; ++i) {
      printContainer(dfa[i]);
    }

    for(i = pos.second, j = 0; i < ts && j < ps; ++i) {
      j = dfa[mapCharToRow[text[i]]][j];
    }
    if(j == ps) {
      pos.first = i-j;
      pos.second = i;
      found = true;
    }
#endif
    return found;
  }

  /*****************************************************************************
   * searchMoyerMoore()
   */
  bool searchBoyerMoore(string text, string pattern, pair<int,int> &pos) {
    bool found = false;
    int i, j, ts = text.size(), ps = pattern.size();

    /*
     *  Build skip table
     */
    vector<int> right(RADIX, -1);
    for(j = 0; j < ps; j++) {
      right[pattern[j] - 'a'] = j;
    }
    printContainer(right);

    /*
     *  Run search
     */
    int skip = 0;
    for(i = pos.second; i < ts; i += skip) {
      skip = 0;
      for(j = ps-1; j >= 0; --j) {
        if(pattern[j] != text[i+j]) {
          skip = max(1, j - right[pattern[j] - 'a']);
          break;
        }
      }
      if(skip == 0) {
        pos.first = i;
        pos.second = i+j;
        found = true;
        break;
      }
    }
    return found;
  }

  /*****************************************************************************
   * searchRabinKarp()  @TODO
   */
  bool searchRabinKarp(string text, string pattern, pair<int,int> &pos) {
    (void) text;
    (void) pattern;
    (void) pos;
    return false;
  }

  /*****************************************************************************
   * isPalindromePair()
   */
  bool hasPalindrome(string s) {
    int i = 0, j = s.size()-1;
    while(i < j && s[i] != s[j])
      j--;
    while(i < j && s[i] == s[j]) {
      i++, j--;
    }
    iLog(0, "Check %s for palindrome = %d", s.c_str(), i >= j);
    return i >= j;
  }

  /*****************************************************************************
   * isPalindromePair()
   */
  bool isPalindromePair(string s1, string s2) {
    return hasPalindrome(s1+s2) || hasPalindrome(s2+s1);;
  }

  /*****************************************************************************
   * reverseWords()
   */
  void reverseWords(string &text) {
    /*
    int i = 0, last = text.size()-1;
    while(i < last) {
      char temp = text[i];
      text[i] = text[last-i];
      text[last-i] = temp;
      ++i, --last;
    }
     */
    reverse(text.begin(), text.end());
    cout << text << endl;
    size_t start = 0, end;
    while((end = text.find(" ", start)) != string::npos) {
      reverse(text.begin() + start, text.begin() + end);
      start = end + 1;
    }
    reverse(text.begin() + start, text.end());
    cout << text << endl;
  }

  /*****************************************************************************
   * removeAndReplace()
   */
  void removeAndReplace(string &text, char remove,
                        char change_from, string change_to) {
    int i = 0, pos = 0, length = (int) text.size(), count = 0;

    (void)change_to;

    for(i = 0; i < length; ++i) {
      if(text[i] != remove) {
        text[pos++] = text[i];
      }
      if(text[i] == change_from)
        count++;
    }
    text[pos] = ' ';
    iLog(0, "After 1st pass %s (len=%d)", text.c_str(), pos);

    /*
     */
    int newLength = pos + (count * (change_to.size() - 1));
    text.resize(newLength, '\0');
    i = pos - 1;
    pos = newLength - 1;
    while(i >= 0) {
      iLog(0, "text[%d]=%c", i, text[i]);
      if(text[i] == change_from) {
        for(int j = (int) change_to.size()-1; j >= 0; j--) {
          iLog(1, "Replace text[%d]=%c with change_to[%d]]=%c",
               pos, text[pos], j, change_to[j]);
          text[pos--] = change_to[j];
        }
      } else {
        iLog(1, "Copy text[%d]=%c to text[%d]", i, text[i], pos);
        text[pos--] = text[i];
      }
      i--;
    }
    iLog(0, "After 2nd pass %s", text.c_str());
  }

 private:
  int RADIX = 26;
};

#endif /* __PRIMITIVE_H__ */
