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


// BFS on 2D grid
// find the number of hops from start to end, if not reachable, return -1.
int bfs(pair <int, int> start, pair <int, int> end)
{
    int max_cell = 9;
    if (start == end) return 0;
    map <pair <int, int>, int> dist;
    queue <pair <int, int> > q1;
    set <pair <int, int> > vis;
    vis.insert(start);
    dist[start] = 0;
    q1.push(start);
    while (!q1.empty())
    {
        pair <int, int> cur_node = q1.front();
        q1.pop();
        vector <pair <int, int> > vec1;
        int x = cur_node.first, y = cur_node.second;
        vec1 = {{x + 1, y + 2}, {x + 2, y + 1}, {x + 2, y - 1}, {x + 1, y - 2},
        {x - 1, y - 2}, {x - 2, y - 1}, {x - 2, y + 1}, {x - 1, y + 2}};
        for (auto a : vec1)
        {
            if (a.first > 0 && a.first < max_cell && a.second > 0 && a.second < max_cell && !vis.count(a))
            {
                vis.insert(a);
                q1.push(a);
                dist[a] = dist[cur_node] + 1;
                if (a.first == end.first && a.second == end.second) return dist[a];
            }
        }
    }
    return -1;
}
