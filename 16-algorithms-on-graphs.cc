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
      /* ---- 03 ------------------------------------------------------------ */
      case 3: {
        /*
         *  @POTENTIALLY
         */
        cout << "EPI: ";
        cout << "Pins and Wires ->Lft & Right" << endl;
        vector<vector<int>> m;
        readMatrix(m);
        break;
      }
      /* ---- 04 ------------------------------------------------------------ */
      case 4: {
        /*
         *  @TODO Understand this, potentially implement
         */
        cout << "EPI: ";
        cout << "Strongly connected ?" << endl;
        vector<vector<int>> m;
        readMatrix(m);
        break;
      }
      /* ---- 11 ------------------------------------------------------------ */
      case 11: {
        /*
         *  @TODO Learn Floyd-Warshall algorithm for all nodes shortest path
         */
        cout << "EPI: ";
        cout << "Strongly connected ?" << endl;
        vector<vector<int>> m;
        readMatrix(m);
        break;
      }
      default: {
        break;
      }
    }

    cin >> part;
  }
}
