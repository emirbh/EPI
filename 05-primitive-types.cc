#include <iostream>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;

#include "idebug.h"
#include "primitive.h"

int main() {
  int part;
  cin >> part;

  PrimitiveOps<long> slBitOps;
  PrimitiveOps<unsigned long> ulBitOps;

  /*
   */
  unsigned short x = 10;
  unsigned short w = x - 1;
  unsigned short y = x & (x - 1);
  unsigned short n = x & ~(x - 1);
  unsigned short m = x & (x + 1);
  unsigned short z = x ^ 1;
  unsigned short t = x ^ 8;
  unsigned short s = x | 4;
  unsigned short r = x & 4;
  unsigned short p = x; p =~ x;
  cout << "x           =" << x << " \t[bin=" << itob(x) << "]" <<  endl;
  cout << "[x-1]       =" << w << " \t[bin=" << itob(w) << "]" <<  endl;
  cout << "[x &= (x-1)]=" << y << " \t[bin=" << itob(y) << "]" <<  endl;
  cout << "[x &=~(x-1)]=" << n << " \t[bin=" << itob(n) << "]" <<  endl;
  cout << "[x &= (x+1)]=" << m << " \t[bin=" << itob(m) << "]" <<  endl;
  cout << "[x ^= 1]    =" << z << " \t[bin=" << itob(z) << "]" <<  endl;
  cout << "[x ^= 8]    =" << t << " \t[bin=" << itob(t) << "]" <<  endl;
  cout << "[x |= 4]    =" << s << " \t[bin=" << itob(s) << "]" <<  endl;
  cout << "[x &= 4]    =" << r << " \t[bin=" << itob(r) << "]" <<  endl;
  cout << "[x ~= x]    =" << r << " \t[bin=" << itob(p) << "]" <<  endl;

  while(part != -1) {
    cout << "Part: " << part << "----------------------------------------";
    cout << "--------------------------------" << endl;

    switch(part) {
      /* ---- 01 ------------------------------------------------------------ */
      case 1: {
        /*
        PrimitiveOps<unsigned short>::parity(11);
        unsigned short number = 11;
        bitops.parity(number);
         */
        cout << "EPI: ";
        cout << "Parity" << endl;
        unsigned long number = 11;
        cin >> number;
        cout << ulBitOps.parity(number) << endl;
        break;
      }
      /* ---- 02 ------------------------------------------------------------ */
      case 2: {
        cout << "EPI: ";
        cout << "Swap Bits" << endl;
        unsigned long number = 11;
        cin >> number;
        cout << itob(number) << endl;
        number = ulBitOps.swapBits(number, 1, 2);
        cout << itob(number) << endl;
        break;
      }
      /* ---- 03 ------------------------------------------------------------ */
      case 3: {
        cout << "EPI: ";
        cout << "Reverse Bits" << endl;
        unsigned long number = 110;
        cin >> number;
        cout << number << " : " << itob(number) << endl;
        number = ulBitOps.reverseBits(number);
        cout << number << " : " << itob(number) << endl;
        break;
      }
      /* ---- 04 ------------------------------------------------------------ */
      case 4: {
        cout << "EPI: ";
        cout << "Closest Larger" << endl;
        unsigned long number = 110;
        cin >> number;
        cout << number << " : " << itob(number) << endl;
        number = ulBitOps.closestLarger(number);
        cout << number << " : " << itob(number) << endl;
        break;
      }
      /* ---- 05 ------------------------------------------------------------ */
      case 5: {
        /*
         *  @TODO this is strange problem, maybe I should look at it some more
         */
        cout << "EPI: ";
        cout << "Generate Power Set" << endl;
        vector<unsigned long> v;
        readArray(v);
        printContainer(v, "Power Set of" );
        vector<vector<unsigned long>> pset = ulBitOps.generatePowerSet(v);
        for(const vector<unsigned long> &sset : pset) {
          printContainer(sset, "Sub Set");
        }
        break;
      }
      /* ---- 06 ------------------------------------------------------------ */
      case 6: {
        cout << "EPI: ";
        cout << "int to string/string to int" << endl;
        unsigned long i = 110;
        cin >> i;
        string si = ulBitOps.intToString(i);
        cout << "From int=" << i << " to string=" << si << endl;
        int is = slBitOps.stringToInt(si);
        cout << "From string=" << si << "to int=" << is << endl;
        break;
      }
      /* ---- 07 ------------------------------------------------------------ */
      case 7: {
        cout << "EPI: ";
        cout << "convert to different base" << endl;
        string value1 = "1111";
        long base1 = 10;
        long base2 = 16;
        cin >> value1 >> base1 >> base2;
        string value2 = slBitOps.convert_base(value1, base1, base2);
        cout << value1 << " = " << value2 << endl;
        break;
      }
      /* ---- 08 ------------------------------------------------------------ */
      case 8: {
        cout << "EPI: ";
        cout << "Excel Column ID to intreger" << endl;
        string col = "ZZ";
        cin >> col;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        long value = slBitOps.convertExcelColumnID(col);
        cout << col << " = " << value << endl;
        break;
      }
      /* ---- 10 ------------------------------------------------------------ */
      case 10: {
        cout << "EPI: ";
        cout << "GCD" << endl;
        unsigned long ul1, ul2;
        cin >> ul1 >> ul2;
        unsigned long ul = ulBitOps.gcd(ul1, ul2);
        cout << "gcd(" << ul1 << "," << ul2 << ")=" << ul << endl;
        break;
      }
      /* ---- 12 ------------------------------------------------------------ */
      case 12: {
        cout << "EPI: ";
        cout << "Rectangles Intersection" << endl;
        vector<vector<unsigned long>> v;
        readMatrix(v);
        for(size_t i = 0; i < v.size(); i++) {
          if(v[i].size() != 8) {
            cout << "Invalid dscription of two rectangles." << endl;
            continue;
          }
          PrimitiveOps<unsigned long>::Rectangle r1{
            v[i][0], v[i][1], v[i][2], v[i][3]
          };
          PrimitiveOps<unsigned long>::Rectangle r2{
            v[i][4], v[i][5], v[i][6], v[i][7]
          };
          if(ulBitOps.is_intersect(r1, r2)) {
            PrimitiveOps<unsigned long>::Rectangle ri =
              ulBitOps.intersection_rectangle(r1, r2);
            cout << ri.x << ":" << ri.y << ":" << ri.width << ":" << ri.height;
            cout << endl;
          }
          exit(1);
        }
        break;
      }
      /* ---- 13 ------------------------------------------------------------ */
      case 13: {
        cout << "EPI: ";
        cout << "Divide" << endl;
        unsigned a, b;
        cin >> a >> b;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        PrimitiveOps<unsigned int> pops;
        unsigned x = pops.add(a, b);
        cout << x << endl;
        break;
      }
      /* ---- 14 ------------------------------------------------------------ */
      case 14: {
        cout << "EPI: ";
        cout << "Divide" << endl;
        int x, y;
        cin >> x >> y;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        PrimitiveOps<int> pops;
        int result = pops.divide(x, y);
        cout << x << "/" << y << " = " << result << endl;
      }
      /* ---- 40 ------------------------------------------------------------ */
      case 40: {
        cout << "EPI: ";
        cout << "Is double a palindrome" << endl;
        int x;
        cin >> x;
        bool isPalindrome = PrimitiveOps<int>::isDecimalPalindrome(x);
        cout << x << " is palindrome = " << isPalindrome << endl;
      }
    }

    cin >> part;
  }
}
