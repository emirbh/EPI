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
        cout << "EPI: ";
        cout << "Production Sequence" << endl;
        vector<string> d;
        readArray(d);
        string s, t;
        cin >> s >> t;
        ProductionSequence ps(d);
        int result = ps.canProduce(s, t);
        cout << "Found sequence " << s << " to " << t << " in " << result;
        cout  << " steps." << endl;
        break;
      }
      /* ---- 03 ------------------------------------------------------------ */
      case 3: {
        /*
         *  @MAYBE
         */
        cout << "EPI: ";
        cout << "Pins and Wires -> Left & Right" << endl;
        int nVertices;
        cin >> nVertices;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        vector<vector<int>> m;
        readMatrix(m);
        Graph<int> g(nVertices);
        for(int i = 0; i < (int) m.size(); i++) {
          g.addEdge(m[i][0], m[i][1]);
        }
        g.print();
        PinsAndWires<int> pnw(g);
        bool aligned = pnw.arePinsLeftAndRight();
        cout << "Pins are aligned = " << aligned << endl;
        break;
      }
      /* ---- 04 ------------------------------------------------------------ */
      case 4: {
        cout << "EPI: ";
        cout << "Degree of Connectedness" << endl;
        int nV;
        cin >> nV;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        vector<vector<int>> m;
        readMatrix(m);
        Graph<int> g(nV);
        for(int i = 0; i < (int) m.size(); i++) {
          g.addEdge(m[i][0], m[i][1]);
        }
        g.print();
        ConnectivityDegree<int> cd(g);
        /*
         *  @TODO still do not know 2V and 2E connectedness (good terms ?)
         */
        bool is2EConnected = cd.is2VerticeConnected();
        cout << "Graph is 2E-connected = " << is2EConnected << endl;
        bool is2VConnected = cd.is2EdgeConnected();
        cout << "Graph is 2V-connected = " << is2VConnected << endl;
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
