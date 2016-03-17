#ifndef __LLISTS_H__
#define __LLISTS_H__

#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::make_shared;
using std::vector;

/*******************************************************************************
 * class ListNode
 */
template <typename T>
struct ListNode {
  T data;
  shared_ptr<ListNode<T>> next;
};

/*******************************************************************************
 * class LinkedList
 */
template <typename T>
class LinkedList {
 private:
  shared_ptr<ListNode<T>> head;
  shared_ptr<ListNode<T>> tail;

  void append_node(shared_ptr<ListNode<T>>& head,
                   shared_ptr<ListNode<T>>& tail,
                   shared_ptr<ListNode<T>>& node) {
    head ? tail->next = node : head = node;
    tail = node;
  }

  void append_node_and_advance(shared_ptr<ListNode<T>>& head,
                               shared_ptr<ListNode<T>>& tail,
                               shared_ptr<ListNode<T>>& node) {
    append_node(head, tail, node);
    node = node->next;
  }

 public:
  /*****************************************************************************
   *  Vector Constructor
   */
  LinkedList(vector<T>& init) {
    for (size_t i = init.size(); i > 0; i-- ) {
      auto curr = make_shared<ListNode<T>>(ListNode<T>{init[i-1], nullptr});
      curr->next = head;
      head = curr;
    }
    tail = make_shared<ListNode<T>>(ListNode<T>{init[init.size()-1], nullptr});

    iLog(0, "head=%d tail=%d", head->data, tail->data);
  }

  /*****************************************************************************
   *  print()
   */
  void print() {
    shared_ptr<ListNode<T>> hd = head;
    while(hd) {
      cout << hd->data << " ";
      hd = hd->next;
      cout << endl;
      if(hd == head)
        break;
    }
    cout << endl;
  }

  void merge(LinkedList &that) {
    shared_ptr<ListNode<T>> mhead = nullptr, mtail = nullptr;
    shared_ptr<ListNode<T>> wthis = head, wthat = that.head;
    shared_ptr<ListNode<T>> tthis = tail, tthat = that.tail;

    /*
    while(wthis != tthis && wthat != tthat) {
     */
    while(wthis && wthat) {
      iLog(0, "compare %d %d", wthis->data, wthat->data);
      append_node_and_advance(mhead, mtail,
                              wthis->data < wthat->data ? wthis : wthat);
      iLog(1, "head %d tail %d", mhead->data, mtail->data);
    }
    if(wthis)
      append_node(mhead, mtail, wthis);
    if(wthat)
      append_node(mhead, mtail, wthat);

    head = mhead;
    tail = mtail;
  }

  /*****************************************************************************
   *  compare()
   */
  int compare(shared_ptr<ListNode<T>> head2) {
    int result = 0;
    shared_ptr<ListNode<T>> head1 = head;

    while (head1 != nullptr && head2 != nullptr) {
      if (head1->data < head2->data) {
        return -1;
      } else if (head1->data > head2->data) {
        return 1;
      }
      head1 = head1->next;
      head2 = head2->next;
    }

    if (head1 != nullptr && head2 == nullptr) {
      result = -1;
    } else if (head1 == nullptr && head2 != nullptr) {
      result = 1;
    }

    return result;
  }

  /*****************************************************************************
   *  merge()
   */
  shared_ptr<ListNode<T>> merge(shared_ptr<ListNode<T>> head2) {
    shared_ptr<ListNode<T>> head1 = this->head;
    shared_ptr<ListNode<T>> head = nullptr, tail = nullptr;

    while (head1 && head2) {
      append_node_and_advance(head, tail,
                              head1->data < head2->data ? head1 : head2);
    }

    if (head1) {
      append_node(head, tail, head1);
    }

    if (head2) {
      append_node(head, tail, head2);
    }

    return head;
  }

  /*****************************************************************************
   *  setCycle()
   */
  void setCycle(int n) {
    shared_ptr<ListNode<T>> tail = head, cycle = head;
    int cntr = 0;
    while ((++cntr)<n) {
      iLog(0, "cntr=%d Cycle: %d", cntr, cycle->data);
      cycle = cycle->next;
    }

    while (tail->next) {
      tail = tail->next;
    }
    tail->next = cycle;
    iLog(0, "Cycle: %d", cycle->data);
  }

  /*****************************************************************************
   *  findCycle()
   */
  shared_ptr<ListNode<T>> findCycle() {
    shared_ptr<ListNode<T>> slow = head, fast = head;
    while (slow && fast && slow->next && fast->next && fast->next->next) {
      iLog(0, "slow=%d fast=%d", slow->data, fast->data);
      slow = slow->next;
      fast = fast->next->next;
      if (slow == fast) {
        /*
         * Found cycle now calculate the length of the cycle and get the start
         * of the start by increasing fast by "cycle length" and then move
         * node/fast at the same speed until they become equal
         */
        int cycle_length = 0;
        do {
          cycle_length++;
          fast = fast->next;
        } while (fast != slow);

        slow = fast = head;

        while (cycle_length-- > 0) {
          fast = fast->next;
        }

        while (slow != fast) {
          slow = slow->next;
          fast = fast->next;
        }
        return slow;
      }
    }
    return nullptr;
  }

  /*****************************************************************************
   *  reverseList()
   */
  shared_ptr<ListNode<T>> reverse_list() {
    /*
     *  H -> 1 -> 2 -> 3 -> 4 -> 5 -> 6
     *  H -> 2 -> 1 -> 3 -> 4 -> 5 -> 6
     *  H -> 3 -> 2 -> 1 -> 4 -> 5 -> 6
     */
    shared_ptr<ListNode<T>> curr = head, prev = nullptr, temp;

    while (curr) {
      temp = curr->next;
      iLog(0, "curr=%d prev=%d temp=%d",
           curr->data, prev ? prev->data : -1, temp ? temp->data : -1);
      curr->next = prev;
      prev = curr;
      curr = temp;
    }

    return prev;
  }

  /*****************************************************************************
   *  getMiddle()
   */
  shared_ptr<ListNode<T>> get_midle() {
    shared_ptr<ListNode<T>> midle = head, fast = head;
    while (fast && fast->next && fast->next->next) {
      midle = midle->next;
      fast = fast->next->next;
    }
    return midle;
  }

  /*****************************************************************************
   *  getMiddle()
   */
  void sortOddEven() {
    /*
     *  0 1 2 3 4 5
     *
     *  0 2 4
     *   1 3 5
     */
    shared_ptr<ListNode<T>> nhead = nullptr, ntail = nullptr,
                            wev = head, wod = wev ? wev->next : nullptr,
                            prev_wev = head, cod = wod;

    while(wod && wev) {
      iLog(0, "even=%d odd=%d", wev->data, wod->data);
      wev->next = wod->next;
      prev_wev = wev;
      wev = wev->next;
      if(wev) {
        wod->next = wev->next;
        wod = wod->next;
      }
    }
    if(prev_wev) {
      prev_wev->next = cod;
    }

    /*
    head = nhead;
    tail = ntail;
     */
  }
};

#endif /* __LLISTS_H__ */
