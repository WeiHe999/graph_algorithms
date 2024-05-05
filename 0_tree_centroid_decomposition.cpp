/*
use tree centroid decomposition to find the number of paths with a fixed length
idea: recursive to find tree centroid, until all nodes have been used as a centroid
for each centrois, find the number of paths cross the centroid (including start from the centroid or end at centroid) by using a unordered_map

sample input:
5 2 // number of nodes = 5, fix_length = 2
1 2
1 3
3 4
3 5


output
4
*/

#include <bits/stdc++.h>
using namespace std;

const int MM = 1e1 + 1;
int n, a, b, centroid, cnt=0, fixed_len;
unordered_map<int, vector<int> > graph;
vector<bool> is_removed(MM, false);
vector<int> subtree_size(MM), dist(MM);
unordered_map<int, int> m1; //{distrance_from_centroid: frequency}

/** DFS to calculate the size of the subtree rooted at `node` */
void dfs1(int node, int parent = -1) {
	subtree_size[node] = 1;
	for (auto child : graph[node]) {
		if (child == parent || is_removed[child]) continue;
		dfs1(child, node);
		subtree_size[node] += subtree_size[child];
	}
}

// find centroid
void dfs2(int node, int parent = -1) {
    bool flag = true;
    int tree_size = subtree_size[node];
	for (auto child : graph[node]) {
		if (child == parent || is_removed[child]) continue;
		if (subtree_size[child] * 2 > tree_size) {
		    flag = false;
		    dfs2(child, node);
		}
	}
	if (flag) 
	{
	    centroid = node;
	    is_removed[node] = true;
	}
}

// find distance from centroid to every node
void dfs3(int cur, int prev)
{
    for (auto x: graph[cur])
    {
        if (x==prev || is_removed[x]) continue;
        dist[x] = dist[cur] + 1;
        cout << "dist[x]=" << dist[x] << endl;
        if (m1.count(fixed_len - dist[x])) 
        {
            cnt += m1[fixed_len - dist[x]];
            cout << "centroid=" << centroid << ", node=" << x << endl;
        }
        m1[dist[x]]++;
        dfs3(x, cur);
    }
}

// // /** Build up the centroid decomposition recursively */
void dfs4(int node) {
    // update subtree_size
    dfs1(node, -1);
    // find centroid
    dfs2(node, -1);
    cout << "centroid=" << centroid << endl;
     
	// find the number of path with fix-length
	m1 = {};
	m1[0] = 1;
	dist[centroid] = 0;
	//for (int i=1; i<=n; i++) dist[i] = 0;
	dfs3(centroid, -1);
	for (int child : graph[centroid]) {
		if (is_removed[child]) continue;
		dfs4(child);
	}
}


int main()
{
    cin >> n >> fixed_len;
    for (int i = 1; i<n; i++)
    {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    
    dfs4(1);
    cout << cnt << endl;  
    
}
