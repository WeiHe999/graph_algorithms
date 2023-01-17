/*
dmoj: CCC '09 S4 - Shop and Ship
*/

#include <bits/stdc++.h>
using namespace std;

void dijkstra(int start_node, unordered_map <int, vector<pair<int, int> > > &graph, vector <int> &dist)
{
    priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > q1;
    q1.push({0, start_node});
    while (!q1.empty())
    {
        pair <int, int> cur_node = q1.top();
        q1.pop();
        for (auto x : graph[cur_node.second])
        {
            if (cur_node.first + x.second < dist[x.first])
            {
                dist[x.first] = cur_node.first + x.second;
                q1.push({dist[x.first], x.first});
            }
        }
    }
}

int main()
{
    cin.tie(0); cout.tie(0); cin.sync_with_stdio(0);
    int n, t, a, b, c, k, d, s = INT_MAX;
    cin >> n >> t;
    unordered_map <int, vector<pair<int, int> > > graph;
    for (int x = 0; x < t; x++)
    {
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
        graph[b].push_back({a, c});
    }
    cin >> k;
    vector <pair <int, int> > vec1;
    for (int x = 0; x < k; x++)
    {
        cin >> a >> b;
        vec1.push_back({a, b});
    }
    cin >> d;
    vector <int> dist(n + 1, INT_MAX);
    dist[d] = 0;
    dijkstra(d, graph, dist);
    for (auto x : vec1) s = min(dist[x.first] + x.second, s);
    cout << s << "\n";
}
