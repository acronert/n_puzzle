#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <Node.class.hpp>

struct vecHasher
{
	std::size_t operator()(const std::vector<uint32_t> &v) const
	{
		std::size_t seed = v.size();
		for(auto x : v)
		{
			x = ((x >> 16) ^ x) * 0x45d9f3b;
    		x = ((x >> 16) ^ x) * 0x45d9f3b;
    		x = (x >> 16) ^ x;
    		seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  		}
  		return seed;
	}
};

class Heap
{
	private:

		std::vector<Node *>	_v;
		size_t				_size;

		std::unordered_map<std::vector<uint32_t>, size_t, vecHasher>	_indexes;

		void	_heapify_up(size_t idx);
		void	_heapify_down(size_t idx);
		void	_makeHeap();

		size_t	_minChild(size_t idx);

	public:

		Heap();
		~Heap();

		void	insert(Node *newNode);
		void	modify(size_t idx, Node *newNode);
		Node*	popMin();
		const Node*	operator[](size_t idx) const;

		bool	getIndex(std::vector<int> &serial, size_t &idx);

		size_t	getSize() const;
		void	printHeap();
		void	printIndexes();


};


#endif
