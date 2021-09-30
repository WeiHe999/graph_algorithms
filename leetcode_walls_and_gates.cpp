#include <bits/stdc++.h>
using namespace std;

vector <vector <int> > rooms = {{2147483647, -1, 0, 2147483647}, {2147483647, 2147483647, 2147483647, -1},
{2147483647, -1, 2147483647, -1},  {0, -1, 2147483647, 2147483647}};
int rows = rooms.size();
int cols = rooms[0].size();
vector <pair <int, int> > visited;
vector <pair <int, int> > q;

void add_room(int r, int c)
{
    if (r >= 0 && r != rows && c >= 0 && c != cols && find(visited.begin(), visited.end(), make_pair(r, c)) == visited.end() && rooms[r][c] != -1)
    {
        visited.push_back({r, c});
        q.push_back({r, c});
    }
}

void walls_and_gates()
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (rooms[r][c] == 0)
            {
                visited.push_back({r, c});
                q.push_back({r, c});
            }
        }
    }
    int d = 0;
    int l;
    while (q.size() != 0)
    {
        l = q.size();
        for (int a = 0; a < l; a++)
        {
            rooms[q[0].first][q[0].second] = d;
            add_room(q[0].first + 1, q[0].second);
            add_room(q[0].first - 1, q[0].second);
            add_room(q[0].first, q[0].second + 1);
            add_room(q[0].first, q[0].second - 1);
            q.erase(q.begin());
        }
        d++;
    }
}

int main()
{
    cin.sync_with_stdio (0); cin.tie (0);
    walls_and_gates();
    for (auto a : rooms)
    {
        for (auto b : a) cout << b << " ";
        cout << endl;
    }
}
