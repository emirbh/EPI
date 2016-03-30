#ifndef __BINARY_SEARCH_TREES_H__
#define __BINARY_SEARCH_TREES_H__

#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;
using std::make_shared;

#include "idebug.h"
#include "trees.h"
#include "llists.h"

/*******************************************************************************
 *  class Bst
 */
template <typename T>
class Bst : public BinaryTree<T> {
 public:
  Bst() : BinaryTree<T>() {
  }

  Bst(vector<T> &v) : BinaryTree<T>(v) {
  }

  bool isBst() {
    return this->isBstHelper(this->root, numeric_limits<T>::min(),
                             numeric_limits<T>::max(), 0);
  }

  T findSuccessor(T value) {
    shared_ptr<BinaryTreeNode<T>> node = findNodeHelper(value);
    shared_ptr<BinaryTreeNode<T>> successor = findSuccessorHelper(node, 0);
    return successor->data;
  }

  void fromSorted(vector<T> &v) {
    this->root = fromSortedHelper(v, 0, static_cast<int>(v.size()), 0);
  }

  void fromLinkedList(LinkedList<T> &l) {
    (void) l;
    /*
    int size = l.size();
    this->root = fromLinkedListHelper(l, 0, size, 0);
     */
  }

 protected:
  bool isBstHelper(shared_ptr<BinaryTreeNode<T>> node, const T &lower,
                   const T&upper, int level) {
    iLog(level, "Check %d", node->data);
    if(!node->data) {
      return true;
    } else if(node->data < lower || node->data > upper) {
      return false;
    }
    return (node->left ?
            isBstHelper(node->left, lower, node->data, level+1) : true) &&
           (node->right ?
            isBstHelper(node->right, node->data, upper, level+1) : true);
  }

  shared_ptr<BinaryTreeNode<T>> findNodeHelper(T value) {
    shared_ptr<BinaryTreeNode<T>> node = this->root;
    iLog(1, "Find node for %d", value);
    while(node) {
      if(node->data == value) {
        iLog(0, "Found node for %d", value);
        break;
      } else if(value < node->data) {
        node = node->left;
      } else /* if(value > node->data) */ {
        node = node->right;
      }
    }
    return node;
  }

  shared_ptr<BinaryTreeNode<T>> findSuccessorHelper(
      shared_ptr<BinaryTreeNode<T>> node, int level) {
    /*
     *  first cheeck if node has right sub-tree and go all the way left
     */
    if(node->right) {
      iLog(level, "Take right node for %d", node->data);
      node = node->right;
      auto left = node->left;
      while(node->left)
        iLog(level+1, "Take left node for %d", node->data);
        node = node->left;
      return node;
    }

    /*
     *  now find first parent where node is not the right child
     */
    while(node->parent && node->parent->right == node) {
      node = node->parent;
    }

    return node->parent;
  }

  shared_ptr<BinaryTreeNode<T>> fromSortedHelper(vector<T> &v, int s, int e,
                                                 int l) {
    int m = s + (e - s)/2;
    if(m >= e)
      return nullptr;

    shared_ptr<BinaryTreeNode<T>> node = make_shared<BinaryTreeNode<T>>(v[m]);

    iLog(l, "Created node %d", v[m]);

    node->left = fromSortedHelper(v, s, m, l + 1);
    if(node->left)
      node->left->parent = node;

    node->right = fromSortedHelper(v, m+1, e, l + 1);
    if(node->right)
      node->right->parent = node;

    return node;
  }

  /*
  shared_ptr<BinaryTreeNode<T>> fromLinkedListHelper(vector<T> &v, int s, int e,
                                                 int l) {
    (void) v;
    (void) s;
    (void) e;
    (void) l;
    return nullptr;
  }
   */
};

/*******************************************************************************
 *  class BstRbNode
 */
template <typename T>
class BstRbNode {
 public:
   /*
    * @TODO make private
    */
  T key;
  bool isRed;
  shared_ptr<BstRbNode<T>> left, right;

  BstRbNode(T key)
      : key(key), isRed(true), left(nullptr), right(nullptr) {
  }

 protected:
};

/*******************************************************************************
 *  class BstRdTree
 */
template <typename T>
class BstRbTree {
 public:
  BstRbTree()
    : root(nullptr) {
  }

  void add(T key) {
    root = addNode(root, key);
    root->isRed = false;
  }

  void print() {
    int level = 0;
    printBstRbTree(root, level);
  }

 protected:
  shared_ptr<BstRbNode<T>> root;

  shared_ptr<BstRbNode<T>> addNode(shared_ptr<BstRbNode<T>> parent, T key) {
    if (!parent) {
      // parent = new shared_ptr<BstRbNode<T>>(key);
      parent = std::make_shared<BstRbNode<T>>(key);
      return parent;
    }

    // iLog(0, "node %d -> add %d", parent->key, key);

    if (key < parent->key) {
      parent->left = addNode(parent->left, key);
    } else if (key > parent->key) {
      parent->right = addNode(parent->right, key);
    } else { // if (parent->key == key)
      parent->key = key;
    }

    if (!isRed(parent->left) && isRed(parent->right) ) {
      // iLog(1, "Rotate Left %d", parent->key);
      parent = rotateLeft(parent);
    }
    if (isRed(parent->left) && isRed(parent->left->left)) {
      // iLog(1, "Rotate Right %d", parent->key);
      parent = rotateRight(parent);
    }
    if (isRed(parent->left) && isRed(parent->right)) {
      flipColors(parent);
    }

    // print();

    return parent;
  }

  bool isRed(shared_ptr<BstRbNode<T>> node) {
    if (node == nullptr) return false;
    return node->isRed;
  }

  shared_ptr<BstRbNode<T>> rotateLeft(shared_ptr<BstRbNode<T>> h) {
    /*
     *      H              X
     *     / \            / \
     *    a   X    =>    H   c
     *       / \        / \
     *      b   c      a   b
     */
    shared_ptr<BstRbNode<T>> x = h->right;
    h->right = x->left;
    x->left = h;
    x->isRed = h->isRed;
    h->isRed = true;
    return x;
  }

  shared_ptr<BstRbNode<T>> rotateRight(shared_ptr<BstRbNode<T>> h) {
    /*
     *      H              X
     *     / \            / \
     *    X   c    =>    a   H
     *   / \                / \
     *  a   b              b   c
     */
    shared_ptr<BstRbNode<T>> x = h->left;
    h->left = x->right;
    x->right = h;
    x->isRed = h->isRed;
    h->isRed = true;
    return x;
  }

  void flipColors(shared_ptr<BstRbNode<T>> x) {
    x->isRed = true;
    x->left->isRed = x->right->isRed = false;
  }

  void printBstRbTree(shared_ptr<BstRbNode<T>> node, int level) {
    if(node == nullptr) {
      return;
    }

    /*
     */
    if (node->isRed) {
      iLog(level, "Node: %d (level=%d) (red)", node->key, level);
    } else {
      iLog(level, "Node: %d (level=%d) ", node->key, level);
      /*
      iLog(level+1, "Node: %d (level=%d) ", node->key, level+1);
       */
    }

    printBstRbTree(node->left, level+1);
    printBstRbTree(node->right, level+1);
  }
};

#endif /* __BINARY_SEARCH_TREES_H__ */
