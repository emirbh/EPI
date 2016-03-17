#ifndef __BINARY_SEARCH_TREES_H__
#define __BINARY_SEARCH_TREES_H__

#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

/*******************************************************************************
 *  class Bst
 */
template <typename T>
class Bst {
 public:
  Bst(vector<T> &v) {
    (void)v;
  }

  bool isBst() {
    return true;
  }

 private:
  struct Node {
    T data;
    shared_ptr<Node> left, right;
  };
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

 private:
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

 private:
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
