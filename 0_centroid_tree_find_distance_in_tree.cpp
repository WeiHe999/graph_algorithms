/*
input
11
0 1 3
0 2 4
2 3 5
3 4 4
4 5 6
0 6 3
6 7 2
6 8 5
8 9 6
8 10 7

*/

#include <bits/stdc++.h>
using namespace std;

template < typename T > void print (T t)
{
    for (const auto & e:t) cout << e << " ";
    cout << "\n";
}

const int MM = 1e1 + 3;
int n, k, a, b, c, centroid, q, a1, a2;
vector <vector <pair <int, int> > > graph(MM);
vector <int> size1(MM);
vector <bool> removed(MM, false);
vector <vector <int> > g_dist(log2(MM) + 1, vector <int>(MM)), g_centroid(log2(MM) + 1, vector <int>(MM, -1));

void dfs1(int cur, int prev)
{
    size1[cur] = 1;
    for (auto x : graph[cur])
    {
        if (x.first == prev || removed[x.first]) continue;
        dfs1(x.first, cur);
        size1[cur] += size1[x.first];
    }
}

void dfs2(int cur, int prev, int t_size)
{
    bool flag = true;
    for (auto x : graph[cur])
    {
        if (x.first == prev || removed[x.first]) continue;
        if (size1[x.first] > (t_size / 2))
        {
            dfs2(x.first, cur, t_size);
            flag = false;
        }
    }
    if (flag)
    {
        centroid = cur;
        removed[centroid] = true;
    }
}

void dfs3(int cur, int prev, int level)
{
    g_centroid[level][cur] = centroid;
    for (auto x : graph[cur])
    {
        if (x.first == prev || removed[x.first]) continue;
        g_dist[level][x.first] = g_dist[level][cur] + x.second;
        dfs3(x.first, cur, level);
    }
}

void dfs4(int cur, int level)
{
    dfs1(cur, -1);
    centroid = -1;
    dfs2(cur, -1, size1[cur]);
    dfs3(centroid, -1, level);
    for (auto x : graph[centroid])
    {
        if (removed[x.first]) continue;
        dfs4(x.first, level + 1);
    }
}

int main()
{
    
    cin.tie(0); cout.tie(0); cin.sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
        graph[b].push_back({a, c});
    }
    // proprocessing to get d_dist and g_centroid tables
    dfs4(1, 0);
    
    // find distance between any two nodes in the tree
    int a1 = 2, a2 = 5;
    int final_level;
    for (int level = log2(MM); level >= 0; level--)
    {
        if (g_centroid[level][a1] == -1 || g_centroid[level][a2] == -1 || g_centroid[level][a1] != g_centroid[level][a2]) continue;
        final_level = level;
        break;
    }
    cout << "distance between 2 nodes: \n";
    cout << g_dist[final_level][a1] + g_dist[final_level][a2] << "\n";
    
    // find the min distance between set-A and set-B
    vector<int> va = {2, 4}, vb = {6, 8};
    vector <int> vec1(MM, 1e9);
    
    int ans = 1e9;
    vector<int> centroids;
    // find min distance to centroid for set-A
    for (auto b: va)
    {
        for (int level = log2(MM); level >= 0; level--)
        {
            if (g_centroid[level][b] == -1) continue;
            vec1[g_centroid[level][b]] = min(g_dist[level][b], vec1[g_centroid[level][b]]);
            centroids.push_back(g_centroid[level][b]);
        }
    }
   
    // loop through node in set-B
    for (auto b: vb)
    {
        for (int level = log2(MM); level >= 0; level--)
        {
            if (g_centroid[level][b] == -1) continue;
            if (vec1[g_centroid[level][b]] < 1e9) 
            {
                ans = min(vec1[g_centroid[level][b]] + g_dist[level][b], ans);
            }
        }
    }
    cout << "min distance between 2 sets of nodes: \n";
    cout << ans << "\n";
        
    // reinitialize for the next query
    for (auto x: centroids) vec1[x] = 1e9;
        
        
    
}
