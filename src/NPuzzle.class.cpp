#include "NPuzzle.class.hpp"
#include "Pool.class.hpp"

NPuzzle::NPuzzle() {
	_algoType[0] = true;
	_algoType[1] = false;
	_algoType[2] = false;
}

NPuzzle::~NPuzzle() {

}

void	NPuzzle::run(char* filepath)
{
	// Initialize
	_start = parse(filepath);
	_size = std::sqrt(_start.size());
	_goal = build_goal(_size);

	if (isSolvable())
		std::cout << "Puzzle is solvable\n";
	else
		std::cout << "Puzzle is unsolvable\n";
	// Display start
	Node nodeDisplay = Node(_start, _goal, _size, 0, 0);
	std::cout << "Start:\n";
	nodeDisplay.display(0);
	std::cout << "\n";

	// Execute A*
	for (int type = 0; type < 3; type++) {
		std::string str = "standard";
		if (type == GREEDY)
			str = "greedy";
		else if (type == UNIFORM)
			str = "uniform";


		if (_algoType[type]) {
			Node *node = new Node(_start, _goal, _size, type, 0);

			auto start_time = std::chrono::high_resolution_clock::now();

			
			//Solution sol = astar<Node, std::vector<uint32_t>>(node);
			try {
				Solution sol = this->_aStar(node);

				auto end_time = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

				sol.setDuration(duration);
				sol.setAlgoType(str);
				_solutions.push_back(sol);

				delete node;

				std::cout << str << " path found !\n";

			}
			catch (std::exception &e) {
				delete node;
				std::cout << e.what() << std::endl;
				return ;
			}
		}
	}


	displaySolutions();
}

void	NPuzzle::displaySolutions() {
	// Display
	int max = 0;
	int n_solutions = _solutions.size();
	int	padding;

	// 5 is number of info lines
	padding = std::max(0, 5 - _size) + 1;

		// get max iterations
	for (int i = 0; i < n_solutions; i++) {
		max = std::max(_solutions[i].getMoveCount(), max);
	}

	for (int i = 0; i < max; i++) {
		for (int j = 0; j < n_solutions; j++) {
			// display paths
			_solutions[j].displayPath(std::min(i, _solutions[j].getMoveCount() - 1) ,0);
			for (int k = 0; k < padding; k++)
				std::cout << "\n";
			// display info
			std::cout << "\033[" << _size + padding << "A";
			_solutions[j].displayInfo((_size + 1) * 3);
			for (int k = 0; k < (_size + padding) - 5; k++)
				std::cout << "\n";
		}

		if (i == max - 1)
			break;
		std::cout << "\033[" << (_size + padding) * n_solutions << "A";    // Move cursor up one line
		usleep(40000);
	}

}

std::vector<uint16_t>	NPuzzle::parse(char* filepath) {
	std::ifstream file(filepath);
	std::string			line;
	std::vector<uint16_t>	vec;

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

// void	take_four(std::vector<Node *> &children, PoolStack &pool)
// {
// 	children.clear();
// 	for (size_t i = 0; i < 4; i++)
// 	{
// 		children.push_back(pool.next());
// 	}
// }

Solution	NPuzzle::_aStar(Node *start)
{
	size_t	max_nodes = 1;
	int		loop_count = 0;

	PoolStack pool = PoolStack();
	std::vector<Node *>	children;
	Heap	openSet = Heap();
	openSet.insert(start);
	std::unordered_map<std::vector<uint16_t>, Node*, vecHasher>	closeSet;
	closeSet[start->getGraph()] = start;

	while (openSet.getSize() > 0)
	{
		loop_count++;
		if (openSet.getSize() > max_nodes)
		{
			max_nodes = openSet.getSize();
		}
		Node*	current = openSet.popMin();
		if (current->isGoal())
		{
			return (Solution(current->buildPath(), loop_count, max_nodes));
		}
		children = current->getChildren(pool);
		for (auto child: children)
		{
			
			auto search = closeSet.find(child->getGraph());
			if (search != closeSet.end()) // dans le closeSet == deja croise
			{
				if (*child < *search->second) //si new f better than old f
				{
					size_t idx = 0;
					if (openSet.getIndex(child->getGraph(), idx)) //si deja ds openset on modifie
					{
						openSet.modify(idx, child);
					}
					else //plus ds open set => ajoute a nveau
					{
						openSet.insert(search->second);
						*search->second = *child;
					}
				}
			}
			else //jamais vu on ajoute aux deux sets
			{
				openSet.insert(child);
				closeSet[child->getGraph()] = child;
			}
		}

	}
	throw std::invalid_argument("No path found");



}

bool	NPuzzle::isSolvable() {

	// New Goal (unsnailed goal)
	std::vector<uint16_t>	newGoal;
	for (int i = 0; i < (int)_goal.size(); i++) {
		if (!_goal[i])
			newGoal.push_back(0);
		else
			newGoal.push_back(i + 1);
	}

	// newStart (unsnailed start)
	std::vector<uint16_t>	newStart;
	for (int i = 0; i < (int)_start.size(); i++) {
		if (_start[i] == 0) {
			newStart.push_back(0);
			continue;
		}
		for (int j = 0; j < (int)_goal.size(); j++) {
			if (_goal[j] == _start[i])
				newStart.push_back(newGoal[j]);
		}
	}

	// check solvability
	int	n_inversions = 0;
	for (std::vector<uint16_t>::iterator it = newStart.begin(); it != newStart.end(); it++) {
		for (std::vector<uint16_t>::iterator it2 = it; it2 != newStart.end(); it2++){
			if (*it > *it2 && *it && *it2)
				n_inversions++;
		}
	}

	int	empty_cell_row = 0;
	for (int i = 0; i < (int)newStart.size(); i++) {
		if (newStart[i] == 0) {
			empty_cell_row = _size - (i / _size) - 1;
			break;
		}
	}

	if (_size % 2) {
		if (n_inversions % 2 == 0)
			return true;
	} else {
		if (empty_cell_row % 2 != n_inversions % 2)
			return true;
	}
	return false;
}