#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;

int bfs(unordered_map <int, vector <int> > graph, int start_node, int end_node)
{
    if (start_node == end_node)
    {
        return 0;
    }
    vector <int> visited;
    unordered_map <int, int> parents = {{start_node, -1}};
    vector <int> list_nodes;
    list_nodes.emplace_back(start_node);
    int current_node;
    while (list_nodes.size() != 0)
    {
        current_node = list_nodes[0];
        list_nodes.erase(list_nodes.begin());
        for (auto x : graph[current_node])
        {
            if (find(visited.begin(), visited.end(), x) == visited.end())
            {
                parents[x] = current_node;
                if (x == end_node)
                {
                    int current = x;
                    int s = 0;
                    while (parents[current] != -1)
                    {
                        s += 1;
                        current = parents[current];
                    }
                    return s;
                }
                visited.emplace_back(x);
                list_nodes.emplace_back(x);
            }
        }
    }
    return -1;
}

int main() {
    unordered_map <int, vector <int> > graph = {{1, {2, 3}}, {2, {3, 4}}, {3, {4}}, {4, {}}};
    int start_node = 1;
    int end_node = 4;
    cout << bfs(graph, start_node, end_node) << endl;
}
