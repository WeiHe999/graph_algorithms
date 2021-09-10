/*
input:
0100
1110
0100
1100
*/


#include <bits/stdc++.h>
using namespace std;

int dfs(vector <vector <int> > graph, int i, int j, vector <pair <int, int> > visited)
{
    if (i >= graph.size() || j >= graph[0].size() || i < 0 || j < 0 || graph[i][j] == 0) return 1;
    for (auto a : visited) if (a.first == i && a.second == j) return 0;
    visited.push_back({i, j});
    return dfs(graph, i, j + 1, visited) + dfs(graph, i, j - 1, visited) + dfs(graph, i + 1, j, visited) + dfs(graph, i - 1, j, visited);
}

int main()
{
    vector <vector <int> > graph;
    vector <int> tmp;
    string line;
    int rows = 4, cols = 4;
    for (int x = 0; x < rows; x++)
    {
        getline(cin, line);
        tmp = {};
        for (int a = 0; a < cols; a++) {tmp.emplace_back(line[a]-'0');}
        graph.push_back(tmp);
    }
    vector <pair <int, int> > visited;
    int test = 0;
    for (int b = 0; b < rows; b++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (graph[b][c] == 1) {cout << dfs(graph, b, c, visited) << endl; test = 1; break;}
        }
        if (test == 1) break;
    }
}
