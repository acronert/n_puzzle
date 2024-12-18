#include <Pool.class.hpp>

Pool::Pool(): _idx(0), _size(POOL_SIZE)
{
	_pool.reserve(POOL_SIZE);
}

Pool::~Pool()
{
}


Node*	Pool::next()
{
	if (_idx == _size)
		return (nullptr);
	else
	{
		_pool.emplace_back(Node());
		Node* pt = &_pool[_idx];
		_idx++;
		return (pt);
	}
}

PoolStack::PoolStack()
{
	_poolStack.push_back(new Pool());
	_size = 1;
	_count = 0;
}

Node*	PoolStack::next()
{
	Node* pt = nullptr;
	if (!_recycle.empty())
	{
		pt = _recycle.back();
		_recycle.pop_back();
		return (pt);
	}
	pt = _poolStack.back()->next();
	if (pt == nullptr)
	{
		if (_size > MAX_ALLOC)
			throw std::overflow_error("too many pool allocations");
		_poolStack.push_back(new Pool());
		_size++;
		return this->next();
	}
	return pt;
}

void	PoolStack::recycle(Node *p)
{
	_recycle.push_back(p);
}
