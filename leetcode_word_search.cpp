#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdio.h>
using namespace std;

template < typename T > void
print (T t)
{
 for (const auto & e:t) cout << e << " ";
  cout << endl;
}

int dfs(vector <vector <char> > board, string word, vector <pair <int, int> > visited, int r, int c, int row, int col, int i)
{
    if (i == word.size()) return true;
    if (row < 0 || col < 0 || row >= r || col >= c || word[i] != board[row][col]) return false;
    for (auto a : visited)
    {
        if (a.first == row && a.second == col) return false;
    }
    visited.push_back({row, col});
    int res = dfs(board, word, visited, r, c, row + 1, col, i + 1);
    if (res == 0)
    {
        res = dfs(board, word, visited, r, c, row - 1, col, i + 1);
        if (res == 0)
        {
            res = dfs(board, word, visited, r, c, row, col + 1, i + 1);
            if (res == 0)
            {
                res = dfs(board, word, visited, r, c, row, col - 1, i + 1);
            }
        }
    }
    visited.erase(visited.begin() + 1);
    return res;
}

int word_search(vector <vector <char> > board, string word)
{
    int r = board.size();
    int c = board[0].size();
    vector <pair <int, int> > visited;
    for (int a = 0; a < r; a++)
    {
        for (int b = 0; b < c; b++)
        {
            if (dfs(board, word, visited, r, c, a, b, 0) == 1) return 1;
        }
    }
    return 0;
}

int main()
{
    cin.sync_with_stdio (0);
    cin.tie (0);
    vector <vector <char> > board = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    string word = "ABCCED";
    if (word_search(board, word) == 1) cout << "true" << endl;
    else cout << "false" << endl;
}
