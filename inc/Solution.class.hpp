#ifndef SOLUTION_CLASS_HPP
# define SOLUTION_CLASS_HPP

# include <Node.class.hpp>
# include <chrono>
# include <vector>

class Solution {
	private:
		std::vector<Node>			_path;
		std::string					_algoType;
		int							_size;
		int							_loopCount;
		int							_maxNode;
		int							_moveCount;
		std::chrono::milliseconds	_duration;

		
	public:
		Solution(std::vector<Node> path, int loopCount, int maxNode);
		~Solution();

		void	setAlgoType(std::string algoType)	{ _algoType = algoType; }
		void	setDuration(std::chrono::milliseconds duration)	{ _duration = duration; };

		int	getMoveCount() { return _moveCount; }

		void	displayInfo(int offset_x) {
			std::cout << "\033[" << offset_x << "C" << "algoType : " << _algoType << std::endl;
			std::cout << "\033[" << offset_x << "C" << "loopCount : " << _loopCount << std::endl;
			std::cout << "\033[" << offset_x << "C" << "maxNode : " << _maxNode << std::endl;
			std::cout << "\033[" << offset_x << "C" << "moveCount : " << _moveCount << std::endl;
			std::cout << "\033[" << offset_x << "C" << "duration : " << std::endl;
		}

		void	displayPath(int idx, int offset_x) {
			_path[idx].display(offset_x);
		}

};

#endif