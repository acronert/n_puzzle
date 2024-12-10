#include "Heap.hpp"


Heap::Heap() : _v(), _size(0), _indexes()
{}

Heap::~Heap()
{}

void	Heap::insert(Node *newNode)
{
	_indexes[newNode->getGraph()] = this->_size;
	this->_v.push_back(newNode);
	this->_size += 1;
	this->_heapify_up(this->_size-1);
}

void	Heap::modify(size_t idx, Node *newNode)
{
	bool	heapify = (*newNode < *_v[idx]);
	*_v[idx] = *newNode;
	if (heapify)
	{
		this->_heapify_up(idx);
	}
	else{
		this->_heapify_down(idx);
	}
}

const Node*	Heap::operator[](size_t idx) const
{
	return (this->_v[idx]);
}

bool	Heap::getIndex(std::vector<int> &serial, size_t &idx)
{}

size_t	Heap::getSize() const
{}

void	Heap::printHeap()
{}

void	Heap::printIndexes()
{}


void	Heap::_heapify_up(size_t idx)
{
	while (idx > 0)
	{
		size_t	root = (idx-1)/2;
		if (_v[idx] < _v[root])
		{
			_indexes[_v[idx]->getGraph()] = root;
			_indexes[_v[root]->getGraph()] = idx;
			std::swap(_v[idx], _v[root]);
			idx = root;
		}
		else{
			break;
		}
	}
}

void	Heap::_heapify_down(size_t idx)
{
	size_t	minc = this->_minChild(idx);
	if (_v[minc] < _v[idx])
	{
		_indexes[_v[idx]->getGraph()] = minc;
		_indexes[_v[minc]->getGraph()] = idx;

		std::swap(_v[idx], _v[minc]);
		this->_heapify_down(minc);
	}
}

void	Heap::_makeHeap()
{
	if (this->_size < 2)
		return;
	for (size_t i = ((this->_size - 1)/2); i>0; i--)
	{
		this->_heapify_down(i);
	}
	this->_heapify_down(0);
}

size_t	Heap::_minChild(size_t idx)
{
	size_t	left = 2*idx + 1;
	size_t	right = 2*idx + 2;

	if (left > this->_size-1)
		return (idx);
	else if (right > this->_size-1)
		return left;
	else{
		return ((_v[left] < _v[right]) ? left : right);
	}
}
