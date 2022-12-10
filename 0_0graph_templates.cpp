// *************** BFS ********************

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
