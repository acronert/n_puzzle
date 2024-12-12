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
	bool	heapify = (newNode->getF() < _v[idx]->getF());
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

bool	Heap::getIndex(const std::vector<uint16_t> &serial, size_t &idx)
{
	auto search = _indexes.find(serial);
	if (search != _indexes.end())
	{
		idx = search->second;
		return(true);
	}
	return(false);
}

size_t	Heap::getSize() const
{
	return this->_size;
}

void	Heap::printHeap()
{
	for (size_t i = 0; i < _v.size(); i++)
	{
		std::cout << "\n=====\n" << "index " << i;
		_v[i]->debug();
		std::cout << "\n=====\n";
	}
	std::cout << std::endl;
}


void	Heap::_heapify_up(size_t idx)
{
	while (idx > 0)
	{
		size_t	root = (idx-1)/2;
		if (_v[idx]->getF() < _v[root]->getF())
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
	if (_v[minc]->getF() < _v[idx]->getF())
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
		return ((_v[left]->getF() < _v[right]->getF()) ? left : right);
	}
}

Node*	Heap::popMin()
{
	if (this->_size > 1)
	{
		_indexes.erase(_v[0]->getGraph());
		_indexes[_v[this->_size -1]->getGraph()] = 0;
		std::swap(this->_v[0], this->_v[this->_size-1]);
		Node*	min = _v.back();
		_v.pop_back();
		this->_size--;
		this->_heapify_down(0);
		return (min);
	}
	else
	{
		Node* min = this->_v.back();
		_v.pop_back();
		this->_size = 0;
		return(min);
	}
}
