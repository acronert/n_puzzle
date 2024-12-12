#ifndef NPUZZLE_CLASS_HPP
# define NPUZZLE_CLASS_HPP

//# include "Astar.hpp"
# include "Solution.class.hpp"
# include <chrono>
# include <algorithm>
#include "Pool.class.hpp"
#include "Heap.hpp"

class NPuzzle {
	private:
		bool	_algoType[3];
		std::vector<Solution>	_solutions;
		std::vector<uint32_t>	_start;
		std::vector<uint32_t>	_goal;
		uint16_t				_size;

		Solution				_aStar(Node* start);

	public:
		NPuzzle();
		~NPuzzle();
		void	run(char* filepath);

		std::vector<uint32_t>	parse(char* filepath);
		void	displaySolutions();
};

#endif
