#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;


void dfs(unordered_map <int, vector <int> > graph, int start_node, vector <int> &visited, vector <int> g_visited)
{
    if (find(visited.begin(), visited.end(), start_node) == visited.end())
    {
        visited.emplace_back(start_node);
        for (auto x : graph[start_node])
            {
                if (find(g_visited.begin(), g_visited.end(), x) == g_visited.end()) dfs(graph, x, visited, g_visited);
            }
    }
}

int main()
{
    unordered_map <int, vector <int> > graph = {{1, {2}}, {2, {3, 4}}, {3, {}}, {4, {}}, {5, {2, 6}}, {6, {7}}, {7, {}}};
    vector <int> visited;
    vector <int> g_visited;
    int start_node;
    for (auto s : graph)
    {
        start_node = s.first;
        if (find(g_visited.begin(), g_visited.end(), start_node) == g_visited.end()) 
        {
            visited={};
            dfs(graph, start_node, visited, g_visited);
            g_visited.insert(g_visited.begin(), visited.begin(), visited.end());
        }
    }
    for (auto a : g_visited) cout << a << " ";
}
