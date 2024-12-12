#ifndef POOL_HPP
#define POOL_HPP

#include <vector>
#include "Node.class.hpp"

#define POOL_SIZE 181440


class Pool
{
	private:
		Node		*_pool;
		std::size_t		_idx;
		std::size_t		_size;

	public:

		Pool();
		~Pool();
		Node*	next();
};

class PoolStack
{
	private:
		std::vector<Pool*>	_poolStack;
		std::size_t				_size;

	public:
		PoolStack();
		~PoolStack() {
			for (auto it: _poolStack)
				delete it;
		};
		Node*	next();
};

#endif
