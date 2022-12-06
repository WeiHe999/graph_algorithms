

//Kruskal’s Minimum Spanning Tree Algorithm

#include <bits/stdc++.h>
using namespace std;

template < typename T > void print (T t)
{
    for (const auto & e:t) cout << e << " ";
    cout << endl;
}

// Function to find root for a node
int find_root(int node, unordered_map<int, int> &node_mapping, vector<int> &node_ids)
{
    int x = node_mapping[node];
    vector<int> list1;
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
bool unify(int node1, int node2, unordered_map<int, int> &node_mapping, vector<int> &node_ids, vector<int> &comp_size)
{
    // find the roots 
    // if they are the same, return the root
    // if not the same, find which one has larger size, merge small component to larger component
    // update component size
    int root1 = find_root(node1, node_mapping, node_ids);
    int root2 = find_root(node2, node_mapping, node_ids);
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

// Kruskal algorithm for bulding min-spannig tree for bi-directional weighted graph
int kruskal(unordered_map<int, unordered_map<int, int> > &graph)
{
    // number of nodes in the graph
    int num_nodes = graph.size();
    
    // step-2: node_mapping
    unordered_map<int, int> node_mapping;
    int number_nodes = 0;
    for (auto x: graph)
    {
        node_mapping[x.first] = number_nodes;
        number_nodes++;
    }
    
    // step 3: init node_ids, and comp_sizes
    vector<int> node_ids(number_nodes), comp_size(number_nodes, 1);
    for (int i = 0; i<number_nodes; i++) node_ids[i] = i;
    
    // step-4: push all edges into priority_queue
    priority_queue<vector<int> > pq;
    for (auto x: graph)
    {
        for (auto y: x.second)
        {
            vector<int> tmp = {{-1*y.second, x.first, y.first}};
            pq.push(tmp);            
        }
    }
    
    // step-5: kruskal algorithm: union to build minimum spanning tree
    int tot_cost = 0;
    int connected_nodes = 1;
    unordered_map<int, unordered_map<int, int> > mst_graph;
    while(!pq.empty())
    {
        // the edge with min weight
        vector<int> v1 = pq.top();
        pq.pop();
        // union
        bool flag = unify(v1[1], v1[2], node_mapping, node_ids, comp_size);
        if (flag) 
        {
            tot_cost += (-1*v1[0]);
            connected_nodes++;
            mst_graph[v1[1]][v1[2]] = -1*v1[0];
            mst_graph[v1[2]][v1[1]] = -1*v1[0];
        }
        //break if all nodes are merged
        if (connected_nodes==num_nodes) break;
    }
    cout << "The edges in min-spanning tree are:" << endl;
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
    unordered_map<int, unordered_map<int, int> > graph;//{start_node: {end_node, weight}}
    graph[0] = {{1, 1}, {2, 6}};
    graph[1] = {{2, 2}, {0, 1}};
    graph[2] = {{3, 3}, {0, 6}, {1, 2}};
    graph[3] = {{0, 5}, {2, 3}};
    
    int tot_cost = kruskal(graph);
    cout << "The total cost  for the min-spanning tree is: " << tot_cost << endl;

}
