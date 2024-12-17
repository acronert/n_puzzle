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
		int		_heuristicType;
		std::vector<Solution>	_solutions;
		std::vector<uint16_t>	_start;
		std::vector<uint16_t>	_goal;
		uint16_t				_size;

		Solution				_aStar(Node* start);

	public:
		NPuzzle();
		~NPuzzle();
		void	run(int argc, char** argv);

		bool	isSolvable();
		std::vector<uint16_t>	parse(char* filepath);

		void	parse(int argc, char** argv);
		void	parseInput(char* filepath);
		void	generateRandomInput();
		void	parseOptions(char* option);

		void	displaySolutions();
};

#endif
