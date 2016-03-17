#include <iostream>
#include <limits>

using std::cin;
using std::cout;
using std::endl;

#include "idebug.h"
#include "graphs.h"

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
        cout << "Maze" << endl;
        vector<vector<int>> m;
        readMatrix(m);
        Maze<int> maze(m);
        Maze<int>::MazeCell start{0, 0};
        Maze<int>::MazeCell end{(int) m.size()-1, (int) m[m.size()-1].size()-1};
        Maze<int>::MazePath path = maze.findPath(start, end);
        cout << "Path found = " << (path.size() > 0) << endl;
        for_each(path.begin(), path.end(), [](const Maze<int>::MazeCell &p) ->
          void {
            cout << p.x << ":" << p.y << endl;
          });
        break;
      }
      /* ---- 02 ------------------------------------------------------------ */
      case 2: {
        break;
      }
      /* ---- 41 ------------------------------------------------------------ */
      case 41: {
        cout << "EPI: ";
        cout << "Graph Basics" << endl;
        vector<int> v;
        readArray(v);
        Graph<OneDCoor>::Edges edges;
        for(int i = 0; i < (int) v.size(); i += 2) {
          Graph<OneDCoor>::EdgeVertices ev{{v[i], v[i+1]}};
          edges.push_back(ev);
        }
        Graph<OneDCoor> g(edges);
        g.print();
        break;
      }
      default: {
        break;
      }
    }

    cin >> part;
  }
}
