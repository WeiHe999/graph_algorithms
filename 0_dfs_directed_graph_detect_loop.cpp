#include <bits/stdc++.h>
using namespace std;


void dfs(int start, unordered_map<int, unordered_set<int> > &graph, bool found_loop, 
vector<int> &visited, vector<int> &dist, int &loop_length)
{
    if (found_loop) return;
    visited[start] = 1;
    for (auto x: graph[start])
    {
        // if detect a loop
        if (visited[x]==1)
        {
            found_loop = true;
            loop_length = dist[start] - dist[x] + 1;
            return;
        }
        if (visited[x]==0)
        {
            visited[x] = 1;
            dist[x] = dist[start] + 1;
            dfs(x, graph, found_loop, visited, dist, loop_length);
        }
    }
    // update visited status to 2 if all of the descendents of the node have been visited
     visited[start] = 2;
}

int main()
{
    cin.tie(0); cout.tie(0); cin.sync_with_stdio(0);
    unordered_map<int, unordered_set<int> > graph = {{1, {2}}, {2, {3, 5}}, {3, {4, 5}}, {4, {2}}};
    vector<int> visited(10, 0);
    vector<int> dist(10, 0);
    int loop_lenth = -1;
    bool found_loop = false;
    dfs(1, graph, found_loop, visited, dist, loop_lenth);
    cout << loop_lenth << endl;
    
    
}
