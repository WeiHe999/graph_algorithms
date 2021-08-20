#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
using namespace std;

int find_min_node(unordered_map <int, float> costs, vector <int> visited)
{
    int minimum_node = -1;
    float minimum_cost = INFINITY;
    for (const auto x : costs)
    {
        if (find(visited.begin(), visited.end(), x.first) == visited.end() && costs[x.first] < minimum_cost)
        {
            minimum_node = x.first;
            minimum_cost = costs[x.first];
        }
    }
    return minimum_node;
}

float dijkstra(unordered_map <int, unordered_map<int, float> > graph, int start_node, int end_node, unordered_map <int, int> &parents, unordered_map <int, float> &costs)
{
    vector <int> visited;
    while (true)
    {
        int min_node = find_min_node(costs, visited);
        if (min_node == -1) break;
        visited.emplace_back(min_node);
        for (const auto a : graph[min_node])
        {
            float c = costs[min_node] + graph[min_node][a.first];
            if (c < costs[a.first])
            {
                costs[a.first] = c;
                parents[a.first] = min_node;
            }
        }
    }
    return costs[end_node];
}

int main()
{
    
    unordered_map <int, unordered_map<int, float> > graph;
    graph[1] = {{2, 3}, {3, 2}};
    graph[2] = {{3, 1}, {4, 5}};
    graph[3] = {{4, 1}};
    graph[4] = {};
    int start_node = 1;
    int end_node = 4;
    unordered_map <int, float> costs;
    for (const auto a : graph)
    {
        if (a.first == start_node) costs[a.first] = 0;
        else costs[a.first] = INFINITY;
    }
    unordered_map <int, int> parents = {{start_node, -1}};
    float ans = dijkstra(graph, start_node, end_node, parents, costs);
    cout << ans << endl;
    int current = end_node;
    vector <int> vec1;
    while (current != -1)
    {
        vec1.insert(vec1.begin(), current);
        current = parents[current];
    }
    for (auto a : vec1)
    {
        cout << a << " ";
    }
    cout << endl;
}
