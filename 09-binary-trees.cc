#include <iostream>
#include <limits>

using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;

#include "idebug.h"
#include "trees.h"

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
        vector<int> v;
        readArray(v);
        BinaryTree<int> bt(v);
        bool balanced = bt.isBalancedTree();
        cout << "Balanced = " << balanced;
        break;
      }
      /* ---- 05 ------------------------------------------------------------ */
      case 5: {
        vector<int> v;
        readArray(v);
        BinaryTree<int> bt(v);
        bt.iterativeInOrderTraversal();
        break;
      }
      /* ---- 06 ------------------------------------------------------------ */
      case 6: {
        vector<int> v;
        readArray(v);
        BinaryTree<int> bt(v);
        int k;
        cin >> k;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        bt.iterativeInOrderTraversal();
        shared_ptr<BinaryTreeNode<int>> node = bt.findKthNode(k);
        cout << k << "-th node is " << node->data << endl;
        break;
      }
      /* ---- 07 ------------------------------------------------------------ */
      case 7: {
        vector<char> v;
        readArray(v);
        BinaryTree<char> bt;
        printContainer(v);
        bt.reconstructFromPreorder(v);
        bt.print();
        break;
      }
      default: {
        break;
      }
    }

    cin >> part;
  }
}
