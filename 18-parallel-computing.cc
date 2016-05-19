#include <iostream>
#include <limits>

using std::cin;
using std::cout;
using std::endl;

#include "idebug.h"
#include "parallel-computing.h"

int main() {
  int part;
  cin >> part;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  while(part != -1) {
    cout << "Part: " << part << "----------------------------------------";
    cout << "--------------------------------" << endl;

    switch(part) {
      /* ---- 01 ------------------------------------------------------------ */
      case 1: {
        int n;
        cin >> n;
        cout << "1) ----------------------" << endl;
        {
          cout << "EPI: ";
          cout << "Service with Caching (1)" << endl;
          using namespace ServiceWithCache1;
          for(int i = 0; i < n; i++) {
            thread(ServiceThread, "req:" + to_string(i + 1)).detach();
            sleep_for(milliseconds(200));
          }
        }
        cout << "2) ----------------------" << endl;
        {
          cout << "EPI: ";
          cout << "Service with Caching (2)" << endl;
          using namespace ServiceWithCache2;
          for(int i = 0; i < n; i++) {
            thread(ServiceThread, "req:" + to_string(i + 1)).detach();
            sleep_for(milliseconds(200));
          }
        }
        break;
      }
      /* ---- 02 ------------------------------------------------------------ */
      case 2: {
        /*
         *  @TODO implement concurrent queue and simple code
         */
        cout << "EPI: ";
        cout << "Task Execution Server (aka Web Server)" << endl;
        break;
      }
      /* ---- 03 ------------------------------------------------------------ */
      case 3: {
        cout << "EPI: ";
        cout << "Requester class" << endl;
        using namespace RequesterClass;
        break;
      }
      /* ---- 05 ------------------------------------------------------------ */
      case 5: {
        cout << "EPI: ";
        cout << "Readers Writers Problem 1" << endl;
        using namespace ReadersWriters1;
        thread tw1(Writer("writerOne"), "write");
        thread tw2(Writer("writerTwo"), "write");
        thread tr1(Reader("readerOne"), "read");
        thread tr2(Reader("readerTwo"), "read");
        sleep_for(milliseconds(10000));
        break;
      }
      /* ---- 20 ------------------------------------------------------------ */
      case 20: {
        cout << "EPI: ";
        cout << "Two threads incrementing" << endl;
        using namespace TwoThreadsIncrementing;
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        int threadId = 0;
        thread t1(increment, n, ++threadId);
        thread t2(increment, n, ++threadId);
        t1.join();
        t2.join();
        cout << "Counter = " << counter << endl;
        break;
      }
      /* ---- 22 ------------------------------------------------------------ */
      case 22: {
        cout << "EPI: ";
        cout << "Two threads incrementing" << endl;
        using namespace TwoThreadsIncrementing;
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        int threadId = 0;
        thread t1(increment, n, ++threadId);
        thread t2(increment, n, ++threadId);
        t1.join();
        t2.join();
        cout << "Counter = " << counter << endl;
        break;
      }
      /* ---- 23 ------------------------------------------------------------ */
      case 23: {
        cout << "EPI: ";
        cout << "Odd Even Turn" << endl;
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        OddEvenTurn oe(n);
        thread t1 = oe.createThread(true);
        thread t2 = oe.createThread(false);
        t1.join();
        t2.join();
        /*
         */
        break;
      }
      /* ---- -1 ------------------------------------------------------------ */
      default: {
        break;
      }
    }

    cin >> part;
  }
}
