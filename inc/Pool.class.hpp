#ifndef POOL_HPP
#define POOL_HPP

#include <Node.class.hpp>
#include <stack>

#define POOL_SIZE 181440

class Pool
{
	private:
		Node		*_pool;
		size_t		_idx;
		size_t		_size;

	public:

		Pool();
		~Pool();
		Node*	next();
};

class PoolStack
{
	private:
		std::stack<Pool>	_poolStack;
		size_t				_size;

	public:
		PoolStack();
		Node*	next();
};

#endif
