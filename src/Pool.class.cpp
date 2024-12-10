#include <Pool.class.hpp>

Pool::Pool(): _idx(0), _size(POOL_SIZE)
{
	_pool = new Node[_size];
	
}
