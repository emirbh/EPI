#include <iostream>
#include <limits>

using std::cout;
using std::endl;

#include "idebug.h"
#include "trees.h"
#include "llists.h"
#include "binary-search-trees.h"

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
        cout << "EPI: ";
        cout << "Satisfies BST Property" << endl;
        vector<int> v;
        readArray(v);
        Bst<int> bst(v);
        bool isBst = bst.isBst();
        cout << "BST Property : " << isBst << endl;
        /*
        bst.print();
         */
        break;
      }
      /* ---- 02 ------------------------------------------------------------ */
      case 2: {
        cout << "EPI: ";
        cout << "Node Successor" << endl;
        vector<int> v;
        readArray(v);
        int x;
        cin >> x;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Bst<int> bst(v);
        int successor = bst.findSuccessor(x);
        cout << x << " successor : " << successor << endl;
        /*
        bst.print();
         */
        break;
      }
      /* ---- 03 ------------------------------------------------------------ */
      case 3: {
        cout << "EPI: ";
        cout << "Insert and delete node" << endl;
        /*
         *  @TODO implement this in Bst
         */
        break;
      }
      /* ---- 06 ------------------------------------------------------------ */
      case 6: {
        cout << "EPI: ";
        cout << "Min-First BST" << endl;
        /*
         *  @TODO implement this
         */
        break;
      }
      /* ---- 07 ------------------------------------------------------------ */
      case 7: {
        cout << "EPI: ";
        cout << "BST from sorted array" << endl;
        vector<int> v;
        readArray(v);
        Bst<int> bst;
        bst.fromSorted(v);
        /*
         */
        break;
      }
      /* ---- 08 ------------------------------------------------------------ */
      case 8: {
        cout << "EPI: ";
        cout << "BST from sorted linked list" << endl;
        vector<int> v;
        readArray(v);
        LinkedList<int> ll(v);
        Bst<int> bst;
        bst.fromLinkedList(ll);
        /*
         *  @TODO implement function
         */
        break;
      }
      default: {
        break;
      }
    }

    cin >> part;
  }
}
