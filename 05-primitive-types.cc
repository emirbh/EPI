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
  unsigned short x = 8;
  unsigned short w = x - 1;
  unsigned short y = x & (x - 1);
  unsigned short z = x ^ 1;
  unsigned short t = x ^ 8;
  unsigned short s = x | 4;
  unsigned short r = x & 4;
  unsigned short p = x; p =~ x;
  unsigned short m = x & (x + 1);
  cout << "x           =" << x << " \t[bin=" << itob(x) << "]" <<  endl;
  cout << "[x-1]       =" << w << " \t[bin=" << itob(w) << "]" <<  endl;
  cout << "[x &= (x-1)]=" << y << " \t[bin=" << itob(y) << "]" <<  endl;
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
    }

    cin >> part;
  }
}