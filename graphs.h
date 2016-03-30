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

/*******************************************************************************
 *  class PinsAndWires
 */
template <typename T>
class PinsAndWires {
 public:
  PinsAndWires(vector<vector<T>> &m) : m(m) {
    initialize();
  }

 protected:
  struct Vertex {
    int d;
    T data;
    vector<Vertex *> edges;
  };

  vector<vector<T>> &m;

  void initialize() {
    /*
    unordered_map<T,
    for(int i = 0; i < (int) m.size(); i++) {
      T id1 = m[i][0];
      T id2 = m[i][1];

      Vertex *v1 = new Vertex{-1, id1, new vector<Vertex *>()};
    }
     */
  }
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
 *  class ConnectivityDegree
 */

#endif /* __GRAPHS_H__ */
