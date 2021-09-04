#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
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

vector <string > find_neighbors(string current_node, vector <string > list_words)
{
    vector <string > neighbors;
    for (int i=0; i<list_words.size(); i++)
    {
        if(list_words[i]!=current_node)
        {
            if(compare(current_node, list_words[i])==1)
            {
                neighbors.push_back(list_words[i]);
            }
            
        }
    } 
    return neighbors;
}

int bfs(vector<string> list_words, string start_node, string end_node)
{
    if (start_node == end_node)
    {
        return 0;
    }
    vector <string > visited;
    map <string, string > parents = {{start_node, "NA"}};
    vector <string > list_nodes;
    list_nodes.emplace_back(start_node);
    string current_node;
    vector <string > neighbors;
    while (list_nodes.size() != 0)
    {
        current_node = list_nodes[0];
        list_nodes.erase(list_nodes.begin());
        neighbors = find_neighbors(current_node, list_words);

        for (auto a : neighbors)
        {

            
            if (find(visited.begin(), visited.end(), a) == visited.end())
            {
                parents[a] = current_node;
                if (a == end_node)
                {
                    string current = a;
                    int s = 0;
                    while (parents[current]!=start_node)
                    {
                        s += 1;
                        current = parents[current];
                    }
                    return s+1;
                }
                visited.emplace_back(a);
                list_nodes.emplace_back(a);
            }
        }
    }
    return -1;
}

int main() {
    string start_node="hit", end_node="cog";
    vector<string> list_words = {"hot", "dot", "dog", "lot", "log", "cog"};

    int steps = bfs(list_words, start_node, end_node);
    cout << steps << endl;

   
}
