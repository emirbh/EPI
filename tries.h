#ifndef __TRIES_H__
#define __TRIES_H__

#include <memory>
#include <vector>
#include <string>

using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::string;
using std::to_string;

/*******************************************************************************
 *  class Trie
 */
template <typename K, typename V>
class Trie {
 public:
  enum NODE_SEARCH {
    NOT_FOUND = 0,
    VALUE_FOUND,
    TRACE_FOUND
  };

  Trie(int size) : size(size) {
    root = make_shared<TrieNode>(size);
  }

  void add(V value) {
    /*
    iLog(0, "Add %s", value.c_str());
     */
    addNode(root, value, 0, value);
  }

  void add(K key, V value) {
    addNode(root, key, 0, value);
  }

  void print() {
    printNode(root, -1, 0);
  }

  int getValueByKey(K key, V &value, vector<V> &trace) {
    return getNodeValueByKey(root, key, 0, value, trace);
  }


 private:
  /*****************************************************************************
   *  class Trie
   */
  class TrieNode {
   public:
    V value;
    vector<V> trace;
    bool isSet;
    vector<shared_ptr<TrieNode>> nodes;

    TrieNode() : isSet(false) {
    }

    TrieNode(int size) : isSet(false)  {
      nodes.resize(size);
    }

    bool empty() {
      return !isSet;
    }

    void setValue(V value) {
      this->value = value;
      isSet = true;
    }

    V getValue() {
      return value;
    }

    void addPath(V &value) {
      trace.push_back(value);
    }
  };

  int size;
  shared_ptr<TrieNode> root;

  shared_ptr<TrieNode> addNode(shared_ptr<TrieNode> node, K &key,
                               unsigned int idx, V &value) {
    if(idx == key.size()) {
      node->setValue(value);
      return node;
    }

    node->addPath(value);
    int nodeIdx = key[idx] - 'a';
    if(!node->nodes[nodeIdx]) {
      /*
      iLog(idx, "AddNode key=%s idx=%d nodeIdx=%d NEW",
           key.c_str(), idx, nodeIdx);
       */
      node->nodes[nodeIdx] = make_shared<TrieNode>(size);
    } else {
      /*
      iLog(idx, "AddNode key=%s idx=%d nodeIdx=%d",
           key.c_str(), idx, nodeIdx);
       */
    }
    return addNode(node->nodes[nodeIdx], key, idx+1, value);
  }

  int getNodeValueByKey(shared_ptr<TrieNode> node, K key, unsigned int keyIdx,
                         V &value, vector<V> &trace) {
    int ret = NOT_FOUND;

    if(keyIdx == key.size()) {
      if(!node->empty()) {
        iLog(keyIdx, "FOUND: %d:%s -> value=%d",
             keyIdx, key.c_str(), node->getValue());
        value = node->getValue();
        ret = VALUE_FOUND;
      } else {
        iLog(keyIdx, "TRACE: %d:%s -> value=%d",
             keyIdx, key.c_str(), node->getValue());
        trace = node->trace;
        ret = TRACE_FOUND;
      }
      return ret;
    }
    /*
     */

    int childIdx = key[keyIdx] - 'a';
    iLog(keyIdx, "%d:%s -> childIdx=%d", keyIdx, key.c_str(), childIdx);
    if(!node->nodes[childIdx]) {
      if(keyIdx > 0 && node->trace.size() > 0) {
        trace = node->trace;
        ret = TRACE_FOUND;
      }
      return ret;
    }

    return getNodeValueByKey(node->nodes[childIdx], key, keyIdx+1,
                             value, trace);
  }

  void printNode(shared_ptr<TrieNode> node, int keyIdx, int level) {
    if(keyIdx != -1) {
      if(node->empty()) {
        iLog(level, "%c", 'a' + keyIdx);
      } else {
    /*
        iLog(level, "%c -> %s", 'a' + keyIdx, node->getValue().c_str());
     */
        string str = to_string(node->getValue());
        iLog(level, "%c -> %s", 'a' + keyIdx, str.c_str());
      }
    } else {
        iLog(level, "<root>");
    }
    for(int i = 0; i < size; i++) {
      if(!node->nodes[i]) { continue; }
      printNode(node->nodes[i], i, level+1);
    }
  }
};

#endif /* __TRIES_H__ */
