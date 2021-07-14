#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
void dfs(unordered_map <int, vector<int> > graph, int start_node, vector <int> &visited)
{
    if (find(visited.begin(), visited.end(), start_node) == visited.end())
    {
        visited.emplace_back(start_node);
        for (auto x : graph[start_node])
            {
                dfs(graph, x, visited);
            }
    }
}

int main()
{
    int num_nodes, num_edges;
    cin >> num_nodes >> num_edges;
    unordered_map <int, vector<int> > graph;
    for (int x = 0; x < num_edges; x++)
    {
        int start, end;
        cin >> start >> end;
        graph[start].emplace_back(end);
        if (graph.find(end) == graph.end())
        {
            graph[end] = vector <int> {};
        }
    }
    
    //print the graph
    for (auto a : graph)
    {
        cout << a.first << ": ";
        for (auto b : graph[a.first])
        {
            cout << b << " ";
        }
        cout << endl;
    }
    
    vector <int> visited;
    dfs(graph, 1, visited);
    for (auto c : visited)
    {
        cout << c << " ";
    }
}
