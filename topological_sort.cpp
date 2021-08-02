/*
Topological sort works on Directed Acyclic Graph (DAG).
If the graph contains loops, topological sort fails.
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;


void dfs(unordered_map <int, vector<int> > graph, int start_node, vector <int> &visited, vector <int> &global_visited)
{
    if (find(visited.begin(), visited.end(), start_node) == visited.end() && 
    find(global_visited.begin(), global_visited.end(), start_node) == global_visited.end())
    {
        visited.emplace_back(start_node);
        for (auto x : graph[start_node])
            {
                dfs(graph, x, visited, global_visited);
            }
    }
}

int main() {
    unordered_map <int, vector <int> > graph = {{1, {4}}, {2, {4}}, {3, {1, 2}}, {4, {}}, {5, {1, 4}}};
    vector<int> global_visited, visited;
    for (auto x: graph)
    {
        if (find(global_visited.begin(), global_visited.end(), x.first)==global_visited.end())
        {
            visited = {};
            dfs(graph, x.first, visited, global_visited);
            //insert vector visited into global_visited from front
            global_visited.insert(global_visited.begin(), visited.begin(), visited.end());
        }
    }

    for (auto x: global_visited)
    {
        cout << x << ", ";
    }
    cout << endl;
}
