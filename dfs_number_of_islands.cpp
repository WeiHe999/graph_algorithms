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
#include <unordered_map>
#include <algorithm>
using namespace std;


void dfs(vector< vector<int> > graph, vector <pair<int, int> > &visited, pair<int, int> start_node, int rows, int cols)
{
    if (find(visited.begin(), visited.end(), start_node) == visited.end())
    {
        visited.emplace_back(start_node);
        // find the neighbors
        int x = start_node.first;
        int y = start_node.second;
        vector <pair<int, int> > neighbors = {{x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1}};
        for (auto a : neighbors)
        {
            if (a.first>=cols || a.second>=rows || a.first<0 || a.second<0) continue;
            if (graph[a.first][a.second]==0) continue;
            // dfs on neighbor
            dfs(graph, visited, a, rows, cols);
        }
    }
}

int main()
{
    int rows, cols;
    cin >> rows >> cols;
    cin.ignore();
    
    vector< vector<int> > graph;
    string line;
    for (int i = 0; i < rows; i++)
    {
        getline(cin, line);
        vector<int> row_vec;
        for(int j=0; j<line.size(); j++)
        {
            if(line[j]=='+') row_vec.push_back(1);
            else if (line[j]=='-') row_vec.push_back(0);
            else continue;
        }
        graph.push_back(row_vec);

    }
    
    //print the graph
    cout << "Grid matrix:" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
    
    // dfs
    vector <pair<int, int> > global_visited = {};
    vector <pair<int, int> > local_visited = {};
    int cnt = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            pair<int, int> s = {i, j};
            if (graph[i][j]==1 && find(global_visited.begin(), global_visited.end(), s) == global_visited.end())
            {
                cnt ++;
                local_visited = {};
                dfs(graph, local_visited, s, rows, cols);
                global_visited.insert(global_visited.end(), local_visited.begin(), local_visited.end() );
            }
            
        }
    }

    // for (auto x: global_visited)
    // {
    //     cout << x.first << ", " << x.second << endl;
    // }
    cout << "The number of islands is: " << cnt << endl;

}
