#ifndef EDGENODE_H
#define EDGENODE_H

class Edgenode {
public:
	Edgenode();
	~Edgenode();
	int _y; // Информация о смежности
	int _weight; //Вес ребра,  если есть
	std::shared_ptr<Edgenode> _next;  //Следующее  ребро в списке
};

#endif //EDGENODE_H