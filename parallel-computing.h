#ifndef __PARALLEL_COMPUTING_H__
#define __PARALLEL_COMPUTING_H__

#include <chrono>
#include <thread>
#include <mutex>
#include <iomanip>
#include <queue>
#include <condition_variable>

using std::chrono::milliseconds;
using std::this_thread::sleep_for;
using std::mutex;
using std::chrono::system_clock;
using std::chrono::duration;
using std::setprecision;
using std::lock_guard;
using std::thread;
using std::this_thread::get_id;
using std::queue;
using std::condition_variable;
using std::unique_lock;

#include "idebug.h"

/*******************************************************************************
 *  namespace ServiceWithCache1
 */
namespace ServiceWithCache1 {
  /********
   *  class ServiceRequest
   */
  class ServiceRequest {
   public:
    ServiceRequest(const string& s) : request_(s) {}

    string ExtractWordToCheckFromRequest() { return request_; }

   private:
    string request_;
  };

  /********
   *  class ServiceResponse
   */
  class ServiceResponse {
   public:
    const vector<string>& response() { return response_; }

    void EncodeIntoResponse(const vector<string>& s) { response_ = s; }

   private:
    vector<string> response_;
  };

  /********
   *  ClosestInDictionary()
   */
  vector<string> ClosestInDictionary(const string& w) {
    sleep_for(milliseconds(200));
    return {w + "_result"};
  }

  /********
   *  class SpellCheckService
   */
  class SpellCheckService {
   public:
    static void Service(ServiceRequest& req, ServiceResponse& resp) {
      string w = req.ExtractWordToCheckFromRequest();
      if (w != w_last_) {
        w_last_ = move(w);
        closest_to_last_word_ = ClosestInDictionary(w_last_);
      }
      resp.EncodeIntoResponse(closest_to_last_word_);
    }

   private:
    static string w_last_;
    static vector<string> closest_to_last_word_;
  };

  /********
   *  ServiceThread()
   */
  void ServiceThread(const string& data) {
    iLog(0, "Starting thread %d : %s", get_id(), data.c_str());
    static mutex mx;
    auto start_time = system_clock::now();
    ServiceRequest req(data);
    ServiceResponse resp;
    lock_guard<mutex> lock(mx);
    SpellCheckService::Service(req, resp);
    duration<float> running_time = system_clock::now() - start_time;
    cout << data << " -> " << resp.response()[0] << " (" << setprecision(3)
         << running_time.count() << " sec)" << endl;
  }

  string SpellCheckService::w_last_;
  vector<string> SpellCheckService::closest_to_last_word_;
};

/*******************************************************************************
 *  namespace ServiceWithCache2
 */
namespace ServiceWithCache2 {
  /********
   *  class ServiceRequest
   */
  class ServiceRequest {
   public:
    ServiceRequest(const string& s) : request_(s) {}

    string ExtractWordToCheckFromRequest() { return request_; }

   private:
    string request_;
  };

  /********
   *  class ServiceResponse
   */
  class ServiceResponse {
   public:
    const vector<string>& response() { return response_; }

    void EncodeIntoResponse(const vector<string>& s) { response_ = s; }

   private:
    vector<string> response_;
  };

  /********
   *  ClosestInDictionary
   */
  vector<string> ClosestInDictionary(const string& w) {
    sleep_for(milliseconds(200));
    return {w + "_result"};
  }

  /********
   *  class SpellCheckService
   */
  class SpellCheckService {
   public:
    static void Service(ServiceRequest& req, ServiceResponse& resp) {
      string w = req.ExtractWordToCheckFromRequest();
      vector<string> result;
      bool found = false;
      {
        lock_guard<mutex> lock(mx);
        if (w == w_last_) {
          result = closest_to_last_word_;
          found = true;
        }
      }
      if (!found) {
        result = ClosestInDictionary(w);
        lock_guard<mutex> lock(mx);
        w_last_ = move(w);
        closest_to_last_word_ = result;
      }
      resp.EncodeIntoResponse(result);
    }

   private:
    static string w_last_;
    static vector<string> closest_to_last_word_;
    static mutex mx;
  };

  /********
   *  ServiceThread()
   */
  void ServiceThread(const string& data) {
    iLog(0, "Starting thread %d : %s", get_id(), data.c_str());
    auto start_time = system_clock::now();
    ServiceRequest req(data);
    ServiceResponse resp;
    SpellCheckService::Service(req, resp);
    duration<float> running_time = system_clock::now() - start_time;
    cout << data << " -> " << resp.response()[0] << " (" << setprecision(3)
         << running_time.count() << " sec)" << endl;
  }

  string SpellCheckService::w_last_;
  vector<string> SpellCheckService::closest_to_last_word_;
  mutex SpellCheckService::mx;
};

/*******************************************************************************
 *  namespace ServiceWithCache2
 */
namespace RequesterClass {
  /*
  class Requester {
   public:
    void Execute(string &s, int milliTimeout) {
      executeHelper(s, milliTimeout);
    }

    static void taskRunner(string &s) {
      cout << "Executing " << s << endl;
      sleep_for(milliseconds(500));
    }

    static void timeRunner(thread *th, int timeout) {
    }

    void executeHelper(string &s, int milliTimeout) {
      thread main(taskRunner, s);
      thread time(timeRunner, &main, milliTimeout);
    }
   private:
  };
   */
};

/*******************************************************************************
 *  namespace ReadersWriters1
 */
namespace ReadersWriters1 {
  namespace SYNC {
    mutex mutexRead, mutexWrite;
    condition_variable condRead;
    int readCount = 0;
    int data = 0;
  };

  queue<string> cq;

  class Reader {
   public:
    Reader(string name) : name(name) {
    }

    void operator ()(string s) {
      while(true) {
        {
          lock_guard<mutex> lock(SYNC::mutexRead);
          SYNC::readCount++;
        }
        if(SYNC::data > 0) {
          cout << "\t\t\t\t\t" << name << ":" << s << ":" << SYNC::data-- << endl;
        } else {
          cout << "\t\t\t\t\t" << name << ":" << s << ":" << "EMPTY" << endl;
        }
        {
          lock_guard<mutex> lock(SYNC::mutexRead);
          SYNC::readCount--;
          SYNC::condRead.notify_one();
        }
        sleep_for(milliseconds(1000));
        /*
         */
      }
    }
   protected:
    string name;
  };

  class Writer {
   public:
    Writer(string name) : name(name) {
    }

    void operator ()(string s) {
      cout << name << " : START" << endl;
      while(true) {
        unique_lock<mutex> lockWrite(SYNC::mutexWrite);
        bool done = false;
        while(!done) {
          unique_lock<mutex> lockRead(SYNC::mutexRead);
          if(SYNC::readCount == 0) {
            SYNC::data++;
            cout << name << ":" << s << ":" << SYNC::data << endl;
            done = true;
          } else {
            while(SYNC::readCount != 0) {
              cout << "\t" << name << " : wait on read count" << endl;
              SYNC::condRead.wait(lockRead);
            }
          }
          /*
          lockRead.unlock();
           */
        }
        lockWrite.unlock();
        sleep_for(milliseconds(1000));
        /*
         */
      }
    }
   protected:
    string name;
  };
};

/*******************************************************************************
 *  class Semaphore
 */
class Semaphore {
  Semaphore(int maxAvailable) : maxAvailable(maxAvailable), taken(0) {
  }

 public:
  void acquire() {
    unique_lock<mutex> lock(mtx);
    while(taken == maxAvailable) {
      cond.wait(lock);
    }
    ++taken;
  }

  void release() {
    lock_guard<mutex> lock(mtx);
    --taken;
    cond.notify_all();
  }

 protected:
  int maxAvailable;
  int taken;
  condition_variable cond;
  mutex mtx;
};

/*******************************************************************************
 *  namespace TwoThreadsIncrementing
 */
namespace TwoThreadsIncrementing {
  static int counter = 0;

  void increment(int n, int threadId) {
    for(int i = 0; i < n; i++) {
      counter++;
      cout << "Thread : " << threadId << " = " << counter << endl;
    }
  }
};

/*******************************************************************************
 *  class OddEvenTurn
 */
class OddEvenTurn {
 public:
  OddEvenTurn(int n) : count(n), turn(true) {
  }

  void threadEntry(bool odd) {
    for(int i = 1; i <= count; i++) {
      if((i % 2 == 0) == odd) {
        continue;
      }
      wait(odd);
      cout << "Thread " << odd << " : " << i << endl;
      toggle();
    }
  }

  thread createThread(bool odd) {
    return thread([=] { threadEntry(odd); });
  }

 protected:
  int count;
  bool turn;
  mutex mtx;
  condition_variable cond;

  void wait(bool val) {
    unique_lock<mutex> lock(mtx);
    while(turn != val) {
      cond.wait(lock);
    }
  }

  void toggle() {
    lock_guard<mutex> lock(mutex);
    turn = !turn;
    cond.notify_one();
  }
};

#endif /* __PARALLEL_COMPUTING_H__ */
