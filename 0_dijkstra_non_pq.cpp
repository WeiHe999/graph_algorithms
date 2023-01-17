/*
dmoj: CCC '09 S4 - Shop and Ship
not use priority queue, time complexity O(V**2), applicable to the case where the number of nodes is small, while the number of edges is huge
*/

#include <bits/stdc++.h>
using namespace std;

void dijkstra(int start_node, unordered_map <int, vector<pair<int, int> > > graph, vector <int> &dist, vector <bool> &vis, int n)
{
    for (int a = 0; a < n; a++)
    {
        int min_node, min_dist = INT_MAX;
        for (int x = 1; x <= n; x++)
        {
            if (!vis[x] && dist[x] < min_dist)
            {
                min_dist = dist[x];
                min_node = x;
            }
        }
        vis[min_node] = true;
        for (auto x : graph[min_node]) dist[x.first] = min(dist[min_node] + x.second, dist[x.first]);
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
    vector <bool> vis(n + 1, false);
    dist[d] = 0;
    dijkstra(d, graph, dist, vis, n);
    for (auto x : vec1) s = min(dist[x.first] + x.second, s);
    cout << s << "\n";
}
