/*
This algorithm is used to find the strongly connected components from a directed graph.
In a strongly connected component, each node can reach any other node in the same component. In other words,
for any two nodes a and b in the same component, a can reach b and b can reach a.
input:
6 8 // num_nodes = 6, num_edges = 8
1 2 // edge 1
1 3
2 4
4 1
3 5
5 6
4 6
3 4

output: 3 components with roots 1, 5, 6, respectively:
1: 3 4 2 1 
5: 5 
6: 6 

*/

#include <bits/stdc++.h>
using namespace std;
const int MM = 10;

unordered_map <int, vector <int> > graph;
unordered_map <int, vector <int> > components;
vector <int> dfn(MM + 1), low(MM + 1), in_stack(MM + 1);
stack <int> s1;
int ind;

void tarjan(int cur)
{
    ind++;
    dfn[cur] = low[cur] = ind;
    s1.push(cur);
    in_stack[cur] = 1;
    for (auto x : graph[cur])
    {
        if (dfn[x] == 0)
        {
            tarjan(x);
            low[cur] = min(low[cur], low[x]);
        }
        else if (in_stack[x]) low[cur] = min(low[cur], dfn[x]);
    }
    if (dfn[cur] == low[cur])
    {
        vector <int> vec1;
        while (s1.top() != cur)
        {
            vec1.emplace_back(s1.top());
            in_stack[s1.top()] = 0;
            s1.pop();
        }
        vec1.emplace_back(s1.top());
        components[s1.top()] = vec1;
        in_stack[s1.top()] = 0;
        s1.pop();
    }
}

int main() {
    int n, m, a, b;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        graph[a].push_back(b);
    }
    ind = 0;
    tarjan(1);
    for (auto x : components)
    {
        cout << x.first << ": ";
        for (auto y : x.second) cout << y << " ";
        cout << "\n";
    }
}
