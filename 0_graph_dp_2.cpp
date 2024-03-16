/*
graph dp example: find the max sum of node values from source to destination, and the number of ways to get the max total sum
You can not collect values from any two consecutive nodes.
input:
5 5
1 4 2 6 2
1 2
1 4
2 3
3 5
4 5

output:
6
2 // 2 ways to get max value 9
*/


#include <bits/stdc++.h>
using namespace std;

const int MM = 10;
unordered_map<int, vector<int> > graph, parents;
vector<int> value(MM);
vector< vector<int> > dp(MM, vector<int> (2)), cnt(MM, vector<int> (2));
int s, e;

// find max total sum
void dfs(int cur)
{
    // base case
    if (cur==s) 
    {
        dp[cur][0] = 0;
        dp[cur][1] = value[cur];
        return;
    }
    if (dp[cur][0] > 0 || dp[cur][1] > 0) return;
    for (auto p: parents[cur])
    {
        dfs(p);
        
        dp[cur][1] = max(dp[cur][1], dp[p][0] + value[cur]);
        dp[cur][0] = max({dp[cur][0], dp[p][0], dp[p][1]});
    }
}

// find number of ways to get max total sum
void dfs1(int cur)
{
    // base case
    if (cur==s) 
    {
        cnt[cur][0] = 1;
        cnt[cur][1] = 1;
        return;
    }
    // memoization
    if (cnt[cur][0] > 0 || cnt[cur][1] > 0 ) return;
    for (auto p: parents[cur])
    {
        dfs1(p);
        if (dp[cur][1] == dp[p][0] + value[cur]) cnt[cur][1] += cnt[p][0];
        if (dp[cur][0] == dp[p][0]) cnt[cur][0] += cnt[p][0];
        if (dp[cur][0] == dp[p][1]) cnt[cur][0] += cnt[p][1];
        
    }
}


int32_t main() {
    int n, m, a, b;
    cin >> n >> m;
    s = 1, e = n;
    for (int i = 1; i <= n; i++) cin >> value[i];
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        graph[a].emplace_back(b);
        parents[b].emplace_back(a);
    }
    
    dfs(e);
    dfs1(e);
    int max_v = max(dp[e][0], dp[e][1]);
    int max_n = 0;
    if (max_v==dp[e][0]) max_n += cnt[e][0];
    if (max_v==dp[e][1]) max_n += cnt[e][1];
    cout << max_v << endl;
    cout << max_n << endl;
    
}
