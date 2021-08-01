#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// check if child is the same to one of its ancestors
bool check_ancestor(int child, int parent, unordered_map <int, int> &parents)
{
    if (child==parent) return true; //self loop
    int current = parent;
    int steps = 0;
    int max_steps = 1; // 1 for undirected graph, 0 for directed graph
    while(parents[current]!=-1)
    {
        current = parents[current];
        steps++; 
        if (current==child && steps>max_steps) return true;
    }
    return false;
}


bool dfs_loop(unordered_map <int, vector<int> > graph, int start_node, int parent, 
unordered_map <int, int> &parents, vector <int> &visited)
{
    if (find(visited.begin(), visited.end(), start_node) == visited.end())
    {
        visited.emplace_back(start_node);
        parents[start_node] = parent;
        
        for (auto x : graph[start_node])
            {
                if (find(visited.begin(), visited.end(), x) == visited.end()) 
                {
                    if (dfs_loop(graph, x, start_node, parents, visited)) return true;
                }
                else 
                {
                    if(check_ancestor(x, start_node, parents)) return true;
                }
            }
    }
    return false;
}

int main() {
    unordered_map <int, vector <int> > graph = {{1, {2, 3}}, {2, {3}}, {3, {4}}, {4, {2}}};
    int start_node = 1;
    vector<int> visited;
    unordered_map <int, int> parents;
    bool ret = dfs_loop(graph, start_node, -1, parents, visited);
    for (auto x: visited)
    {
        cout << x << ", ";
    }
    cout << endl;
    cout << ret << endl;
}
