#include <bits/stdc++.h>
using namespace std;

pair <int, int> find_min_node(vector < vector <int> > &vec_h)
{
    make_heap(vec_h.begin(), vec_h.end(), [](vector <int> a, vector <int> b) {return a > b;});
    pop_heap(vec_h.begin(), vec_h.end(), [](vector <int> a, vector <int> b) {return a > b;});
    int min_node = vec_h.back()[1];
    int min_steps = vec_h.back()[2];
    vec_h.pop_back();
    return {min_node, min_steps};
}

int dijkstra(unordered_map <int, unordered_map<int, int> > graph, int start_node, int end_node,
unordered_map <int, int> &parents, unordered_map <int, unordered_map <int, int> > &costs, vector <vector <int> > &vec_h, int max_steps)
{
    vector <int> visited;
    
    while (true)
    {
        pair <int, int> p1 = find_min_node(vec_h);
        int min_node = p1.first;
        int min_steps = p1.second;
        if (min_node == end_node)
        {
            return costs[end_node][min_steps];
        }
        visited.emplace_back(min_node);
        for (const auto a : graph[min_node])
        {
            int c = costs[min_node][min_steps] + graph[min_node][a.first];
            int steps = min_steps + 1;
            if (steps <= max_steps)
            {
                costs[a.first][steps] = c;
                vec_h.push_back({c, a.first, steps});
                parents[a.first] = min_node;
            }
        }
    }
}

int main()
{
    
    unordered_map <int, unordered_map<int, int> > graph;
    graph[1] = {{2, 10}, {4, 5}, {3, 20}};
    graph[2] = {{3, 1}, {4, 3}};
    graph[3] = {{5, 4}};
    graph[4] = {{2, 3}, {5, 2}, {3, 9}};
    graph[5] = {{1, 7}, {3, 6}};
    int k = 0;
    int max_steps = k + 1;
    int start_node = 1;
    int end_node = 3;
    unordered_map <int, unordered_map <int, int> > costs;
    vector <vector <int> > vec_h;
    for (const auto a : graph)
    {
        if (a.first == start_node) {costs[a.first][0] = 0; vec_h.push_back({0, a.first, 0});}
        else {costs[a.first][1] = INT_MAX; vec_h.push_back({INT_MAX, a.first, 1});}
    }
    unordered_map <int, int> parents = {{start_node, -1}};
    float ans = dijkstra(graph, start_node, end_node, parents, costs, vec_h, max_steps);
    cout << ans << endl;
}
