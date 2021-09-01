#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

int find_min_node(vector < vector <int> > &vec_h)
{
    make_heap(vec_h.begin(), vec_h.end(), [](vector <int> a, vector <int> b) {return a > b;});
    pop_heap(vec_h.begin(), vec_h.end(), [](vector <int> a, vector <int> b) {return a > b;});
    int min_node = vec_h.back()[1];
    vec_h.pop_back();
    return min_node;
}

int dijkstra(unordered_map <int, unordered_map<int, int> > graph, int start_node, int end_node,
unordered_map <int, int> &parents, unordered_map <int, pair <int, int> > &costs, vector <vector <int> > &vec_h, int max_steps)
{
    vector <int> visited;
    while (true)
    {
        int min_node = find_min_node(vec_h);
        cout << "min node:" << min_node << endl;
        if (min_node == end_node) return costs[min_node].first;
        visited.emplace_back(min_node);
        for (const auto a : graph[min_node])
        {
            cout << "neighbor: " << a.first << endl;
            int c = costs[min_node].first + graph[min_node][a.first];
            int steps = costs[min_node].second + 1;
            if (c < costs[a.first].first && steps<=max_steps)
            {
                costs[a.first].first = c;
                costs[a.first].second = steps;
                vec_h.push_back({c, a.first, steps});
                parents[a.first] = min_node;
            }
        }
    }
    return costs[end_node].first;
}

int main()
{
    
    unordered_map <int, unordered_map<int, int> > graph;
    graph[1] = {{2, 10}, {4, 5}};
    graph[2] = {{3, 1}, {4, 3}};
    graph[3] = {{5, 4}};
    graph[4] = {{2, 2}, {5, 2}};
    graph[4] = {{1, 7}, {3, 6}};
    int k = 1;
    int max_steps = k+1;
    int start_node = 1;
    int end_node = 3;
    unordered_map <int, pair <int, int> > costs;
    vector <vector <int> > vec_h;
    for (const auto a : graph)
    {
        if (a.first == start_node) {costs[a.first] = {0, 0}; vec_h.push_back({0, a.first, 0});}
        else {costs[a.first] = {INT_MAX, 1}; vec_h.push_back({INT_MAX, a.first, 1});}
    }
    unordered_map <int, int> parents = {{start_node, -1}};
    float ans = dijkstra(graph, start_node, end_node, parents, costs, vec_h, max_steps);
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
