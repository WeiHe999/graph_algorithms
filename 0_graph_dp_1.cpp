/*
graph dp example: find the max sum of node values from source to destination, and the number of ways to get the max total sum
input:
5 5
1 4 2 6 2
1 2
1 4
2 3
3 5
4 5

output:
9
2 // 2 ways to get max value 9
*/


#include <bits/stdc++.h>
using namespace std;

const int MM = 10;
unordered_map<int, vector<int> > graph, parents;
vector<int> value(MM), dp(MM), cnt(MM);
int s, e;

// find max total sum
void dfs(int cur)
{
    // base case
    if (cur==s) 
    {
        dp[cur] = value[cur];
        return;
    }
    if (dp[cur] > 0) return;
    for (auto p: parents[cur])
    {
        dfs(p);
        dp[cur] = max(dp[cur], dp[p] + value[cur]);
    }
}

// find number of ways to get max total sum
void dfs1(int cur)
{
    // base case
    if (cur==s) 
    {
        cnt[cur] = 1;
        return;
    }
    // memoization
    if (cnt[cur] > 0) return;
    for (auto p: parents[cur])
    {
        dfs1(p);
        if (dp[p] + value[cur] == dp[cur])
        {
            cnt[cur] += cnt[p];
        }
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
    cout << dp[e] << endl;
    cout << cnt[e] << endl;
    
}
