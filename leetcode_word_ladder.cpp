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

vector <string > find_neighbors(string current_word, vector <string > list_words)
{
    vector <string > neighbors;
    for (int i = 0; i < list_words.size(); i++)
    {
        if (list_words[i] != current_word)
        {
            if (compare(current_word, list_words[i]) == 1) neighbors.push_back(list_words[i]);
        }
    } 
    return neighbors;
}

int bfs(vector <string> list_words, string start_word, string end_word, unordered_map <string, string > &parents)
{
    if (start_word == end_word)
    {
        return 0;
    }
    vector <string > visited;
    vector <string> list_nodes = {start_word};
    string current_word;
    vector <string> neighbors;
    while (list_nodes.size() != 0)
    {
        current_word = list_nodes[0];
        list_nodes.erase(list_nodes.begin());
        neighbors = find_neighbors(current_word, list_words);
        for (auto a : neighbors)
        {
            if (find(visited.begin(), visited.end(), a) == visited.end())
            {
                parents[a] = current_word;
                if (a == end_word)
                {
                    string current = a;
                    int s = 0;
                    while (current != "-1") {s++; current = parents[current];}
                    return s;
                }
                visited.emplace_back(a);
                list_nodes.emplace_back(a);
            }
        }
    }
    return -1;
}

int main()
{
    vector <string> list_words = {"hot", "dot", "dog", "lot", "log", "cog"};
    string start_word = "hit";
    string end_word = "cog";
    unordered_map <string, string > parents = {{start_word, "-1"}};
    int steps = bfs(list_words, start_word, end_word, parents);
    cout << steps << endl;
    cout << "final path: ";
    string current = end_word;
    vector <string> vec1;
    while (current != "-1") {vec1.insert(vec1.begin(), current); current = parents[current];}
    for (auto a : vec1) cout << a << " ";
    cout << endl;
}
