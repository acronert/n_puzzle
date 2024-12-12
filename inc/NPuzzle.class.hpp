#ifndef NPUZZLE_CLASS_HPP
# define NPUZZLE_CLASS_HPP

# include "Node.class.hpp"
# include "Astar.hpp"
# include "Solution.class.hpp"
# include <chrono>
# include <algorithm>

class NPuzzle {
	private:
		bool	_algoType[3];
		std::vector<Solution>	_solutions;
		std::vector<uint32_t>	_start;
		std::vector<uint32_t>	_goal;
		uint16_t				_size;

	public:
		NPuzzle();
		~NPuzzle();
		void	run(char* filepath);

		std::vector<uint32_t>	parse(char* filepath);
		void	displaySolutions();
};

#endif