#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


int find_root(int node, vector <int> &vec_parents, unordered_map <int, int> map_mapping)
{
    int x = map_mapping[node];
    vector <int> vec1;
    while (x != vec_parents[x])
    {
        vec1.emplace_back(x);
        x = vec_parents[x];
    }
    for (auto a : vec1) vec_parents[a] = x;
    return x;
}

bool union1(int node1, int node2, unordered_map <int, int> &map_comp_sizes, vector <int> &vec_parents, unordered_map <int, int> map_mapping)
{
    int root1 = find_root(node1, vec_parents, map_mapping);
    int root2 = find_root(node2, vec_parents, map_mapping);
    if (root1 == root2) return true;
    if (map_comp_sizes[root1] > map_comp_sizes[root2])
    {
        vec_parents[root2] = root1;
        map_comp_sizes[root1] += map_comp_sizes[root2];
        map_comp_sizes[root2] = 0;
    }
    else
    {
        vec_parents[root1] = root2;
        map_comp_sizes[root2] += map_comp_sizes[root1];
        map_comp_sizes[root1] = 0;
    }
    return false;
}


int main() {

    unordered_map <int, vector<int> > graph = {{1, {2, 3}}, {2, {4}}, {3, {}}, {4, {1}}};
    
    unordered_map <int, int> map_mapping;
    vector <int> vec_parents;
    unordered_map <int, int> map_comp_sizes;
    int count = 0;
    for (auto x : graph)
    {
        map_mapping[x.first] = count;
        vec_parents.emplace_back(count);
        map_comp_sizes[count] = 1;
        count++;
    }
    // step 3: loop through all links to detect loop
    for (auto a : graph)
    {
        for (auto b : a.second)
        {
            if (union1(a.first, b, map_comp_sizes, vec_parents, map_mapping) == true)
            {
                cout << true << endl;
                return 0;
            }
        }
    }
    cout << false << endl;
}
