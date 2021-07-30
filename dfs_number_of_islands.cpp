/*
note: + represents land, - represent sea
input
6 6
+++---
++--++
--+--+
--++--
----+-
----++
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void dfs(vector <vector <int> > graph, pair <int, int> start_node, vector <pair <int, int> > &visited, int rows, int cols)
{
    if (find(visited.begin(), visited.end(), start_node) == visited.end())
    {
        visited.push_back(start_node);
        int x = start_node.first;
        int y = start_node.second;
        vector <pair <int, int> > neighbours = {{x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1}};
        for (auto a : neighbours)
        {
            
            if (a.first < 0 || a.second < 0 || a.first >= rows || a.second >= cols) continue;
            if (graph[a.first][a.second] == 0) continue;
            dfs(graph, a, visited, rows, cols);
        }
    }
}

int main()
{
    int rows, cols;
    cin >> rows >> cols;
    cin.ignore();
    vector <vector <int> > graph;
    vector <int> tmp;
    string line;
    for (int x = 0; x < rows; x++)
    {
        getline(cin, line);
        tmp = {};
        for (int a = 0; a < cols; a++)
        {
            if (line[a] == '-') tmp.push_back(0);
            if (line[a] == '+') tmp.push_back(1);
        }
        graph.push_back(tmp);
    }
    // cout << "Matrix:" << endl;
    // for (auto b : graph)
    // {
    //     for (auto c : b)
    //     {
    //         cout << c << " ";
    //     }
    //     cout << endl;
    // }
    vector <pair <int, int> > global_visited;
    vector <pair <int, int> > visited;
    int s = 0;
    pair <int, int> p;
    for (int b = 0; b < rows; b++)
    {
        for (int c = 0; c < cols; c++)
        {
            p = {b, c};
            if (graph[b][c] == 0 || find(global_visited.begin(), global_visited.end(), p) != global_visited.end()) continue;
            dfs(graph, p, visited, rows, cols);
            global_visited.insert(global_visited.end(), visited.begin(), visited.end());
            visited = {};
            s++;
        }
    }
    cout << s << endl;
}
