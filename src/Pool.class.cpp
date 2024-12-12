#include <Pool.class.hpp>

Pool::Pool(): _idx(0), _size(POOL_SIZE)
{
	_pool = new Node[_size];
}

Pool::~Pool()
{
	delete[] _pool;
}


Node*	Pool::next()
{
	if (_idx == _size)
		return (nullptr);
	else
	{
		Node* pt = &_pool[_idx];
		_idx++;
		return (pt);
	}
}

PoolStack::PoolStack()
{
	_poolStack.push_back(new Pool());
	_size = 1;
}

Node*	PoolStack::next()
{
	Node* pt = nullptr;
	pt = _poolStack.back()->next();
	if (pt == nullptr)
	{
		_poolStack.push_back(new Pool());
		_size++;
		return this->next();
	}
	return pt;
}
