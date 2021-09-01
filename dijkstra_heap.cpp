#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
using namespace std;

int find_min_node(vector <pair <float, int> > &vec_h)
{
    make_heap(vec_h.begin(), vec_h.end(), [](pair <float, int> a, pair <float, int> b) {return a > b;});
    pop_heap(vec_h.begin(), vec_h.end(), [](pair <float, int> a, pair <float, int> b) {return a > b;});
    int min_node = vec_h.back().second;
    vec_h.pop_back();
    return min_node;
}

float dijkstra(unordered_map <int, unordered_map<int, float> > graph, int start_node, int end_node, unordered_map <int, int> &parents, 
               unordered_map <int, float> &costs, vector <pair <float, int> > &vec_h)
{
    vector <int> visited;
    while (true)
    {
        int min_node = find_min_node(vec_h);
        if (min_node == -1) break;
        visited.emplace_back(min_node);
        for (const auto a : graph[min_node])
        {
            float c = costs[min_node] + graph[min_node][a.first];
            if (c < costs[a.first])
            {
                costs[a.first] = c;
                vec_h.push_back({c, a.first});
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
    vector <pair <float, int> > vec_h;
    for (const auto a : graph)
    {
        if (a.first == start_node) {costs[a.first] = 0; vec_h.push_back({0, a.first});}
        else {costs[a.first] = INFINITY; vec_h.push_back({INFINITY, a.first});}
    }
    unordered_map <int, int> parents = {{start_node, -1}};
    float ans = dijkstra(graph, start_node, end_node, parents, costs, vec_h);
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
