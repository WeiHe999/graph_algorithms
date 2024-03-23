/*
problem: find the sum of distances to each node in a tree in time complexity of O(n)
sample input:
5 4
1 2
1 3
3 4
3 5

Output:
6 9 5 8 8

Method:
1. use type-1 tree DP (child to parent) to find the sum of distances to node-1
2. use type-2 tree DP (use parent to update child) to do re-rooting, finding the sum of distances to every node
*/

#include <bits/stdc++.h>
using namespace std;

const int MM = 10;
int n, m, dist[MM], cnt[MM], ans[MM];
vector<int> adj[MM];

// type-1 tree dp, update parent DP from children DP
void dfs1(int cur, int par)
{
    cnt[cur] = 1;
    for (auto x: adj[cur])
    {
        if (x==par) continue;
        dfs1(x, cur);
        cnt[cur] += cnt[x];
        dist[cur] += (dist[x] + cnt[x]);
    }
}

// type-1 tree dp, update child DP from parent DP (do the update before looping through children)
void dfs2(int cur, int par, int par_dist)
{
    if (par!=-1)
    {
        ans[cur] = par_dist - cnt[cur] + (n - cnt[cur]);
    }
    for (auto x: adj[cur])
    {
        if (x==par) continue;
        dfs2(x, cur, ans[cur]);
    }
}

int main() {
    
    memset(dist, 0, sizeof(dist));
    memset(cnt, 0, sizeof(cnt));
    memset(ans, 0, sizeof(ans));
    cin >> n >> m;
    for (int i = 0, a, b; i<m; i++)
    {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    // dfs to find the sum of diatnces to root node 1
    dfs1(1, -1);
    ans[1] = dist[1];

    // re-rooting to find the sum of diatnces to every node as root
    dfs2(1, -1, ans[1]);
    
    for (int i = 1; i<=n; i++) cout << ans[i] << " ";
    cout << endl;
    

}
