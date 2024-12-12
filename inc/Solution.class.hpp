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

		void	displayStart(int offset_x);
		void	displayGoal(int offset_x);
		void	displayInfo(int offset_x);
		void	displayPath(int idx, int offset_x);

};

#endif