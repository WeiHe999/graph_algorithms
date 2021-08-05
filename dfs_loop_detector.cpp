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

int main()
{
    unordered_map <int, vector <int> > graph = {{1, {2}}, {2, {3, 4}}, {3, {}}, {4, {}}, {5, {2, 6}}, {6, {7}}, {7, {}}};
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
                cout << "There is a loop." << endl;
                return 0;
            }
            
            g_visited.insert(g_visited.end(), visited.begin(), visited.end());
        }
    }
    cout << "There is no loop." << endl;
}
