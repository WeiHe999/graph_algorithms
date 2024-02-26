#include <bits/stdc++.h>
using namespace std;
const int MM = 10;

unordered_map <int, vector <int> > graph;
unordered_map <int, vector <int> > components;
vector <int> dfn(MM + 1), low(MM + 1), in_stack(MM + 1);
stack <int> s1;
int ind = 0;

void tarjan(int cur, int prev)
{
    ind++;
    dfn[cur] = low[cur] = ind;
    s1.push(cur);
    in_stack[cur] = 1;
    for (auto x : graph[cur])
    {
        if (x==prev) continue;
        if (dfn[x] == 0)
        {
            tarjan(x, cur);
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
        graph[b].push_back(a);
    }
    tarjan(1, -1);
    for (auto x : components)
    {
        cout << x.first << ": ";
        for (auto y : x.second) cout << y << " ";
        cout << "\n";
    }
    
    // print all bridges in the bidirectional graph
    set<pair<int, int> > bridges;
    for (int i=1; i<=n; i++)
    {
        for (auto x: graph[i])
        {
            // from node-i to node-x
            if ((dfn[x] > dfn[i]) && (low[x] > low[i])) bridges.insert({min(i, x), max(i, x)});
            if ((dfn[i] > dfn[x]) && (low[i] > low[x])) bridges.insert({min(i, x), max(i, x)});
        }

    }
    cout << "Bridges: " << endl;
    for (auto x : bridges)
    {
        cout << x.first << ", " << x.second << endl;
    }
    
}
