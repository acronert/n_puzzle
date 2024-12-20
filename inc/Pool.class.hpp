#ifndef POOL_HPP
#define POOL_HPP

#include <vector>
#include "Node.class.hpp"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define POOL_SIZE 1000000
#define MAX_MEMORY_KB 10000000

class Pool
{
	private:
		std::vector<Node>	_pool;
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
		std::vector<Node*>	_recycle;
		std::size_t			_size;
		unsigned long long	_memoryUsed;

	public:
		PoolStack();
		~PoolStack() {
			for (auto it: _poolStack)
				delete it;
		};
		Node*	next();
		void	recycle(Node* p);
		void	updateMemoryUsed();
};

#endif
