/*
dmoj problem: Graph Contest 3 P2 - Shortest Path 
*/

#include <bits/stdc++.h>
using namespace std;

void spfa(int start_node, unordered_map <int, vector <pair <int, int> > > &graph, vector <int> &dist, vector <bool> &inq)
{
    dist[start_node] = 0;
    queue <int> q1;
    q1.push(start_node);
    inq[start_node] = true;
    while (!q1.empty())
    {
        int cur_node = q1.front();
        q1.pop();
        inq[cur_node] = false;
        for (auto x : graph[cur_node])
        {
            if (dist[cur_node] + x.second < dist[x.first])
            {
                dist[x.first] = dist[cur_node] + x.second;
                if (!inq[x.first])
                {
                    q1.push(x.first);
                    inq[x.first] = true;
                }
            }
        }
    }
}

const int MM = 1e9;

int main()
{
    cin.tie(0); cout.tie(0); cin.sync_with_stdio(0);
    int n, m, a, b, c;
    cin >> n >> m;
    unordered_map <int, vector <pair <int, int> > > graph;
    for (int x = 0; x < m; x++)
    {
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
    }
    vector <int> dist(n + 1, MM);
    vector <bool> inq(n + 1, false);
    spfa(1, graph, dist, inq);
    cout << dist[n] << "\n";
}
