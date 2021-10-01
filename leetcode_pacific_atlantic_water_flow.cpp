#include <bits/stdc++.h>
using namespace std;

vector <vector <int> > heights = {{1, 2, 2, 3, 5}, {3, 2, 3, 4, 4}, {2, 4, 5, 3, 1}, {6, 7, 1, 4, 5}, {5, 1, 1, 2, 4}};
int rows = heights.size(), cols = heights[0].size();
vector <pair <int, int> > visit1, visit2;

void dfs(int r, int c, vector <pair <int, int> > &visit, int prev_height)
{
    if (find(visit.begin(), visit.end(), make_pair(r, c)) != visit.end() || r < 0 || r == rows || c < 0 || c == cols || heights[r][c] < prev_height) return;
    visit.push_back({r, c});
    dfs(r + 1, c, visit, heights[r][c]);
    dfs(r - 1, c, visit, heights[r][c]);
    dfs(r, c + 1, visit, heights[r][c]);
    dfs(r, c - 1, visit, heights[r][c]);
}

vector <pair <int, int> > atlantic_heights()
{
    for (int c = 0; c < cols; c++)
    {
        dfs(0, c, visit1, heights[0][c]);
        dfs(rows - 1, c, visit2, heights[rows - 1][c]);
    }
    for (int r = 0; r < rows; r++)
    {
        dfs(r, 0, visit1, heights[r][0]);
        dfs(r, cols - 1, visit2, heights[r][cols - 1]);
    }
    vector <pair <int, int> > res;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (find(visit1.begin(), visit1.end(), make_pair(r, c)) != visit1.end() &&
            find(visit2.begin(), visit2.end(), make_pair(r, c)) != visit2.end()) res.push_back({r, c});
        }
    }
    return res;
}

int main()
{
    cin.sync_with_stdio (0); cin.tie (0);
    vector <pair <int, int> > res = atlantic_heights();
    cout << "[";
    for (int a = 0; a < res.size(); a++)
    {
        if (a == res.size() - 1) cout << "[" << res[a].first << ",  " << res[a].second << "]";
        else cout << "[" << res[a].first << ",  " << res[a].second << "], ";
    }
    cout << "]" << endl;
}
