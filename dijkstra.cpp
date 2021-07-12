/*******************************************
# user input:
# 4 nodes 5 edges
4 5 
1 2 3
1 3 6
2 3 4
2 4 4.5
3 4 8

********************************************/
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <cmath>
using namespace std;

int find_min_node(unordered_map<int, float> costs, vector<int> visited)
{
	int minimum_node = -1;
	float minimum_cost = INFINITY;
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

float dijkstra(	unordered_map<int, unordered_map<int, float>> &graph,
	unordered_map<int, float> &costs,
	unordered_map<int, int> &parents,
	int start_node,
	int end_node)
{

	costs[start_node] = 0;
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

	return costs[end_node];

}

vector<int> find_min_cost_path(	unordered_map<int, int> &parents,
	int start_node,
	int end_node)
{
	vector<int> path;
	int node = end_node;
	while (node != start_node)
	{
		path.push_back(node);
		node = parents[node];
	}
	path.push_back(node);
	reverse(path.begin(), path.end());
	return path;
}

int main()
{
	unordered_map<int, unordered_map<int, float>> graph;
	unordered_map<int, float> costs;
	int num_nodes, num_edges;
	cin >> num_nodes >> num_edges;
	for (int x = 0; x < num_edges; x++)
	{
		cout << x << endl;
		int start_node, end_node;
		float cost;
		cin >> start_node >> end_node >> cost;
		if (graph.find(start_node) == graph.end())
		{
			graph[start_node] = unordered_map<int, float>
			{ 	{ 		end_node, cost
				}
			};
			costs[end_node] = INFINITY;
		}
		else
		{
			graph[start_node].insert({ end_node, cost });
		}
		// to avoid missing leaf nodes
		if (graph.find(end_node) == graph.end())
		{
			graph[end_node] = {};
			costs[end_node] = INFINITY;
		}
	}

	int start_node = 1;
	int end_node = 4;
	unordered_map<int, int> parents;
	parents[start_node] = -1;
	float min_cost = dijkstra(graph, costs, parents, start_node, end_node);

	// print the cost
	cout << "The min cost from " << start_node << " to " << end_node << " is " << min_cost << "." << "\n";

	//print the min-cost path
	vector<int> path = find_min_cost_path(parents, start_node, end_node);
	cout << "The min-cost path:" << endl;
	for (auto x: path) cout << x << "-->";
	cout << endl;

	return 0;
}
