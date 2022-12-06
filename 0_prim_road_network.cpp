// problem is from DMOJ: Road Network

#include <bits/stdc++.h>
using namespace std;

long long distance(long long x1, long long y1, long long x2, long long y2)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}


// node_id from 1 to n
double prim(unordered_map <long long, unordered_map<long long, long long> > &graph, int n)
{
    // PRIM for MST
    vector<long long> dist(n+1, LLONG_MAX), parents(n+1, -1);
    vector<bool> vis(n+1);
    double tot_dist = 0;
    priority_queue<pair<long long, long long> > min_q; //min_queue={dist, node_id}
    // push the first node
    dist[1] = 0;
    min_q.push({0, 1});
    while(!min_q.empty())
    {
        pair<long long, long long> min_n = min_q.top();
        long long cur_node = min_n.second;
        min_q.pop();
        if (vis[cur_node]) continue;
        vis[cur_node] = true;
        for (auto x: graph[min_n.second])
        {
            long long child_node = x.first;
            if ((!vis[child_node]) && (graph[cur_node][child_node] < dist[child_node]))
            {
                // update dist and parents
                dist[child_node] = graph[cur_node][child_node];
                parents[child_node] = cur_node;
                // push into queue
                min_q.push({-1*graph[cur_node][child_node], child_node});
            }
        }
    }
    for (int i=1; i<=n; i++) 
    {
        tot_dist += sqrt(dist[i]);
    }
    
    // print the edges inn MST
    // cout << "The edges in MST:" << endl;
    // for (int i=1; i<=n; i++)
    // {
    //     if (parents[i] >=0) cout << parents[i] << "-->" << i << endl;
    // }
    
    return tot_dist;
    
}


int main()
{
    cin.tie(0); cout.tie(0); cin.sync_with_stdio(0);
    long long n, m, a, b;
    cin >> n >> m;
    unordered_map <long long, pair <long long, long long> > m1;
    unordered_map <long long, unordered_map<long long, long long> > graph;//{start_node: {end_node: dist}}
    for (long long x = 1; x <= n; x++)
    {
        cin >> a >> b;
        m1[x] = {a, b};
    }
    // completely connected graph
    for (long long x = 1; x <= n; x++)
    {
        for (long long y = x+1; y <= n; y++)
        {
            long long d = distance(m1[x].first, m1[x].second, m1[y].first, m1[y].second);
            graph[x][y] = d;
            graph[y][x] = d;
        }
    }
    // set the cost for the existing edges to 0
    for (long long x = 0; x < m; x++)
    {
        cin >> a >> b;
        graph[a][b] = 0;
        graph[b][a] = 0;
    }
    
    // PRIM for MST
    double ans = prim(graph, n);

 
    cout << fixed << setprecision(2) << ans << "\n";
}
