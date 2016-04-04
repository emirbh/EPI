#ifndef __TREES_H__
#define __TREES_H__

#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <stack>
#include <memory>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::vector;
using std::stack;
using std::make_shared;

/*******************************************************************************
 *  class BinaryTreeNode
 */
template <typename T>
struct BinaryTreeNode {
 public:
  T data;
  shared_ptr<BinaryTreeNode<T>> parent;
  shared_ptr<BinaryTreeNode<T>> left, right;
  int size;

  /*****************************************************************************
   *  BinaryTreeNode()
   */
  BinaryTreeNode(T value) {
    data = value;
    size = 0;
  }

  /*****************************************************************************
   *  getters
   */
  const T & getData() { return data; }
  int getSize() { return size; }
  shared_ptr<BinaryTreeNode<T>> getParent() { return parent; }
  shared_ptr<BinaryTreeNode<T>> getLeft() { return left; }
  shared_ptr<BinaryTreeNode<T>> getRight() { return right; }

  /*****************************************************************************
   *  compare()
   */
  int compare(shared_ptr<BinaryTreeNode<T>> that) {
    iLog(0, "Compare %d and %d", this->getData(), that->getData());
    int diff = this->getData() - that->getData();
    if (diff != 0) {
      return diff;
    }

    if (diff == 0) {
      if (this->getLeft() != nullptr && that->getLeft() == nullptr) {
        return -1;
      } else if (this->getLeft() == nullptr && that->getLeft() != nullptr) {
        return 1;
      } else if( this->getLeft() != nullptr && that->getLeft() != nullptr) {
        diff = this->getLeft()->compare(that->getLeft());
      }
    }

    if (diff == 0) {
      if (this->getRight() != nullptr && that->getRight() == nullptr) {
        return -1;
      } else if (this->getRight() == nullptr && that->getRight() != nullptr) {
        return 1;
      } else if( this->getRight() != nullptr && that->getRight() != nullptr) {
        diff = this->getRight()->compare(that->getRight());
      }
    }

    return diff;
  }

  /*****************************************************************************
   *  flatten()
   */
  shared_ptr<BinaryTreeNode<T>> flatten(shared_ptr<BinaryTreeNode<T>> node) {
    shared_ptr<BinaryTreeNode<T>> lroot = nullptr, rroot = nullptr;

    if (node->left) {
      lroot = flatten(node->left);
      node->left = nullptr;
    }

    if (node->right) {
      rroot = flatten(node->right);
      node->right = nullptr;
    }

    if (lroot != nullptr) {
      pushRight(lroot, node);
    } else {
      lroot = node;
    }

    if (rroot != nullptr) {
      pushRight(lroot, rroot);
    }

    return lroot;
  }

  /*****************************************************************************
   *  pushRight()
   */
  void pushRight(shared_ptr<BinaryTreeNode<T>> node,
                  shared_ptr<BinaryTreeNode<T>> right) {
    if (node->right) {
      pushRight(node->right, right);
    } else {
      node->right = right;
    }
  }
};

/*******************************************************************************
 *  class BinaryTree
 */
template <typename T>
class BinaryTree {
 public:
  shared_ptr<BinaryTreeNode<T>> root;

  /*****************************************************************************
   *  BinaryTree()
   */
  BinaryTree() : root(nullptr)  {}

  BinaryTree(vector<T> &v) {
    root = buildBinaryTree(v);
  }

  /*****************************************************************************
   *  buildBinaryTree()
   */
  shared_ptr<BinaryTreeNode<T>> buildBinaryTree(vector<T> &v) {
    int idx = 0;
    auto root = createBinaryTreeNode(v, idx);

    return root;
  }

  /*****************************************************************************
   *  print()
   */
  void print() {
    int level = 0;
    printBinaryTree(root, level);
  }

  /*****************************************************************************
   *  compare()
   */
  int compare(BinaryTree<T> &that) {
    int diff = 0;

    diff = this->root->compare(that.getHead());

    return diff;
  }

  /*****************************************************************************
   *  flatten()
   */
  void flatten() {
    root = root->flatten(root);
  }

  /*****************************************************************************
   *  isBalancedTree()
   */
  bool isBalancedTree() {
    NodeDepth depth = { true, 0 };
    int treeDepth = getNodeDepth(root, depth);
    iLog(0, "Tree is balanced = %d and has maximum depth %d",
         depth.balanced, depth.maxDepth);
    (void)treeDepth;
    return depth.balanced;
  }

  /*****************************************************************************
   *  iterativeInOrderTraversal()()
   */
  void iterativeInOrderTraversal() {
    shared_ptr<BinaryTreeNode<T>> curr = root, prev = nullptr, next = nullptr;
    int level = 0;
    while(curr) {
      if(!prev || prev->left == curr || prev->right == curr) {
        if(curr->left) {
          next = curr->left;
        } else {
          iLog(level, "node %d", curr->data);
          next = curr->right ? curr->right : curr->parent;
        }
      } else if(curr->left == prev) {
          iLog(level, "node %d", curr->data);
          next = curr->right ? curr->right : curr->parent;
      } else if(curr->right == prev) {
        next = curr->parent;
      }
      prev = curr;
      curr = next;
    }
  }

  /*****************************************************************************
   *  findKthNode()()
   */
  shared_ptr<BinaryTreeNode<T>> findKthNode(int k) {
    shared_ptr<BinaryTreeNode<T>> curr = root;
    while(curr) {
      int leftSize = curr->left ? curr->left->size : 0;
      if(leftSize + 1 < k) {
        k -= (leftSize + 1);
        curr = curr->right;
      } else if(k == leftSize + 1) {
        return curr;
      } else {
        curr = curr->left;
      }
    }
    return curr;
  }

  /*****************************************************************************
   *  reconstructFromPreorder()()
   */
  void reconstructFromPreorder(vector<T> v) {
    stack<shared_ptr<BinaryTreeNode<T>>> s;
    for(auto it = v.crbegin(); it != v.crend(); it++) {
      if(*it == '0') {
        s.push(nullptr);
      } else {
        shared_ptr<BinaryTreeNode<T>> l = s.top(); s.pop();
        shared_ptr<BinaryTreeNode<T>> r = s.top(); s.pop();
        /*
        shared_ptr<BinaryTreeNode<T>> n = 
          make_shared<BinaryTreeNode<T>>(
              BinaryTreeNode<T>{*it, nullptr, l, r, 0});
         */
        shared_ptr<BinaryTreeNode<T>> n = 
          make_shared<BinaryTreeNode<T>>(BinaryTreeNode<T>(*it));
        n->left = l;
        n->right = r;
        s.emplace(n);
      }
    }
    root = s.top();
  }

 protected:
  struct NodeDepth {
    bool balanced;
    int maxDepth;
  };

  /*****************************************************************************
   *  getHead()
   */
  const shared_ptr<BinaryTreeNode<T>> getHead() {
    return root;
  }

  /*****************************************************************************
   *  createBinaryTreeNode()
   */
  shared_ptr<BinaryTreeNode<T>> createBinaryTreeNode(
      vector<T> &v, int &idx, shared_ptr<BinaryTreeNode<T>> parent = nullptr) {
    if (idx >= (int) v.size()) {
      return nullptr;
    }

    /*
     */
    int level = floor(log2(idx+1));
    iLog(level, "Create node [%d]=%d", idx, v[idx]);

    shared_ptr<BinaryTreeNode<T>> node =
      shared_ptr<BinaryTreeNode<T>>(new BinaryTreeNode<T>(v[idx]));

    int leftIdx = idx*2 + 1;
    int rightIdx = idx*2 + 2;

    node->size = 1;
    node->parent = parent;
    node->left = createBinaryTreeNode(v, leftIdx, node);
    node->right = createBinaryTreeNode(v, rightIdx, node);
    if(node->left)
      node->size += node->left->size;
    if(node->right)
    node->size += node->right->size;

    /*
    cout << node->getData() << "-Left:" << node->left << endl;
    cout << node->getData() << "-Right:" << node->right << endl;
     */

    return node;
  }

  /*****************************************************************************
   *  printBinaryTree()
   */
  void printBinaryTree(shared_ptr<BinaryTreeNode<T>> node, int level) {
    if(node == nullptr) {
      return;
    }
    iLog(level, "Node: %d [size=%d]", node->getData(), node->getSize());

    printBinaryTree(node->left, level+1);
    printBinaryTree(node->right, level+1);
  }

  /*****************************************************************************
   *  getNodeDepth()()
   */
  int getNodeDepth(shared_ptr<BinaryTreeNode<T>> node, NodeDepth &depth) {
    if (node == nullptr) {
      return 0;
    }
    int nodeDepth = 1;

    int leftDepth = getNodeDepth(node->left, depth);
    int rightDepth = getNodeDepth(node->right, depth);

    if (abs(leftDepth - rightDepth) > 1) {
      depth.balanced = false;
    }
    nodeDepth += std::max(leftDepth, rightDepth);
    depth.maxDepth = nodeDepth > depth.maxDepth ? nodeDepth : depth.maxDepth;

    return nodeDepth;
  }
};

#endif /* __TREES_H__ */
