/*
input:
6
2 1
3 1
4 2
4 3
5 3
2 6
6 4
0 0
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

bool check_ancestor(int a, int start_node, unordered_map <int, int> parents)
{
    int current = start_node;
    while (current != -1)
    {
        if (a == current) return true;
        current = parents[current];
    }
    return false;
}

bool dfs_check_loop(int start_node, int parent, unordered_map <int, int> &parents, vector <int> &visited, unordered_map <int, vector <int> > graph)
{
    if (find(visited.begin(), visited.end(), start_node) == visited.end())
    {
        visited.emplace_back(start_node);
        parents[start_node] = parent;
        vector <int> list_children = graph[start_node];
        
        for (auto a : list_children)
        {
            //detect if there is a loop for the subnet rooted at a
            if (find(visited.begin(), visited.end(), a) == visited.end())
            {
                bool ret_value = dfs_check_loop(a, start_node, parents, visited, graph);
                if (ret_value == true) return true;
            }
            else
            {
                //if a has been visited, check if a is an ancestor of start_node
                if (check_ancestor(a, start_node, parents) == true) return true;
                
            }
        }
    }
    return false;
}


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
    unordered_map <int, vector <int> > graph;
    int n;
    cin >> n;
    int c, d;
    while (true)
    {
        cin >> c >> d;
        if (c == 0 && d == 0) break;
        if (graph.find(d) == graph.end()) graph[d] = {};
        graph[d].emplace_back(c);
    }
    vector <int> visited;
    vector <int> g_visited;
    unordered_map <int, int> parents;
    int start_node;
    int parent;
    bool b;
    for (auto s : graph)
    {
        start_node = s.first;
        parent = -1;
        if (find(g_visited.begin(), g_visited.end(), start_node) == g_visited.end()) 
        {
            visited={};
            parents = {};
            if (dfs_check_loop(start_node, parent, parents, visited, graph) == true)
            {
                cout << "You can not finish all courses" << endl;
                return 0;
            }
            g_visited.insert(g_visited.end(), visited.begin(), visited.end());
        }
    }
    cout << "You can finish all courses in the order of" << endl;
    g_visited = {};
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
