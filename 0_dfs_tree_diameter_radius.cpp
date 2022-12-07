/*
program to find the diameter, diameter endpoints, radius, center for a tree

input:
5 4
1 2 4
2 4 2
2 5 3
1 3 6

Output put:
The tree diameter length is: 13
The two diameter endpoints are: 5, 3
The tree radius length is: 7
The tree center is: 1
*/


#include <bits/stdc++.h>
using namespace std;

template < typename T > void print (T t)
{
    for (const auto & e:t) cout << e << " ";
    cout << endl;
}

void dfs(unordered_map <int, vector <pair <int, int> > > &graph, vector <bool> &vis,
vector <bool> &global_vis, vector <int> &dist, int cur_node, unordered_map <int, int> &parents, int &max_dist, int &max_node)
{
    vis[cur_node] = true;
    global_vis[cur_node] = true;
    for (auto x : graph[cur_node])
    {
        if (!vis[x.first])
        {
            dist[x.first] = dist[cur_node] + x.second;
            if (dist[x.first] > max_dist)
            {
                max_dist = dist[x.first];
                max_node = x.first;
            }
            parents[x.first] = cur_node;
            dfs(graph, vis, global_vis, dist, x.first, parents, max_dist, max_node);
        }
    }
}


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
        graph[b].push_back({a, c});
        
    }
    
    // global visited vector, dealing with graph with multiple components
    vector <bool> global_vis(n + 1, false);
    
    //step-1: find one of the diameter endpoints
    vector <bool> vis1(n + 1, false);
    vector <int> dist1(n + 1);
    int start_node = 1;
    int max_node1 = start_node, max_dist1 = 0;
    unordered_map <int, int> par1={{start_node, -1}};
    dfs(graph, vis1, global_vis, dist1, start_node, par1, max_dist1, max_node1);
    
    // step-2: find the diameter
    vector <bool> vis2(n + 1, false);
    vector <int> dist2(n + 1);
    start_node = max_node1;
    int max_node2 = start_node, max_dist2 = 0;
    unordered_map <int, int> par2 = {{start_node, -1}};
    dfs(graph, vis2, global_vis, dist2, start_node, par2, max_dist2, max_node2);
    int dia = max_dist2;
    cout << "The tree diameter length is: " << dia << endl;
    cout << "The two diameter endpoints are: " << start_node << ", " << max_node2 << endl;
    
    // step-3: find radius and tree center
    int cur = max_node2, rad = INT_MAX, center_node = -1;
    while (cur != -1)
    {
        int max_d = max(dist2[cur], dia - dist2[cur]);
        if (max_d < rad)
        {
            rad = max_d;
            center_node = cur;
        }
        cur = par2[cur];
    }
    cout << "The tree radius length is: " << rad << endl;
    cout << "The tree center is: " << center_node << endl;           
    
}

