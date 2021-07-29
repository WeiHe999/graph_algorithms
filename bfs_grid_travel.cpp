/*
note: S represents start point, E represents end point, # represent a wall, _ represent a floor
input:
5 5
S_#__
___#_
#___E
__#__
#____
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

int bfs(vector <vector <int > > graph, pair <int, int> start_node, pair <int, int> end_node, int rows, int cols)
{
    if (start_node == end_node)
    {
        return 0;
    }
    vector <pair <int, int> > visited;
    map <pair <int, int>, pair <int, int> > parents = {{start_node, {-1, -1}}};
    vector <pair <int, int> > list_nodes;
    list_nodes.emplace_back(start_node);
    pair <int, int> current_node;
    vector <pair <int, int> > vec_loop;
    int x;
    int y;
    while (list_nodes.size() != 0)
    {
        current_node = list_nodes[0];
        list_nodes.erase(list_nodes.begin());
        x = current_node.first;
        y = current_node.second;
        vec_loop = {{x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1}};
        for (auto a : vec_loop)
        {
            if (a.first>=cols || a.second>=rows || a.first<0 || a.second<0) continue;
	    // if it is a wall
            if (graph[a.first][a.second]==1) continue;
            
            if (find(visited.begin(), visited.end(), a) == visited.end())
            {
                parents[a] = current_node;
                if (a == end_node)
                {
                    pair <int, int> current = a;
                    int s = 0;
                    while (parents[current]!=start_node)
                    {
                        s += 1;
                        current = parents[current];
                    }
                    return s+1;
                }
                visited.emplace_back(a);
                list_nodes.emplace_back(a);
            }
        }
    }
    return -1;
}

int main() {
    cin.sync_with_stdio (0);
    cin.tie (0);
    int rows, cols;
    cin >> rows >> cols;
    cin.ignore();
    vector <vector <int > > graph;
    pair <int, int> start_node;
    pair <int, int> end_node;
    for (int x = 0; x < rows; x++)
    {
        string line;
        getline(cin, line);
        vector<int> tmp;
        for (int a = 0; a < line.length(); a++)
        {
            if (line[a] == '#') tmp.push_back(1);//wall is 1
            else if (line[a] == 'S') 
            {
                start_node = {x, a};
                tmp.push_back(0);
            
            }
            else if (line[a] == 'E') 
            {
                end_node = {x, a};
                tmp.push_back(0);
            
            }
            else if (line[a] == '_') tmp.push_back(0);
            else continue;
        }
        graph.push_back(tmp);
    }
  cout << "start node: " << start_node.first << ", " << start_node.second << endl;
  cout << "end node: "<< end_node.first << ", " << end_node.second << endl;
  cout << "grid matrix: " << endl;
	for(int i=0; i<rows; i++)
	{
	    for(int j=0; j<cols; j++) cout << graph[i][j] << " ";
	    cout << endl;
	}
  int steps = bfs(graph, start_node, end_node, rows, cols);
  if (steps==-1) cout << "end node is not reachable from the start node." << endl;
  else cout << "The minimal number of steps from start node to end node is " << steps << endl;
}
