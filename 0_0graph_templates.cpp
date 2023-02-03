// ****************************************
// *************** BFS ********************
// ****************************************

// basic BFS
// find the distance from start_node to end_node in an unweighted graph, return -1 if not reachable
int bfs(unordered_map <int, unordered_set <int> > graph, int start_node, int end_node)
{
    if (start_node == end_node) return 0;
    queue <int> q1;
    unordered_set <int> visited;
    unordered_map <int, int> dist;
    q1.push(start_node);
    visited.insert(start_node);
    dist[start_node]= 0;
    while (!q1.empty())
    {
        int cur_node = q1.front();
        q1.pop();
        for (auto x : graph[cur_node])
        {
            if (!visited.count(x))
            {
                visited.insert(x);
                dist[x] = dist[cur_node] + 1;
                if (x == end_node) return dist[x];
                q1.push(x);
            }
        }

    }
    return -1;
}

// BFS on 2D grid of char, 'O' is open space (you can go up, down, left, right), 'X' is wall (you can go into the cell)
// 'C' is start position, 'W' is destination, cell is numbered from 1 to 50
int bfs(vector <vector <char> > graph, pair <int, int> start_node, pair <int, int> end_node)
{
    // cell is numbered from 1 to 50
    int max_cell = 50;
    // can not exceed 60 steps
    int max_allowed_steps = 60;
    
    queue <pair <int, int> > q1;
    vector <vector <int> > dist(max_cell+1, vector <int>(max_cell+1));
    vector <vector <bool> > vis(max_cell+1, vector <bool>(max_cell+1));
    q1.push(start_node);
    vis[start_node.first][start_node.second] = true;
    dist[start_node.first][start_node.second] = 0;
    while (!q1.empty())
    {
        pair <int, int> cur_node = q1.front();
        q1.pop();
        vector <pair <int, int> > vec1 = {{cur_node.first - 1, cur_node.second},
        {cur_node.first + 1, cur_node.second}, {cur_node.first, cur_node.second - 1}, {cur_node.first, cur_node.second + 1}};
        for (auto a : vec1)
        {
            if (a.first >= 1 && a.first < graph.size() && a.second >= 1 && 
            a.second < graph[0].size() && graph[a.first][a.second] != 'X' && !vis[a.first][a.second])
            {
                dist[a.first][a.second] = dist[cur_node.first][cur_node.second] + 1;
                if (dist[a.first][a.second] >= max_allowed_steps) return -1;
                if (a.first == end_node.first && a.second == end_node.second)
                {
                    return dist[a.first][a.second];
                }
                vis[a.first][a.second] = 1;
                q1.push(a);
            }
        }
    }
    return -1;
}

//multi-source BFS
unordered_map <int, vector <int> > graph;
// find the min-distance between a number of source nodes and a number of end nodes in an unweighted graph
// it can be converted to multiple cases: 
// 1) single-source-single-end BFS: start_nodes contains one node, end_nodes contains one node
// 2) multi-source-single-end BFS: start_nodes contains multiple nodes, end_nodes contains one node 
// 3) priority-multi-source-single-end BFS: source nodes are push into queue in a priority way
// 4) no end-node: in such case, set end_nodes to be empty, put vector <int> dist into input argument
int bfs(vector <int> start_nodes, unordered_set <int> end_nodes, int n)
{
    queue <int> q1;
    vector <int> dist(n + 1, -1);
    // if neccessary, sort start_nodes first for priority order
    for (auto a : start_nodes)
    {
        q1.push(a);
        dist[a] = 0;
        if (end_nodes.count(a)) return 0;
    }
    while (!q1.empty())
    {
        int cur_node = q1.front();
        q1.pop();
        for (auto x : graph[cur_node])
        {
            if (dist[x] == -1)
            {
                dist[x] = dist[cur_node] + 1;
                if (end_nodes.count(x)) return dist[x];
                q1.push(x);
            }
        }
    }
    return -1;
}

// ****************************************
// *************** DFS ********************
// ****************************************

// dfs on an unweighted graph
// initialize the two vectors as below:
vector <bool> vis(n + 1, false);
vector<int> dist(n+1, 0);

void dfs(unordered_map <int, unordered_set <int> > &graph, int cur_node, vector <bool> &vis, vector<int> &dist)
{
    vis[cur_node] = true;
    for (auto x : graph[cur_node])
    {
        if (!vis[x])
        {
            dist[x] = dist[cur_node] + 1;
            dfs(graph, x, vis, dist);
        }
    }
}

// DFS to detect loop in undirected graph
// returned params: loop_found: true or false; loop_nodes: the nodes in a loop
void dfs(unordered_map <int, unordered_set <int> > &graph, vector <int> &loop_nodes, int prev, int cur, 
unordered_map <int, int> &parents, unordered_set <int> &visited, bool &loop_found)
{
   if(loop_found) return;
 
    visited.insert(cur);
    //cout << "visited: " << cur << endl;
    for (auto x : graph[cur])
    {
        if (visited.count(x) && x != prev && !loop_found)
            {
                int c = cur;
                loop_nodes = {x};
                while (c != x)
                {
                    loop_nodes.emplace_back(c);
                    c = parents[c];
                }
                loop_nodes.emplace_back(x);
                loop_found = true;
            }
        
        if (!visited.count(x))
        {
            parents[x] = cur;
            dfs(graph, loop_nodes, cur, x, parents, visited, loop_found);
        }
    }
    
}

int main()
{
    unordered_map <int, unordered_set <int> > graph;
    vector <int> loop_nodes;
    unordered_map <int, int> parents;
    unordered_set <int> visited;
    int start_node = 1;
    parents[start_node] = -1;
    bool flag = false;
    dfs(graph, loop_nodes, parents[start_node], start_node, parents, visited, flag);
    reverse(loop_nodes.begin(), loop_nodes.end());
}

// DFS to detect loop in a directed graph
void dfs(int start, unordered_map<int, unordered_set<int> > &graph, bool found_loop, 
vector<int> &visited, vector<int> &dist, int &loop_length)
{
    if (found_loop) return;
    visited[start] = 1;
    for (auto x: graph[start])
    {
        // if detect a loop
        if (visited[x]==1)
        {
            found_loop = true;
            loop_length = dist[start] - dist[x] + 1;
            return;
        }
        if (visited[x]==0)
        {
            visited[x] = 1;
            dist[x] = dist[start] + 1;
            dfs(x, graph, found_loop, visited, dist, loop_length);
        }
    }
    // update visited status to 2 if all of the descendents of the node have been visited
     visited[start] = 2;
}

int main()
{
    unordered_map<int, unordered_set<int> > graph = {{1, {2}}, {2, {3, 5}}, {3, {4, 5}}, {4, {2}}};
    vector<int> visited(10, 0);
    vector<int> dist(10, 0);
    int loop_length = -1;
    bool found_loop = false;
    dfs(1, graph, found_loop, visited, dist, loop_length);
    cout << loop_length << endl;   
}


// ****************************************
// ***********Floyd Warshall **************
// ****************************************

// *************** Reachable maytrix by Floyd Warshall Algorithm ********************
// reachable[m][n] provides th emin-distance from node-m to node-n
// for loop detection, if reachable[n][n]>0 and reachable[n][n]<100001, node-n is in a loop
// used in weighted directed graph, for unweighted graph, set the weight for each edge to 1
// define reachable matrix as below:
int num_nodes = 100;
int max_dist = 100000; // the max hops between any two nodes
vector <vector <int> > reachable(num_nodes+1, vector <int>(num_nodes+1, max_dist+1));

void floyd_warshall(unordered_map<int, unordered_map<int, int> > graph, vector <vector <int> > &reachable, int n)
{
    for (auto x: graph)
    {
        for (auto y: graph[x.first])
        {
            reachable[x.first][y.first] = y.second;
        }
    }  
    for (int mid = 1; mid <= n; mid++)
    {
        for (int beg = 1; beg <= n; beg++)
        {
            for (int end = 1; end <= n; end++)
            {
                reachable[beg][end] = min(reachable[beg][end], reachable[beg][mid] + reachable[mid][end]);
            }
        }
    }
}

// ****************************************
// ************* Tree *********************
// ****************************************

// #### tree diamater and radius ###
void dfs(unordered_map <int, vector <pair <int, int> > > &graph, vector <bool> &vis,
vector <bool> &global_vis, vector <int> &dist, int cur_node, unordered_map <int, int> &parents, int &max_dist, int &max_node)
{
    vis[cur_node] = true;
    global_vis[cur_node] = true;
    for (auto x : graph[cur_node])
    {
        if (!vis[x.first])
        {
            dist[x.first] = dist[cur_node] + x.second;
            if (dist[x.first] > max_dist)
            {
                max_dist = dist[x.first];
                max_node = x.first;
            }
            parents[x.first] = cur_node;
            dfs(graph, vis, global_vis, dist, x.first, parents, max_dist, max_node);
        }
    }
}

int main()
{
    unordered_map <int, vector <pair <int, int> > > graph;
    // global visited vector, dealing with graph with multiple components
    vector <bool> global_vis(n + 1, false);
    
    //step-1: find one of the diameter endpoints
    vector <bool> vis1(n + 1, false);
    vector <int> dist1(n + 1);
    int start_node = 1;
    int max_node1 = start_node, max_dist1 = 0;
    unordered_map <int, int> par1={{start_node, -1}};
    dfs(graph, vis1, global_vis, dist1, start_node, par1, max_dist1, max_node1);
    cout << "One diameter endpoint is: " << max_node1 << endl;
    
    // step-2: find the diameter
    vector <bool> vis2(n + 1, false);
    vector <int> dist2(n + 1);
    start_node = max_node1;
    int max_node2 = start_node, max_dist2 = 0;
    unordered_map <int, int> par2 = {{start_node, -1}};
    dfs(graph, vis2, global_vis, dist2, start_node, par2, max_dist2, max_node2);
    int dia = max_dist2;
    cout << "The tree diameter length is: " << dia << endl;
    cout << "The two diameter endpoints are: " << start_node << ", " << max_node2 << endl;
    
    // step-3: find radius and tree center
    int cur = max_node2, rad = INT_MAX, center_node = -1;
    while (cur != -1)
    {
        int max_d = max(dist2[cur], dia - dist2[cur]);
        if (max_d < rad)
        {
            rad = max_d;
            center_node = cur;
        }
        cur = par2[cur];
    }
    cout << "The tree radius length is: " << rad << endl;
    cout << "The tree center is: " << center_node << endl; 
}

// #### tree travel ###
/*
tree travel properties in a tree of N nodes and N-1 edges:
Tree property 1: start from node A, visit all nodes and return back to node A, the total travel distance is 2*number_edges = 2*(N-1), 

Tree property 2:  start from node A, visit all nodes and finally stop at any node, what is the min total distance? 
Solution: the min total travel distance = 2*(N-1) - max_distance_from_node_A (DFS to find it)

Tree property 3:  you can start from any node, and visit all nodes, what is the min distance you need?
Solution: start from an diameter endpoint, end at another diameter endpoint, the min total travel distance = 2*(N-1) - tree_diameter

Tree property 4: how to find the max distance from any node to another node in O(N) complexity?
solution: 1) find both diameter endpoints, get dist1 and dist2 vectors, 2) loop through all nodes, for each node, 
the max_dist_node_k = max(dist1[k], dist2[k]), find the max dist among all n nodes.

Tree property 5: you can start from any node and end at any node, find the min distance to travel to visit a set of nodes in a tree?
Solution: 1) create a new graph cutting the unneccesary nodes (the nodes that will not lead to the desired nodes), 
2) min_distance = 2*(num_edges_in_new_graph) - tree_diameter
*/

// ### Tree travel for a set of nodes
// DFS to prune nodes from a undirected tree to get a new graph
// desired_nodes contain the nodes that must visit
// returned params: graph1 (new graph after cutting the unnecessary nodes)
void dfs(int start, unordered_map<int, unordered_set<int> > &graph, unordered_map<int, unordered_set<int> > &graph1, 
unordered_set<int> &desired_nodes, vector<bool> &visited, vector<bool> &keep)
{
    visited[start] = true;
    if (desired_nodes.count(start)) keep[start]=true;
    for (auto x: graph[start])
    {
        if (!visited[x])
        {
            dfs(x, graph, graph1, desired_nodes, visited, keep);
            keep[start] = keep[start] || keep[x];
            if (keep[start] && keep[x]) 
            {
                graph1[start].insert(x);
                graph1[x].insert(start);
            }
        }
    }    
}


// ****************************************
// ********* Topological Sort *************
// ****************************************

// topological sort on the undirected graph with n nodes
// can use priority_queue<int> to get unique output
bool top_sort(unordered_map <int, unordered_set <int> > &graph, int n, vector<int> &output1)
{
    vector<int> indegree(n+1);
    for (auto x: graph)
    {
        for (auto y: x.second)
        {
            indegree[y]++;
        }
    }
    queue <int> q1;
    //priority_queue<int> q1;
    //priority_queue<int, vector<int>, greater<int> > q1; // min priority queue
    for (int x = 1; x <= n; x++) if (indegree[x]==0) q1.push(x);
    int counter = 0;
    while (!q1.empty())
    {
        int cur_node = q1.front();
        //int cur_node = q1.top(); 
        q1.pop();
        output1.emplace_back(cur_node);
        counter++;
        for (auto x : graph[cur_node]) if (--indegree[x] == 0) q1.push(x);
    }
    if (counter != n) return false;
    return true;
}


// ****************************************
// *** Min-Spanning-Tree: PRIM ************
// ****************************************

// to find the min-total-cost for MST in a directed graph with n nodes
// return the total cost for building the MST

// node_id from 1 to n
int prim(unordered_map <int, unordered_map<int, int> > &graph, int n, unordered_map<int, int> &parents)
{
    // PRIM for MST
    vector<int> dist(n+1, LLONG_MAX), parents(n+1, -1);
    vector<bool> vis(n+1);
    priority_queue<pair<int, int> > min_q; //min_queue={dist, node_id}
    // push the first node
    dist[1] = 0;
    min_q.push({0, 1}); //{dist, node_id}
    while(!min_q.empty())
    {
        pair<int, int> min_n = min_q.top();
        int cur_node = min_n.second;
        min_q.pop();
        if (vis[cur_node]) continue;
        vis[cur_node] = true;
        for (auto x: graph[min_n.second])
        {
            int child_node = x.first;
            if ((!vis[child_node]) && (graph[cur_node][child_node] < dist[child_node]))
            {
                // update dist and parents
                dist[child_node] = graph[cur_node][child_node];
                parents[child_node] = cur_node;
                // push into queue
                min_q.push({-1*graph[cur_node][child_node], child_node});
            }
        }
    }
    int tot_dist = 0;
    for (int i=1; i<=n; i++) 
    {
        tot_dist += dist[i];
    }
    
    // print the edges in MST
    // cout << "The edges in MST:" << endl;
    // for (int i=1; i<=n; i++)
    // {
    //     if (parents[i] >=0) cout << parents[i] << "-->" << i << endl;
    // }
    
    return tot_dist;
    
}


// ****************************************
// *** Min-Spanning-Tree: Kruskal *********
// ***** Union Find ***********************
// ****************************************

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

// Kruskal's algorithm to get MST for undirectional graph
// returned params: total cost to build the MST, and the new graph for MST (mst_graph)
long long kruskal(unordered_map <long long, unordered_map<long long, long long> > &graph)
{
    //number of nodes
    long long n = graph.size();
    
    // initialize parants, and rank
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
    long long tot_cost = 0;
    unordered_map<long long, unordered_map<long long, lonhg long> > mst_graph;
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
            tot_cost += -1*v1[0];
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


// ****************************************
// *** Binary search the answer ***********
// ****************************************

bool check(vector <int> &vec1, int mid)
{
}
int main()
{
    vector <int> vec1;
    int ans = INT_MAX;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (check(vec1, mid)) // possible
        {
            ans = mid;
            high = mid - 1;
        }
        else low = mid + 1; // impossible
    }
    cout << ans << "\n";
}

// ****************************************
// *** Dijkstra algorithm ***********
// ****************************************
// initialize
vector <int> dist(n + 1, INT_MAX);
vector <bool> vis(n + 1, false);
dist[d] = 0;
void dijkstra(int start_node, unordered_map <int, vector<pair<int, int> > > &graph, vector <int> &dist, vector <bool> &vis)
{
    priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > q1;
    q1.push({0, start_node});
    while (!q1.empty())
    {
        pair <int, int> cur_node = q1.top();
        q1.pop();
        if (vis[cur_node.second]) continue;
        vis[cur_node.second] = true;
        for (auto x : graph[cur_node.second])
        {
            if (cur_node.first + x.second < dist[x.first])
            {
                dist[x.first] = cur_node.first + x.second;
                q1.push({dist[x.first], x.first});
            }
        }
    }
}


// ****************************************
// *** SPFA algorithm ***********
// ****************************************
// The Shortest Path Faster Algorithm (SPFA) is an improvement of the Bellman–Ford algorithm 
// which can deal with negative edge-cost, a node may be put into the queue multiple times
const int MM = 1e9;
vector <int> dist(n + 1, MM);
vector <bool> inq(n + 1, false);
void spfa(int start_node, unordered_map <int, vector <pair <int, int> > > &graph, vector <int> &dist, vector <bool> &inq)
{
    dist[start_node] = 0;
    queue <int> q1;
    q1.push(start_node);
    inq[start_node] = true; // inq is the vector to check if a node is inside the queue
    while (!q1.empty())
    {
        int cur_node = q1.front();
        q1.pop();
        inq[cur_node] = false;
        for (auto x : graph[cur_node])
        {
            if (dist[cur_node] + x.second < dist[x.first])
            {
                dist[x.first] = dist[cur_node] + x.second;
                if (!inq[x.first])
                {
                    q1.push(x.first);
                    inq[x.first] = true;
                }
            }
        }
    }
}
