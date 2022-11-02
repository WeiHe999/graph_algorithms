/*
input
6 6
1 2
2 3
3 4
4 5
5 3
1 6

*/


#include <bits/stdc++.h>
using namespace std;

template < typename T > void print (T t)
{
    for (const auto & e:t) cout << e << " ";
    cout << "\n";
}

void dfs(unordered_map<int, unordered_set<int> > &graph, vector<bool> &visited, 
        vector<int> &tin, vector<int> &tout, vector<int> &low, int v, int parent, 
        int &timer, vector<bool> &ap,  vector<pair<int,int> > &bridges) 
{
    visited[v] = true;
    tin[v] = low[v] = timer;
    timer++;
    for (int x : graph[v]) {
        //case-1: parent, do nothing
        if (x == parent) continue;
        //case-2: visited node ==> loop point, this is a back edge
        if (visited[x]) {
            low[v] = min(low[v], tin[x]);
        //case-3: unvisited node, do recursive dfs
        } else {
            dfs(graph, visited, tin, tout, low, x, v, timer, ap, bridges);
            low[v] = min(low[v], low[x]);
            //bridge condition
            if (low[x] > tin[v]) bridges.push_back({v, x});
            // anticulation point (not a root)
            if (low[x] >= tin[v] & parent!=-1) ap[v] = true;
        }
    }
    //after visiting all the children, update finish time
    // finish_time == ddiscover_time_of_the_last_child
    tout[v] = timer;
    timer++;
}

//is vertex c in the subtree rooted at p (parent) 
//parent: first in last out
bool is_descendant( int c, int p, vector<int> &tin, vector<int> &tout ) {
   return tin[p] <= tin[c] && tout[c] <= tout[p];
}

int main()
{
    cin.tie(0); cout.tie(0); cin.sync_with_stdio(0);
    int n, m, a, b;
    unordered_map<int, unordered_set<int> > graph;
    cin >> n >> m;
    for (int i=0; i<m; i++)
    {
        cin >> a >> b;
        graph[a].insert(b);
        graph[b].insert(a);
    }
    int timer = 0;
    //ap: anticulation points
    vector<bool> visited(n+1, false), ap(n+1);
    //tin: discovery time (entry time), tout: finish time (out time), 
    //low: low_link_time (the least discovery time that is reachable from the current vertex or from its descendants (via a single back edge) )
    vector<int> tin(n+1), tout(n+1), low(n+1);
    vector<pair<int,int> > bridges;
    int parent = -1;
    int root = 1;
    // a root is an anticulation point if it has 2 or more children
    if (graph[root].size()>1) ap[root] = true;
    dfs(graph, visited, tin, tout, low, root, parent, timer, ap, bridges);
    
    //print
    cout << "discovery time:" << endl;
    print(tin);
    cout << "finish time:" << endl;
    print(tout);
    cout << "low link time:" << endl;
    print(low);
    cout << "articulation points:" << endl;
    print(ap);
    cout << "bridges:" << endl;
    for (auto x: bridges)
    {
        cout << "(" << x.first << ", " << x.second << ")";
    }
    cout << endl;
    
    // check if node c is a descendent of node p
    int c = 5, p = 6;
    if (is_descendant( c, p, tin, tout)) cout << "Yes" << endl;
    else cout << "No" << endl;
    
    
}
