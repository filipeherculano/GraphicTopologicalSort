#include "../include/graph.h"

#include <bits/stdc++.h>

Graph::Graph(int n, int m) : number_nodes_(n), number_edges_(m), ambient_(Ambient(50, 100))
{
	// TODO this should be refactored to create a generic DAG
	visited_.resize(number_nodes_, false);

	buildings_.push_back(Building(10, 0, 10, 10, 17));
	buildings_.push_back(Building(10, 0, -10, 10, 17));
	buildings_.push_back(Building(-10, 0, -10, 10, 17));
	buildings_.push_back(Building(-10, 0, 10, 10, 17));

	adj_[0].push_back(1);
	adj_[0].push_back(2);
	adj_[3].push_back(0);

	for (int i = 0; i < number_nodes_; i++)
	{
		for (int j = 0; j < adj_[i].size(); j++)
		{
			connect(buildings_[i], buildings_[adj_[i][j]]);
		}
	}
}

void Graph::connect(Building source, Building destination)
{
	edges_.push_back(Edges(source, destination));
}

void Graph::topological_sort()
{
	for (int v = 0; v < number_nodes_; v++)
	{
		if (visited_[v] == false)
		{
			DFS(v);
		}
	}
}

void Graph::DFS(int u)
{
	visited_[u] = true;
	for (int v = 0; v < adj_[u].size(); v++)
	{
		if (visited_[adj_[u][v]] == false)
		{
			DFS(adj_[u][v]);
		}
	}
	topological_sort_.push_back(u);
}

void Graph::draw_edges()
{
	for (int i = 0; i < number_edges_; i++)
		edges_[i].draw();
}

void Graph::draw_vertex()
{
	for (int i = 0; i < number_nodes_; i++)
		buildings_[i].draw();
}

void Graph::draw_plane()
{
	ambient_.draw();
}

void Graph::destroy_node()
{
	int current = topological_sort_.back();

	for (int i = 0; i < number_edges_; i++)
	{
		if (edges_[i].is_source(buildings_[current]))
			edges_[i].destroy();
	}
	buildings_[current].destroy();

	topological_sort_.pop_back();
}
