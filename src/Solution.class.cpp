#include "Solution.class.hpp"

Solution::Solution(std::vector<Node> path, int loopCount, int maxNode):
	_path(path), _loopCount(loopCount), _maxNode(maxNode), _moveCount(path.size())
{
	_size = path[0].getSize();
}

Solution::~Solution()
{

}

