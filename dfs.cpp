#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

void dfs(int node, unordered_map<int, vector<int> > graph, vector<int> &visited)
{
    if (find(visited.begin(), visited.end(), node)==visited.end())
    {
        visited.push_back(node);
        for (auto x: graph[node]) dfs(x, graph, visited);
    }
    
}


int main()
{
    int num_nodes, num_edges;
    int start, end;
    unordered_map<int, vector<int> > graph;
    
    //initialize the graph
    cin >> num_nodes >> num_edges;
    for (int i=0; i<num_edges; i++)
    {
        cin >> start >> end;
        if (graph.find(start)!=graph.end())
        {
            graph[start].push_back(end);
        }
        else {
            graph[start] = vector<int> {end};
        }
        // to avoid missing leaf nodes
        if (graph.find(end)==graph.end())
        {
            graph[end] = vector<int> {};
        }
        
    }
    //print the graph
    for (auto x: graph)
    {
        cout << "key=" << x.first << endl;
        for (auto y: x.second)
        {
            cout << y << ", ";
        }
        cout << endl;
    }
    
    //dfs
    vector<int> visited = {};
    dfs(3, graph, visited);
    cout << "DFS: " << endl;
    for (auto x: visited) cout << x << ", ";
    cout << endl;

}
