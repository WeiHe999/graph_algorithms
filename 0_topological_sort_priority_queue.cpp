#include <bits/stdc++.h>
using namespace std;

template < typename T > void print (T t)
{
    for (const auto & e:t) cout << e << " ";
    cout << "\n";
}

void topological_sort(unordered_map<int, unordered_set<int> > &graph, vector<int> &indegree, vector<int> &top_order, int n)
{
    //priority_queue<int, vector<int>, greater<int> > q1; //small element goes first, output: 1 2 5 3 4
    priority_queue<int> q1; // larger element goes first, output: 2 5 1 4 3
    int cnt = 0;
    for (int i=1; i<=n; i++)
    {
        if (indegree[i]==0) q1.push(i);
    }
    while(!q1.empty())
    {
        int cur = q1.top(); // if it is a queue, use q1.front()
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
