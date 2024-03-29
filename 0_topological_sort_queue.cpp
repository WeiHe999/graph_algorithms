/*
5 courses, each course may have prerequisites, for example the 3rd course: 3 1 2 5, means that the third course has 3 prerequisites, 
which are courses 1, 2, and 5
input format:
5
0
0
3 1 2 5
3 1 2 3
1 2
output:
1 2 5 3 4
*/

#include <bits/stdc++.h>
using namespace std;

template < typename T > void print (T t)
{
    for (const auto & e:t) cout << e << " ";
    cout << "\n";
}

void topological_sort(unordered_map<int, unordered_set<int> > &graph, vector<int> &indegree, vector<int> &top_order, int n)
{
    queue<int> q1;
    int cnt = 0;
    for (int i=1; i<=n; i++)
    {
        if (indegree[i]==0) q1.push(i);
    }
    while(!q1.empty())
    {
        int cur = q1.front();
        top_order.push_back(cur);
        q1.pop();
        cnt++;
        for (auto x: graph[cur])
        {
            indegree[x]--;
            if (indegree[x]==0) q1.push(x);
        }
    }
    if (cnt!=n) cout << "There is loop in the grpah\n";
}

int main()
{
    cin.tie(0); cout.tie(0); cin.sync_with_stdio(0);
    int n, m, a;
    cin >> n;
    unordered_map<int, unordered_set<int> > graph;
    vector<int> indegree(n+1);
    for (int i=1; i<=n; i++)
    {
        cin >> m;
        for (int j=0; j<m; j++)
        {
            cin >> a;
            graph[a].insert(i);
            indegree[i]++;
        }
    }
    // print graph
    // for (auto x: graph)
    // {
    //     cout << x.first << " : ";
    //     for (auto y: x.second) cout << y << ", ";
    //     cout << endl;
    // }
    // print(indegree);
    //topological sort
    vector<int> top_order;
    topological_sort(graph, indegree, top_order, n);
    print(top_order);
    
    
}
