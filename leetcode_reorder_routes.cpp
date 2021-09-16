#include <bits/stdc++.h>
using namespace std;

void dfs(int city, int n, vector <pair <int, int> > graph, unordered_map <int, vector <int> > neighbours, vector <int> &visited, int &changes)
{
    for (auto neighbour : neighbours[city])
    {
        if (find(visited.begin(), visited.end(), neighbour) == visited.end())
        {
            visited.emplace_back(neighbour);
            if (find(graph.begin(), graph.end(), make_pair(neighbour, city)) == graph.end()) changes++;
            dfs(neighbour, n, graph, neighbours, visited, changes);
        }
    }
}

int min_reorder(int n, vector <pair <int, int> > graph)
{
    unordered_map <int, vector <int> > neighbours;
    for (int x = 0; x < n; x++) neighbours[x] = {};
    vector <int> visited = {0};
    int changes = 0;
    for (auto a : graph)
    {
        neighbours[a.first].emplace_back(a.second);
        neighbours[a.second].emplace_back(a.first);
    }
    dfs(0, n, graph, neighbours, visited, changes);
    return changes;
}

int main()
{
    cin.sync_with_stdio (0);
    cin.tie (0);
    int n = 6;
    vector <pair <int, int> > graph = {{0, 1}, {1, 3}, {2, 3}, {4, 0}, {4, 5}};
    cout << min_reorder(n, graph) << endl;
}
