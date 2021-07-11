
/*******************************************
# user input:
# 4 nodes 5 edges
4 5 
1 2 3
1 3 6
2 3 4
2 4 4
3 4 8

********************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <climits>
using namespace std;

int find_min_node(unordered_map<int, int> costs, vector<int> visited)
{
	int minimum_node = -1;
	int minimum_cost = INT_MAX;
	for (const auto x: costs)
	{
		if (find(visited.begin(), visited.end(), x.first) == visited.end() && costs[x.first] < minimum_cost)
		{
			minimum_node = x.first;
			minimum_cost = costs[x.first];
		}
	}
	return minimum_node;
}


int main()
{

	unordered_map<int, unordered_map<int, int>> graph;
	int num_nodes, num_edges;
	cin >> num_nodes >> num_edges;
	for (int x = 0; x < num_edges; x++)
	{
		cout << x << endl;
		int start_node, end_node, cost;
		cin >> start_node >> end_node >> cost;
		if (graph.find(start_node) == graph.end())
		{
			graph[start_node] = unordered_map<int, int>
			{ 	{ 		end_node, cost
				}
			};
		}
		else
		{
			graph[start_node].insert({ end_node, cost });
		}
		// to avoid missing leaf nodes
		if (graph.find(end_node) == graph.end())
		{
			graph[end_node] = {};
		}
	}
	

	vector<int> list_nodes;
	for (const auto x: graph)
	{
		list_nodes.push_back(x.first);
	}
	int start_node = 1;
	int end_node = 4;
	unordered_map<int, int> costs;
	for (const auto a: list_nodes)
	{
		if (a == start_node)
		{
			costs[a] = 0;
		}
		else
		{
			costs[a] = INT_MAX;
		}
	}
	unordered_map<int, int> parents;
	parents[start_node] = -1;
	vector<int> visited {};
	while (true)
	{
		int min_node = find_min_node(costs, visited);
		if (min_node == -1) break;
		visited.push_back(min_node);
		for (const auto a: graph[min_node])
		{
			float c = costs[min_node] + graph[min_node][a.first];
			if (c < costs[a.first])
			{
				costs[a.first] = c;
				parents[a.first] = min_node;
			}
		}
	}

    // print the cost
	cout << "The min cost from " << start_node << " to " << end_node << " is " << costs[
		end_node] << "." << "\n";
		
	// print the path
	vector<int> path;
	int node = end_node;
	while (node!=start_node)
	{
	    path.push_back(node);
	    node = parents[node];
	}
	path.push_back(node);
	reverse(path.begin(), path.end());
	
	cout << "The min-cost path is: " << endl;
	for(auto x: path) cout << x << "-->";
	cout << endl;
	
	return 0;
}
