#include <bits/stdc++.h>
using namespace std;

void add_child(vector <pair <int, int> > &visited, vector <vector <int> > heights, vector <pair <int, int> > &q,
int rows, int cols, int r, int c, int prev_height)
{
    if (r >= 0 && r != rows && c >= 0 && c != cols &&
    find(visited.begin(), visited.end(), make_pair(r, c)) == visited.end() && heights[r][c] >= prev_height)
    {
        visited.push_back({r, c});
        q.push_back({r, c});
    }
}

void bfs(vector <pair <int, int> > &visited, vector <vector <int> > heights, vector <pair <int, int> > &q, int rows, int cols)
{
    int l;
    while (q.size() != 0)
    {
        l = q.size();
        for (int a = 0; a < l; a++)
        {
            add_child(visited, heights, q, rows, cols, q[a].first + 1, q[a].second, heights[q[a].first][q[a].second]);
            add_child(visited, heights, q, rows, cols, q[a].first - 1, q[a].second, heights[q[a].first][q[a].second]);
            add_child(visited, heights, q, rows, cols, q[a].first, q[a].second + 1, heights[q[a].first][q[a].second]);
            add_child(visited, heights, q, rows, cols, q[a].first, q[a].second - 1, heights[q[a].first][q[a].second]);
            q.erase(q.begin());
        }
    }
}

int main()
{
    cin.sync_with_stdio (0); cin.tie (0);
    vector <vector <int> > heights = {{1, 2, 2, 3, 5}, {3, 2, 3, 4, 4}, {2, 4, 5, 3, 1}, {6, 7, 1, 4, 5}, {5, 1, 1, 2, 4}};
    int rows = heights.size(), cols = heights[0].size();
    vector <pair <int, int> > visit_p, visit_a, q;
    for (int c = 0; c < cols; c++)
    {
        visit_p.push_back({0, c});
        q.push_back({0, c});
    }
    for (int r = 1; r < rows; r++)
    {
        visit_p.push_back({r, 0});
        q.push_back({r, 0});
    }
    bfs(visit_p, heights, q, rows, cols);
    q = {};
    for (int c = 0; c < cols; c++)
    {
        visit_a.push_back({rows - 1, c});
        q.push_back({rows - 1, c});
    }
    for (int r = 0; r < rows - 1; r++)
    {
        visit_a.push_back({r, cols - 1});
        q.push_back({r, cols - 1});
    }
    bfs(visit_a, heights, q, rows, cols);
    vector <pair <int, int> > res;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (find(visit_p.begin(), visit_p.end(), make_pair(r, c)) != visit_p.end() &&
            find(visit_a.begin(), visit_a.end(), make_pair(r, c)) != visit_a.end()) res.push_back({r, c});
        }
    }
    cout << "[";
    for (int a = 0; a < res.size(); a++)
    {
        if (a == res.size() - 1) cout << "[" << res[a].first << ",  " << res[a].second << "]";
        else cout << "[" << res[a].first << ",  " << res[a].second << "], ";
    }
    cout << "]" << endl;
}
