#include <Pool.class.hpp>

Pool::Pool(): _idx(0), _size(POOL_SIZE)
{
	_pool.reserve(POOL_SIZE);
}

Pool::~Pool()
{
	std::cout << "Pool destructor\n";
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
}

Node*	PoolStack::next()
{
	Node* pt = nullptr;
	pt = _poolStack.back()->next();
	if (pt == nullptr)
	{
		if (_size > MAX_ALLOC)
			throw std::overflow_error("too many pool allocations");
		std::cout << "size = " << _size << "\n";
		_poolStack.push_back(new Pool());
		_size++;
		return this->next();
	}
	return pt;
}
