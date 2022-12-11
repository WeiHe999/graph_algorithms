// dmoj: Road Network

#include <bits/stdc++.h>
using namespace std;

long long distance(long long x1, long long y1, long long x2, long long y2)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

// Function to find root for a node
long long find_set(long long node, vector<long long> &parents)
{
    if (node!=parents[node]) parents[node] = find_set(parents[node], parents);
    return parents[node];
}
    
// Function to merge two nodes
bool unify(long long node1, long long node2, vector<long long> &parents, vector<long long> &rank)
{
    long long root1 = find_set(node1, parents);
    long long root2 = find_set(node2, parents);
    if (root1 == root2)
    {
        return false; //loop        
    }
    else if (rank[root2] > rank[root1])
    {
        parents[root1] = root2;
        return true;        
    }
    else
    {
        parents[root2] = root1;
        if (rank[root2] == rank[root1]) rank[root1]++;
        return true;     
    }

}

// Kruskal's algorithm to get MST for bi-directional graph
double kruskal(unordered_map <long long, unordered_map<long long, long long> > &graph)
{
    //number of nodes
    long long n = graph.size();
    
    // init parants, and rank
    vector<long long> parents(n+1), rank(n+1);
    for (long long i = 0; i <= n; i++) parents[i] = i;
    
    // push all edges into priority_queue
    priority_queue<vector<long long> > pq;
    //set<pair<long long, long long> > visited;
    for (auto x: graph)
    {
        for (auto y: x.second)
        {
            vector<long long> tmp = {{-1*y.second, x.first, y.first}};
            pq.push(tmp);
        }
    }
    
    // kruskal algorithm: union to build minimum spanning tree
    double tot_cost = 0;
    unordered_map<int, unordered_map<int, int> > mst_graph;
    long long connected_nodes = 1;
    while(!pq.empty())
    {
        // the edge with min weight
        vector<long long> v1 = pq.top();
        pq.pop();
        // union
        bool flag = unify(v1[1], v1[2], parents, rank);
        if (flag) 
        {
            tot_cost += sqrt(-1.0*v1[0]);
            mst_graph[v1[1]][v1[2]] = -1*v1[0];
            mst_graph[v1[2]][v1[1]] = -1*v1[0];
            connected_nodes++;
        }
        if (connected_nodes==n) break;
    } 
    
    // //print the tree
    // cout << "Edges in min-spanning-tree:" << endl;
//     for (auto x: mst_graph)
//     {
//         for (auto y: x.second) cout << x.first << " --> " << y.first << ", weight= " << y.second << endl;
//     }
    
    return tot_cost;
}

int main()
{
    cin.tie(0); cout.tie(0); cin.sync_with_stdio(0);
    long long n, m, a, b;
    cin >> n >> m;
    unordered_map <long long, pair <long long, long long> > m1;
    unordered_map <long long, unordered_map<long long, long long> > graph;//{start_node: {end_node: dist}}
    for (long long x = 1; x <= n; x++)
    {
        cin >> a >> b;
        m1[x] = {a, b};
    }
    // completely connected graph
    for (long long x = 1; x <= n; x++)
    {
        for (long long y = x+1; y <= n; y++)
        {
            long long d = distance(m1[x].first, m1[x].second, m1[y].first, m1[y].second);
            graph[x][y] = d;
            graph[y][x] = d;
        }
    }
    // set the cost for the existing edges to 0
    for (long long x = 0; x < m; x++)
    {
        cin >> a >> b;
        graph[a][b] = 0;
        graph[b][a] = 0;
    }
    
    double tot_cost = kruskal(graph);
    cout << fixed << setprecision(2) << tot_cost << "\n";
    
}
