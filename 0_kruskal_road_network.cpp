// DMOJ problem: road network
// build min-spanning tree for bi-directional weighted graph using Kruskal algorithm

#include <bits/stdc++.h>
using namespace std;

long long distance(long long x1, long long y1, long long x2, long long y2)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

// Function to find root for a node
long long find_root(long long node, unordered_map<long long, long long> &node_mapping, vector<long long> &node_ids)
{
    long long x = node_mapping[node];
    vector<long long> list1;
    while (x != node_ids[x])
    {
        list1.push_back(x);
        x = node_ids[x];       
    }
    // path compression
    for (auto y: list1) node_ids[y] = x;
    return x;
}
    
// Function to merge two nodes
bool unify(long long node1, long long node2, unordered_map<long long, long long> &node_mapping, vector<long long> &node_ids, vector<long long> &comp_size)
{
    // find the roots 
    // if they are the same, return the root
    // if not the same, find which one has larger size, merge small component to larger component
    // update component size
    long long root1 = find_root(node1, node_mapping, node_ids);
    long long root2 = find_root(node2, node_mapping, node_ids);
    if (root1 == root2)
    {
        return false; //loop        
    }
    else if (comp_size[root2] > comp_size[root1])
    {
        node_ids[root1] = root2;
        comp_size[root2] += comp_size[root1];
        comp_size[root1] = 0;
        return true;        
    }
    else
    {
        node_ids[root2] = root1;
        comp_size[root1] += comp_size[root2];
        comp_size[root2] = 0;
        return true;     
    }

}

// Kruskal's algorithm to get MST for bi-directional graph
double kruskal(unordered_map <long long, unordered_map<long long, long long> > &graph)
{
    //number of nodes
    long long n = graph.size();
    
    // step-2: node_mapping
    unordered_map<long long, long long> node_mapping;
    long long number_nodes = 0;
    for (auto x: graph)
    {
        node_mapping[x.first] = number_nodes;
        number_nodes++;
    }
    
    // step 3: init node_ids, and comp_sizes
    vector<long long> node_ids(number_nodes), comp_size(number_nodes, 1);
    for (long long i = 0; i<number_nodes; i++) node_ids[i] = i;
    
    // step-4: push all edges into priority_queue
    priority_queue<vector<long long> > pq;
    set<pair<long long, long long> > visited;
    for (auto x: graph)
    {
        for (auto y: x.second)
        {
            vector<long long> tmp = {{-1*y.second, x.first, y.first}};
            pq.push(tmp);
        }
    }
    
    // step-5: kruskal algorithm: union to build minimum spanning tree
    double tot_cost = 0;
    vector<pair<long long, long long> > keep_edges;
    long long connected_nodes = 1;
    while(!pq.empty())
    {
        // the edge with min weight
        vector<long long> v1 = pq.top();
        pq.pop();
        // union
        bool flag = unify(v1[1], v1[2], node_mapping, node_ids, comp_size);
        if (flag) 
        {
            tot_cost += sqrt(-1.0*v1[0]);
            keep_edges.push_back({v1[1], v1[2]});
            connected_nodes++;
        }
        if (connected_nodes==n) break;
    } 
    
    // //print the tree
    // cout << "Edges in min-spanning-tree:" << endl;
    // for (auto x: keep_edges)
    // {
    //     cout << x.first << " --> " << x.second << endl;
    // }
    
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
