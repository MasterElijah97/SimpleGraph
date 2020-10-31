#include "Edgenode.h"

Edgenode::Edgenode() {
	this->_y = 0;
	this->_weight = 0;
}

~Edgenode::Edgenode() {
	this->_next.release();
}