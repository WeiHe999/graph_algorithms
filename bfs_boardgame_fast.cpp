// 4 6
#include <bits/stdc++.h>
using namespace std;

int bfs(int start_node, int end_node, unordered_map <int, int> &visited)
{
    if (start_node == end_node)
    {
        return 0;
    }
    vector <int> list_nodes;
    list_nodes.emplace_back(start_node);
    int current_node;
    vector <int> vec_loop;
    unordered_map <int, int> parents;
    while (list_nodes.size() != 0)
    {
        current_node = list_nodes[0];
        visited[current_node] = 1;
        list_nodes.erase(list_nodes.begin());
        vec_loop = {current_node * 3, current_node - 1, current_node - 3};
        visited[current_node * 3] = 0;
        visited[current_node - 1] = 0;
        visited[current_node - 3] = 0;
        if (current_node % 2 == 0) {vec_loop.emplace_back(current_node / 2); visited[current_node / 2] = 0;}
        for (auto a : vec_loop)
        {
            if (visited[a] != 1)
            {
                parents[a] = current_node;
                if (a == end_node)
                {
                    int current = a;
                    int s = 0;
                    while (parents[current] != start_node)
                    {
                        s += 1;
                        current = parents[current];
                    }
                    return s+1;
                }
                list_nodes.emplace_back(a);
            }
        }
    }
    return -1;
}

int main() {
    cin.sync_with_stdio (0);
    cin.tie (0);
    int start_node, end_node;
    cin >> start_node >> end_node;
    unordered_map <int, int> visited = {{start_node, 0}, {end_node, 0}};
    int steps = bfs(start_node, end_node, visited);
    cout << steps << endl;
}
