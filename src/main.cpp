# include <iostream>
# include <sstream>
# include <fstream>
# include <vector>
# include <set>
#include "Node.class.hpp"

template <class NodeType>
std::vector<NodeType> astar(NodeType &start, NodeType &goal);


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

int	main(int argc, char** argv) {

	// parse and fill grid
	if (argc != 2)
		return -1;
	try {
		std::vector<int> vec = parse(argv[1]);
		for (auto num : vec) {
			std::cout << num << " ";
		}
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	// instancie node start et goal
	// astar(start, goal, h)
	// print
	Node goal = Node(3);
	goal.display();
	std::vector<int> start_vec = {1,2,3,8,4,0,7,6,5};
	Node start = Node(start_vec, 3);

	std::vector<Node> path = astar(start, goal);
	return 0;

}


// template <nodeType>
// std::stack<nodeType>	aStar(nodeType start, nodeType goal, float (*h)(nodeType *a, nodeType *b))
