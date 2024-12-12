#include "Solution.class.hpp"

Solution::Solution(std::vector<Node> path, int loopCount, int maxNode):
	_path(path), _loopCount(loopCount), _maxNode(maxNode), _moveCount(path.size())
{
	_size = path[0].getSize();
}

Solution::~Solution()
{

}

void	Solution::displayStart(int offset_x) {
	std::cout << "Start :\n";
	_path.front().display(offset_x);
	std::cout << "\n";
}

void	Solution::displayGoal(int offset_x) {
	std::cout << "Goal :\n";
	_path.back().display(offset_x);
	std::cout << "\n";
}

void	Solution::displayInfo(int offset_x) {
	std::cout << "\033[" << offset_x << "C" << "Algorithm : " << _algoType << std::endl;
	std::cout << "\033[" << offset_x << "C" << "Time complexity : " << _loopCount << std::endl;
	std::cout << "\033[" << offset_x << "C" << "Space complexity : " << _maxNode << std::endl;
	std::cout << "\033[" << offset_x << "C" << "Number of moves : " << _moveCount << std::endl;
	std::cout << "\033[" << offset_x << "C" << "Time : " << _duration.count()  << "ms" << std::endl;
}

void	Solution::displayPath(int idx, int offset_x) {
	_path[idx].display(offset_x);
}