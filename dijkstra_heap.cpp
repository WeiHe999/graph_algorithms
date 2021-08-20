#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
using namespace std;


int find_min_node_heap(vector<pair<float, int> > &v_heap)
{
    if (v_heap.size()==0) return -1;
    make_heap(v_heap.begin(), v_heap.end(), [](pair <int, int> a, pair <int, int> b) {return a > b;});
    pop_heap(v_heap.begin(), v_heap.end(), [](pair <int, int> a, pair <int, int> b) {return a > b;});
    int min_node = v_heap.back().second;
    v_heap.pop_back();
    return min_node;
}

float dijkstra(unordered_map <int, unordered_map<int, float> > graph, int start_node, int end_node, 
unordered_map <int, int> &parents, unordered_map <int, float> &costs, vector<pair<float, int> > &v_heap)
{
    vector <int> visited;
    while (true)
    {
        int min_node = find_min_node_heap(v_heap);
        if (min_node == -1) break;
        visited.emplace_back(min_node);
        for (const auto a : graph[min_node])
        {
            float c = costs[min_node] + graph[min_node][a.first];
            if (c < costs[a.first])
            {
                costs[a.first] = c;
                v_heap.push_back({c, a.first});
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
    vector<pair<float, int> > v_heap; //{cost, node}
    for (const auto a : graph)
    {
        if (a.first == start_node) 
        {
            costs[a.first] = 0;
            v_heap.push_back({0, a.first});
        }
        else costs[a.first] = INFINITY;
    }
    unordered_map <int, int> parents = {{start_node, -1}};
    float ans = dijkstra(graph, start_node, end_node, parents, costs, v_heap);
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
