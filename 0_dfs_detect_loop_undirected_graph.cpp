/*
Q2:
Given an undirected graph with one loop, print the path of the loop, for example, if node 1—>node 2—>node3—>node 1, the loop path can e printed as: 1 2 3 1 or 2 3 1 2 or 3 1 2 3, either one is correct
Input: the first line contains two integers M, N where M is the number of nodes and N is the number of edges, the next M lines represent M undirected connections with start node and end node
Output: a loop path
Test case:
Input: 
5 5
1 2
2 3
3 4
4 2
3 5

Output:
2 3 4 2
*/

#include <bits/stdc++.h>
using namespace std;

unordered_map <int, vector <int> > graph;
vector <int> vec1;

void dfs(int prev, int cur, 
unordered_map <int, int> &parents, unordered_set <int> &visited, bool &flag)
{
 
    visited.insert(cur);
    //cout << "visited: " << cur << endl;
    for (auto x : graph[cur])
    {
        if (visited.count(x) && x != prev & !flag)
            {
                int c = cur;
                vec1 = {x};
                while (c != x)
                {
                    vec1.emplace_back(c);
                    c = parents[c];
                }
                vec1.emplace_back(x);
                flag = true;
            }
        
        if (!visited.count(x))
        {
            parents[x] = cur;
            dfs(cur, x, parents, visited, flag);
        }
    }
    
}

int main()
{
    cin.tie(0); cout.tie(0); cin.sync_with_stdio(0);
    int n, m, a, b;
    cin >> n >> m;
    for (int x = 0; x < n; x++)
    {
        cin >> a >> b;
        graph[a].emplace_back(b);
        graph[b].emplace_back(a);
    }
    unordered_map <int, int> parents;
    unordered_set <int> visited;
    parents[1] = 0;
    bool flag = false;
    dfs(0, 1, parents, visited, flag);
    reverse(vec1.begin(), vec1.end());
    for (auto x : vec1) cout << x << " ";
    cout << "\n";
}
