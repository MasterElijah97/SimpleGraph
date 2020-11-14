#ifndef GRAPH_H
#define GRAPH_H

#include "Edgenode.h"

class Graph{
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
	//-----------------------------------------------------------------------
	//Functions for BFS and DFS
	void initialize_search_for_BFS() {
		for (int i = 1; i <= _n_vertices; i++) {
			_processed[i] = false;
			_discovered[i] = false;
			_parent[i] = -1;
		}
	}
	void initialize_search_for_DFS() {
		for (int i = 1; i <= _n_vertices; i++) {
			_processed[i] = false;
			_discovered[i] = false;
			_parent[i] = -1;
			_entry_time[i] = 0;
			_exit_time[i] = 0;
		}
	}

	void initialize_search_for_Dijkstra() {
        for (int i = 1; i <= _n_vertices; i++) {
			_intree[i] = false;
			_distance[i] = INF;
			_parent[i] = -1;
		}
	}
	//Breadth First Search
	void BFS(int start) {

		this->initialize_search_for_BFS();

		std::queue<int> q; // очередь на посещение

		int v; // эта нода
		int y; // следующая нода

		std::shared_ptr<Edgenode> ptrToEdgeNode;

		q.push(start);

		_discovered[start] = true;

		while (!q.empty()) {
			v = q.front();
			q.pop();

			//process_early();

			_processed[v] = true;

			ptrToEdgeNode = this->_edges[v];

			while (ptrToEdgeNode) {
				y = ptrToEdgeNode->_y;

				if (!_processed[y] || this->_directed) {
					//process_edge();
				}

				if (!_discovered[y]) {
					q.push(y);
					_discovered[y] = true;
					_parent[y] = v;
				}

				ptrToEdgeNode = ptrToEdgeNode->_next;
			}
			//process_late();
		}
	}
	//Applications of BFS
	void find_path(int start, int finish) {
		if ((start == finish) || (finish == -1)) {
			std::cout << start << "\n";
		} else {
			find_path(start, _parent[finish]);
			std::cout << finish << "\n";
		}
	}

	void connected_components() {
		int c = 0; // номер компоненты

		this->initialize_search_for_BFS();

		for (int i = 1; i <= this->_n_vertices; i++) {
			if (!_discovered[i]) {
				c++;
				std::cout << c << "\n";
				this->BFS(i);
				std::cout << "\n";
			}
		}
	}
	//-----------------------------------------------------------------------
	//Depth First Search
	void DFS(int v)
	{
    	this->initialize_search_for_DFS();

    	std::shared_ptr<Edgenode> tmp_ptr_to_Edgenode;

    	int y;
    	int time;

    	if (_discovered[v]) {
        	return;
    	}
    	time = time + 1;
    	_discovered[v] = true;
    	time++;
    	_entry_time[v] = time;
    	//process_early();
    	tmp_ptr_to_Edgenode = this->_edges[v];

    	while (tmp_ptr_to_Edgenode) {
        	y = tmp_ptr_to_Edgenode->_y;

        	if (!_discovered[y]) {
            	_parent[y] = v;
            	//process_edge();
            	this->DFS(y);
        	} else if ((!_processed[y]) || (this->_directed)) {
            	//process_late();
            	if (_discovered[v]) {
                	return;
            	}
            	tmp_ptr_to_Edgenode = tmp_ptr_to_Edgenode->_next;
        	}
        	//process_late();
        	time++;
        	_exit_time[v]= time;
        	_processed[v] = true;
    	}
}
	//-----------------------------------------------------------------------


	void initialize(unsigned int maximum_vertices, bool directed) {
		_directed = directed;

		_n_vertices = 0;
		_n_edges = 0;;

		for (int i = 0; i <= _maximum_vertices; ++i) {
			_degree[i] =  0;
		}

		for (int i = 0; i <= _maximum_vertices; ++i) {
			_edges[i] =  0;
		}
	}

	void insert_edge(int x, int y, bool directed) {
		auto ptrToEdgeNode = std::make_shared<Edgenode>();

		ptrToEdgeNode->_weight = 0;
		ptrToEdgeNode->_y = y;
		ptrToEdgeNode->_next = this->_edges[x];

		this->_edges[x] = std::move(ptrToEdgeNode);
		this->_degree[x]++;

		if (!directed) {
			this->insert_edge(y, x, true);
		} else {
			this->_n_edges++;
		}
	}

	void read_graph(bool directed) {
		int m; // количество вершин
		int x, y; // вершины в ребре (x, y)

		this->initialize(m, directed);

		std::cin >> this->_n_vertices;
		std::cin >> m;

		for (int i = 1; i <= m; i++) {
			std::cin >> x >> y;
			this->insert_edge(x, y, directed);
		}
	}

	void print_graph() {
		std::shared_ptr<Edgenode> ptrToEdgeNode;

		for (int i = 1; i <= _n_vertices; i++) {
			std::cout << i << "\n";

			ptrToEdgeNode = this->_edges[i];

			while (ptrToEdgeNode) {
				std::cout << ptrToEdgeNode->_y;
				ptrToEdgeNode = ptrToEdgeNode->_next;
			}

		}
	}

void dijkstra(int start) {

  this->initialize_search_for_Dijkstra();
  // fills intree[], distance[] and parent[]

  std::shared_ptr<Edgenode> tmp_ptr_to_Edgenode;

  int v, y;
  int weight;
  int dist;

  _distance[start]  = 0;
  v = start;

  while (!_intree[v]) {
    _intree[v] = true;
    tmp_ptr_to_Edgenode = this->_edges[v];

    while(tmp_ptr_to_Edgenode) {
      y = tmp_ptr_to_Edgenode->_y;
      weight = tmp_ptr_to_Edgenode->_weight;

        if (_distance[y] > (_distance[v] + weight)) {
          _distance[y] = _distance[v] + weight;
          _parent[y] = v;
        }

      tmp_ptr_to_Edgenode = tmp_ptr_to_Edgenode->_next;
    }

    v = 1;
    dist = INF;

    for (int i = 1; i <=  this->_nvertices; ++i) {
      if ((_intree[i] = false) && (dist > _distance[i])) {
        dist = distance[i];
        v = i;
      }
    }
  }
}
};

#endif //SIMPLE_GRAPH_H