# include <iostream>
# include <sstream>
# include <fstream>
# include <vector>
# include <set>
#include "Node.class.hpp"
#include "Astar.hpp"
#include <random>
template <class NodeType>
std::vector<NodeType> astar(NodeType &start);

std::vector<int>	build_goal(std::size_t size);

std::vector<int>	parse(char* filepath) {
	std::ifstream file(filepath);
	std::string			line;
	std::vector<int>	vec;

	if (!file)
		throw std::invalid_argument("Invalid filepath");
	while (std::getline(file, line)) {
		std::istringstream	iss(line);
		std::string			str;

		while (iss >> str) {
			// remove comments
			if (str[0] == '#')
				break;
			// check for non digit characters
			for (auto c : str) {
				if (!std::isdigit(c))
					throw std::invalid_argument("Not a digit");
			}
			// transform to int
			int value = std::stoi(str);
			vec.push_back(value);
		}
	}
	if (!vec.size())
		throw std::invalid_argument("empty grid");

	// extract size
	unsigned int	size = vec[0];

	vec.erase(vec.begin());
	if (vec.size() != size * size || !size)
		throw std::invalid_argument("invalid size");

	// check duplicates
	std::set<int> uniqueNumbers;

	for(int num : vec) {
		if (num < 0 || num >= static_cast<int>(vec.size()))
			throw std::invalid_argument("invalid value : out of range");
		if (!uniqueNumbers.insert(num).second) {
			throw std::invalid_argument("invalid value : duplicate");
		}
	}

	return vec;
}

std::vector<int>	random_vec(size_t size)
{
	std::vector<int> nums(size*size);
	for (int i = 0; i < (int)(size*size); i++)
		nums[i] = i;
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(nums.begin(), nums.end(), g);
	return nums;
}

int	main(int argc, char** argv) {

	(void)argv;
	if (argc != 2)
		return -1;
	try {
		// Initialize
		std::vector<int> start = parse(argv[1]);
		int	size = std::sqrt(start.size());
		std::vector<int> goal = build_goal(size);

		Node *node = new Node(start, goal, size);
		node->setG(0);
		node->h();
		std::cout << node;

		std::cout << "===== Start =====\n";
		node->display();
		std::cout << "=================\n";

		// Execute A*
		std::vector<Node> path = astar(node);

		// Display Path
		std::cout << "Path found, displaying: \n";
		for (auto node = path.rbegin(); node != path.rend(); ++node)
			node->display();

	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}


// template <nodeType>
// std::stack<nodeType>	aStar(nodeType start, nodeType goal, float (*h)(nodeType *a, nodeType *b))
