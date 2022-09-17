#include <bits/stdc++.h>
using namespace std;

int bfs(unordered_map <int, unordered_set <int> > graph, int start_node, int end_node)
{
    if (start_node == end_node) return 0;
    unordered_set <int> visited;
    visited.insert(start_node);
    unordered_map <int, int> dist;;
    queue <int> q1;
    q1.push(start_node);
    while (!q1.empty())
    {
        int cur_node = q1.front();
        q1.pop();
        for (auto x : graph[cur_node])
        {
            if (!visited.count(x))
            {
                visited.insert(x);
                dist[x] = dist[cur_node] + 1;
                if (x == end_node)
                {
                    return visited.size();
                }
                q1.push(x);
            }
        }

    }
    return visited.size();
}

void dfs(unordered_map <int, unordered_set <int> > graph, int start_node, unordered_set <int> &visited)
{
    if (!visited.count(start_node))
    {
        visited.insert(start_node);
        for (auto x : graph[start_node])
        {
            dfs(graph, x, visited);
        }
    }
}

int main()
{
    cin.tie(0); cout.tie(0); cin.sync_with_stdio(0);
    // tree graph
    unordered_map <int, unordered_set <int> > graph = {{1, {2, 3}}, {2, {1}}, {3, {1, 4, 5}}, {4, {3}}, {5, {3}}};
    // not-a-tree graph
    //unordered_map <int, unordered_set <int> > graph = {{1, {2, 3}}, {2, {1, 4}}, {3, {1, 4}}, {4, {2, 3}}, {5, {6}}, {6, {5}}};

    // 2 conditions: 1) connected, 2) number_edges = num_nodes - 1
    int num_nodes = graph.size();
    int num_edges = 0;
    for (auto x: graph)
    {
        num_edges += x.second.size();
    }
    num_edges = num_edges/2;
    if (num_edges != num_nodes - 1)
    {
        cout << "It is not a tree" << endl;
        return 0;
    }

    // method -1: check if it is connected using BFS
    cout << "checking if the graph is connected using BFS." << endl;
    if (bfs(graph, 1, -1)==graph.size()) cout << "It is a tree" << endl;
    else cout << "It is not a tree" << endl;
    
    //method-2: check if it is connected using DFS
    cout << "checking if the graph is connected using DFS." << endl;
    unordered_set <int> visited;
    dfs(graph, 1, visited);
    if (visited.size()==graph.size()) cout << "It is a tree" << endl;
    else cout << "It is not a tree" << endl;    
    
    
}
