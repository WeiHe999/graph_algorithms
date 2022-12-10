// *************** BFS ********************

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

// *************** DFS ********************
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
    int loop_lenth = -1;
    bool found_loop = false;
    dfs(1, graph, found_loop, visited, dist, loop_lenth);
    cout << loop_lenth << endl;   
}



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

// *************** Tree ********************

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

/*
tree travel properties in a tree of N nodes and N-1 edges:
Tree property 1: start from node A, visit all nodes and return back to node A, the total travel distance is 2*number_edges = 2*(N-1), 

Tree property 2:  start from node A, visit all nodes and finally stop at any node, what is the min total distance? 
Solution: the min total travel distance = 2*(N-1) - max_distance_from_node_A (DFS to find it)

Tree property 3:  you can start from any node, and visit all nodes, what is the min distance you need?
Solution: start from an diameter endpoint, end at another diameter endpoint, the min total travel distance = 2*(N-1) - tree_diameter

Tree diameter property 4: how to find the max distance from any node to another node in O(N) complexity?
solution: 1) find both diameter endpoints, get dist1 and dist2 vectors, 2) loop through all nodes, for each node, 
the max_dist_node_k = max(dist1[k], dist2[k]), find the max dist among all n nodes.
*/