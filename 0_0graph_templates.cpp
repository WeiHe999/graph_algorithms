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

