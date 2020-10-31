#ifndef GRAPH_H
#define GRAPH_H

#include "Edgenode.h"

class Graph {
public:
	std::vector<std::shared_ptr<Edgenode>> _edges; //Информация о смежности
	std::vector<int> _degree; //Степень каждой вершины
	int _n_vertices; //Количество вершин в графе
	int _n_edges; // Количество рёбер в графе
	bool _directed; // Ориентированный граф?
	unsigned int _maximum_vertices;
	const int INF = 1000 * 1000 * 1000;
	//-----------------------------------------------------------------------
	//Variables for BFS and DFS
	//BFS
	std::vector<bool> _processed; //обработанные вершины
	std::vector<bool> _discovered; //открытые вершины
	std::vector<int> _parent; // предыдущая нода
	//Dijkstra
	std::vector<int> _distance(MAXV+1);
    std::vector<bool> _intree(MAXV+1);
	//DFS
	std::vector<int> _entry_time;
	std::vector<int> _exit_time;
};

#endif //SIMPLE_GRAPH_H