/*
input 1:
5
1 2 2
1 3 5
2 4 4
3 5 8
4 5 6
0 0 0

input 2:
5
1 2 2
1 3 5
4 5 6
0 0 0
*/


#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
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

int kruskal(unordered_map <int, unordered_map <int, int> > &graph2, vector <vector <int> > &vec_edge_order,
unordered_map <int, int> &map_comp_sizes, vector <int> &vec_parents, unordered_map <int, int> map_mapping)
{
    sort(vec_edge_order.begin(), vec_edge_order.end(), [](vector <int> a, vector <int> b) {return a[2] < b[2];});
    int mst = 0;
    for (auto b : vec_edge_order)
    {
        if (union1(b[0], b[1], map_comp_sizes, vec_parents, map_mapping) == false)
        {
            mst += b[2];
            graph2[b[0]][b[1]] = b[2];
        }
    }
    return mst;
}


int main() {

    int num_cities;
    cin >> num_cities;
    unordered_map <int, unordered_map <int, int> > graph;
    int a, b, c;
    cin >> a >> b >> c;
    while (a != 0 || b != 0 || c != 0)
    {
        graph[a][b] = c;
        cin >> a >> b >> c;
    }
    for (int x = 1; x <= num_cities; x++)
    {
        if (graph.find(x) == graph.end()) graph[x] = {};
    }
    unordered_map <int, int> map_mapping;
    vector <int> vec_parents;
    unordered_map <int, int> map_comp_sizes;
    int count = 0;
    vector <vector <int> > vec_edge_order = {};
    for (auto x : graph)
    {
        for (auto a : x.second)
        {
            vec_edge_order.push_back({x.first, a.first, a.second});
        }
        map_mapping[x.first] = count;
        vec_parents.emplace_back(count);
        map_comp_sizes[count] = 1;
        count++;
    }
    unordered_map <int, unordered_map <int, int> > graph2;
    int tot_cost = kruskal(graph2, vec_edge_order, map_comp_sizes, vec_parents, map_mapping);
    int m = 0;
    int num_comp = 0;
    for (auto d : map_comp_sizes)
    {
        if (d.second > m) m = d.second;
        if (d.second > 0) num_comp++;
    }
    if (m == num_cities) cout << "It is poosible to connect any of two cities, and the total cost is " << tot_cost << endl;
    else cout << "It is impoosible to connect any of two cities, and the number of components is " << num_comp << endl;
}
