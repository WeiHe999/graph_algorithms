/*
https://www.youtube.com/watch?v=h9iTnkgv05E&list=PLot-Xpze53ldBT_7QA8NVot219jFNr_GI&index=6
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;

int compare(string a, string b)
{
    if (a.length() != b.length()) return 0;
    for (int x = 0; x < a.length(); x++)
    {
        if (a.substr(0, x) + a.substr(x + 1) == b.substr(0, x) + b.substr(x + 1)) return 1;
    }
    return 0;
}

void bfs(vector <string> vec1, string start_word, string end_word, int &s, vector <string> &visited)
{
    if (start_word == end_word) return;
    string current_node;
    for (string x : vec1)
    {
        if (find(visited.begin(), visited.end(), x) == visited.end() && compare(start_word, x) == 1)
        {
            s++;
            visited.emplace_back(x);
            bfs(vec1, x, end_word, s, visited);
        }
    }
    return;
}

int main() {
    string start_word="hit", end_word="cog";
    vector<string> list_words = {"hot", "dot", "dog", "lot", "log", "cog"};
    //create graph
    unordered_map <string, vector<string> > graph;
    for (int i=0; i<list_words.size(); i++)
    {
        for(int j=i+1; j<list_words.size(); j++)
        {
            
            int ret = compare(list_words[i], list_words[j]);
            if (ret==1)
            {
                graph[list_words[i]].push_back(list_words[j]);
                graph[list_words[j]].push_back(list_words[i]);
            }
        }
    }
    //print graph
    for(auto x: graph)
    {
        cout << x.first << ": ";
        for (auto y: graph[x.first])
        {
            cout << y << ", ";
        }
        cout << endl;
    }

    // int s = 1;
    // vector <string> visited = {start_word};
    // bfs(vec1, start_word, end_word, s, visited);
    // cout << s << endl;
}
