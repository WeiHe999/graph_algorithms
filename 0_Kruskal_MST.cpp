

//Kruskal’s Minimum Spanning Tree Algorithm

#include <bits/stdc++.h>
using namespace std;

template < typename T > void print (T t)
{
    for (const auto & e:t) cout << e << " ";
    cout << endl;
}


// Function to find root for a node
int find_set(int node, vector<int> &parents)
{
    if (node!=parents[node]) parents[node] = find_set(parents[node], parents);
    return parents[node];
}
    
// Function to merge two nodes
bool unify(int node1, int node2, vector<int> &parents, vector<int> &rank)
{
    int root1 = find_set(node1, parents);
    int root2 = find_set(node2, parents);
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
int kruskal(unordered_map<int, vector<pair<int, int> > > &graph)
{
    //number of nodes
    int n = graph.size();
    
    // init parants, and rank
    vector<int> parents(n+1), rank(n+1);
    for (int i = 0; i <= n; i++) parents[i] = i;
    
    // push all edges into priority_queue
    priority_queue<vector<int> > pq;
    for (auto x: graph)
    {
        for (auto y: x.second)
        {
            vector<int> tmp = {{-1*y.second, x.first, y.first}};
            pq.push(tmp);
        }
    }
    
    // kruskal algorithm: union to build minimum spanning tree
    int tot_cost = 0;
    unordered_map<int, unordered_map<int, int> > mst_graph;
    int connected_nodes = 1;
    while(!pq.empty())
    {
        // the edge with min weight
        vector<int> v1 = pq.top();
        pq.pop();
        // union
        bool flag = unify(v1[1], v1[2], parents, rank);
        if (flag) 
        {
            tot_cost += -1*v1[0];
            mst_graph[v1[1]][v1[2]] = -1*v1[0];
            mst_graph[v1[2]][v1[1]] = -1*v1[0];
            connected_nodes++;
        }
        if (connected_nodes==n) break;
    } 
    
    // //print the tree
    cout << "Edges in min-spanning-tree:" << endl;
    for (auto x: mst_graph)
    {
        for (auto y: x.second) cout << x.first << " --> " << y.first << ", weight= " << y.second << endl;
    }
    
    return tot_cost;
}



int main()
{
    cin.tie(0); cout.tie(0); cin.sync_with_stdio(0);
    
    // step-1: undirected graph
    //unordered_map<int, vector< pair<int, int> >> graph;//{start_node: {end_node, weight}}
    unordered_map<int, vector<pair<int, int> > > graph;//{start_node: {end_node, weight}}
    graph[0] = {{1, 1}, {2, 6}};
    graph[1] = {{2, 2}, {0, 1}};
    graph[2] = {{3, 3}, {0, 6}, {1, 2}};
    graph[3] = {{0, 5}, {2, 3}};
    
    int tot_cost = kruskal(graph);
    cout << "The total cost  for the min-spanning tree is: " << tot_cost << endl;

}
