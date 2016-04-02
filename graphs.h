#ifndef __GRAPHS_H__
#define __GRAPHS_H__

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <queue>
#include <stack>
#include <unordered_set>
#include <array>

using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;
using std::string;
using std::to_string;
using std::queue;
using std::stack;
using std::ostream;
using std::unordered_set;
using std::hash;
using std::array;
using std::pair;

#include "idebug.h"

/*******************************************************************************
 *  class Graph
 */
template <typename T>
class Graph {
 public:
   Graph(int nVertices) :nVertices(nVertices) {
     adjacencyList.assign(nVertices, vector<T>());
   }

   unsigned int getNumberOfVertices() {
     return nVertices;
   }

   void addEdge(T v, T w) {
     adjacencyList[v].emplace_back(w);
     adjacencyList[w].emplace_back(v);
   }

   vector<T> & getAdjacent(int v) {
     return adjacencyList[v];
   }

   void print() {
     for(int i = 0; i < static_cast<int>(adjacencyList.size()); i++) {
       cout << i << "\t\t";
       printContainer(adjacencyList[i]);
     }
   }

 private:
  int nVertices;
  vector<vector<T>> adjacencyList;
};

/*******************************************************************************
 *  class Maze
 */
template <typename T>
class Maze {
 public:
  struct MazeCell {
    T x, y;

    bool operator==(const MazeCell &that) const {
      return (x == that.x && y == that.y);
    }

    string key() {
      return to_string(x)+":"+to_string(y);
    }
  };

  typedef vector<vector<T>> MazeMatrix;
  typedef vector<MazeCell> MazePath;
  typedef unordered_map<string,bool> VerticeStatus;

  Maze(MazeMatrix &m)
      : m(m) {
  }

  MazePath findPath(MazeCell &start, MazeCell &end) {
    MazePath path;
    /*
    findPathDfsHelper(start, end, path);
     */
    findPathBfsHelper(start, end, path);
    return path;
  }

 private:
  MazeMatrix &m;
  MazePath directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1} };
  VerticeStatus discovered;

  bool findPathDfsHelper(MazeCell &cell, MazeCell &end, MazePath &path) {
    bool found = false;
    discovered[cell.key()] = true;

    iLog(0, "Find [%d:%d]", cell.x, cell.y);

    if(cell == end)
      return true;

    for(int i = 0; i < (int) directions.size(); i++) {
      MazeCell next{cell.x+directions[i].x, cell.y+directions[i].y};
      if(next.x < 0 || next.x >= (int) m.size() ||
         next.y < 0 || next.y >= (int) m[next.x].size())
        continue;
      if(discovered.find(next.key()) != discovered.end()) {
        continue;
      }
      if(!m[cell.x][cell.y])
        return false;

      path.push_back(next);
      found = findPathDfsHelper(next, end, path);
      if(!found)
        path.pop_back();
      else
        return found;
    }

    return found;
  }

  bool findPathBfsHelper(MazeCell &cell, MazeCell &end, MazePath &path) {
    bool found = false;

    unordered_map<string,MazeCell> from;

    queue<MazeCell> q;
    q.push(cell);
    while(!q.empty()) {
      cell = q.front();

      iLog(0, "Find [%d:%d]", cell.x, cell.y);
      discovered[cell.key()] = true;

      if(cell == end) {
        (void) path;
        stack<MazeCell> pathStack;
        pathStack.push(cell);
        auto it = from.find(cell.key());
        while(it != from.end()) {
          string prev = it->first;
          MazeCell preCell = it->second;
          pathStack.push(preCell);
          it = from.find(preCell.key());
        }
        while(!pathStack.empty()) {
          path.push_back(pathStack.top());
          pathStack.pop();
        }
        return true;
      }

      for(int i = 0; i < (int) directions.size(); i++) {
        MazeCell next{cell.x+directions[i].x, cell.y+directions[i].y};
        if(next.x < 0 || next.x >= (int) m.size() ||
           next.y < 0 || next.y >= (int) m[next.x].size())
          continue;
        if(discovered.find(next.key()) != discovered.end()) {
          continue;
        }
        /*
         */
        from[next.key()] = cell;
        if(!m[cell.x][cell.y])
          continue;

        iLog(1, "Add [%d:%d]", next.x, next.y);

        q.push(next);
      }
      q.pop();
    }

    return found;
  }
};

/*******************************************************************************
 *  class ProductionSequence
 */
class ProductionSequence {
 public:
  ProductionSequence(vector<string> dv) {
    for_each(dv.begin(), dv.end(), [this](const string &str) -> void {
        this->d[str] = true;
      });
  }

  int canProduce(string s, string t) {
    int result = -1;
    queue<pair<string,int>> q;
    q.push({s,0});
    while(!q.empty()) {
      pair<string,int> ps = q.front(); q.pop();
      iLog(0, "Check %s (%d)", ps.first.c_str(), ps.second);
      if(ps.first == t) {
        iLog(0, "Found production sequence for %s in %d steps",
             ps.first.c_str(), ps.second);
        return ps.second;
      }

      string str = ps.first;
      for(int i = 0; i < (int) str.size(); i++) {
        for(int j = 0; j < 26; j++) {
          str[i] = 'a' + j;
          /*
          iLog(1, "Vary %s", str.c_str());
           */
          auto it(d.find(str));
          if(it != d.end() && it->second == true) {
            it->second = false;
            q.push({str, ps.second + 1});
            iLog(2, "Add %s", str.c_str());
          }
        }
        str[i] = ps.first[i];
      }
    }
    return result;
  }

 private:
  unordered_map<string,bool> d;
};

/*******************************************************************************
 *  class PinsAndWires
 */
template <typename T>
class PinsAndWires {
 public:
  PinsAndWires(Graph<T> &g) : g(g) {
    marked.assign(g.getNumberOfVertices(), false);
    d.assign(g.getNumberOfVertices(), 0);
  }

  bool arePinsLeftAndRight() {
    for(T i = 0; i < (T) g.getNumberOfVertices(); i++) {
      if(bfsHelper(i) == false) {
        return false;
      }
    }
    return true;
  }

 protected:
  Graph<T> &g;
  vector<bool> marked;
  vector<unsigned int> d;

  bool bfsHelper(T v) {
    if(marked[v])
      return true;
    marked[v] = true;
    queue<T> q;
    for(const T & w : g.getAdjacent(v)) {
      if(!marked[w]) {
        d[w] = d[v]+1;
        q.push(w);
      } else if(d[v] %2 == d[w] %2) {
        iLog(0, "%d and %d on the same side", v, w);
        return false;
      }
    }
    return true;
  }
};

/*******************************************************************************
 *  class ConnectivityDegree
 */
template <typename T>
class ConnectivityDegree {
 public:
  ConnectivityDegree(Graph<T> &g) : g(g) {
    reset();
  }

  bool is2VerticeConnected() {
    reset();
    for(T i = 0; i < (int) g.getNumberOfVertices(); i++) {
      if(dfs2EHelper(i, i) == true) {
        return true;
      }
    }
    return false;
  }

  bool is2EdgeConnected() {
    reset();
    for(T i = 0; i < (int) g.getNumberOfVertices(); i++) {
      if(dfs2VHelper(i, i) == true) {
        return true;
      }
    }
    return true;
  }

 private:
  enum Color {WHITE, GRAY, BLACK};
  Graph<T> &g;
  vector<Color> color;
  vector<int> degree;
  vector<int> time;

  void reset() {
    color.assign(g.getNumberOfVertices(), WHITE);
    degree.assign(g.getNumberOfVertices(), 0);
    time.assign(g.getNumberOfVertices(), 0);
  }

  bool dfs2EHelper(T v, T u, int level=0) {
    if(color[v] == Color::GRAY)
      return false;

    color[v] = Color::GRAY;
    for(const T &w : g.getAdjacent(v)) {
      if(w != u && color[w] != Color::BLACK) {
        return dfs2EHelper(w, v, ++level);
      }
    }
    color[v] = Color::BLACK;
    return false;
  }

  bool dfs2VHelper(T v, T u, int level=0) {
    return true;
  }
};

#endif /* __GRAPHS_H__ */
