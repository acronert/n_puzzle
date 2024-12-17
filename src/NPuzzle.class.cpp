#include "NPuzzle.class.hpp"
#include "Pool.class.hpp"

NPuzzle::NPuzzle() {
	_algoType[0] = false;
	_algoType[1] = false;
	_algoType[2] = false;

	_heuristicType = 0;
}

NPuzzle::~NPuzzle() {

}

void	NPuzzle::run(int argc, char** argv)
{
	parse(argc, argv);

	if (isSolvable())
		std::cout << "Puzzle is solvable\n";
	else
		std::cout << "Puzzle is unsolvable\n";

	// Display start
	Node nodeDisplay = Node(_start, _goal, _size, 0, 0);
	std::cout << "Start:" << std::endl;
	nodeDisplay.display(0);
	std::cout << "\n";

	// Execute A*
	for (int aType = 0; aType < 3; aType++) {
		std::string strAlgo = "Standard A*";
		if (aType == GREEDY)
			strAlgo = "Greedy";
		else if (aType == UNIFORM)
			strAlgo = "Uniform Search";

		std::string strHeuristic = "Manhattan Distance";
		if (_heuristicType == MISPLACED)
			strHeuristic = "Misplaced Tiles";
		else if (_heuristicType == GASHNIG)
			strHeuristic = "Gashnig";

		if (_algoType[aType]) {

			Node *node = new Node(_start, _goal, _size, aType, _heuristicType);
			try {

				auto start_time = std::chrono::high_resolution_clock::now();
				Solution sol = this->_aStar(node);

				auto end_time = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

				sol.setDuration(duration);
				sol.setAlgoType(strAlgo);
				sol.setHeurisicType(strHeuristic);
				_solutions.push_back(sol);

				delete node;

				std::cout << strAlgo << " path found !\n";
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

	padding = std::max(0, DISPLAY_INFO_LINES - _size) + 1;

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
			for (int k = 0; k < (_size + padding) - DISPLAY_INFO_LINES; k++)
				std::cout << "\n";
		}

		if (i == max - 1)
			break;
		std::cout << "\033[" << (_size + padding) * n_solutions << "A";    // Move cursor up one line
		usleep(std::min(30000000 / max, 300000));
	}

}

void	NPuzzle::parseInput(char* filepath) {

	std::ifstream 			file(filepath);
	std::string				line;

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
			_start.push_back(value);
		}
	}
	if (!_start.size())
		throw std::invalid_argument("empty grid");

	// extract size
	_size = _start[0];

	_start.erase(_start.begin());
	if (_start.size() != _size * _size || !_size)
		throw std::invalid_argument("invalid size");

	// check duplicates
	std::set<int> uniqueNumbers;

	for(int num : _start) {
		if (num < 0 || num >= static_cast<int>(_start.size()))
			throw std::invalid_argument("invalid value : out of range");
		if (!uniqueNumbers.insert(num).second) {
			throw std::invalid_argument("invalid value : duplicate");
		}
	}

	_goal = build_goal(_size);
}

void	NPuzzle::parseOptions(char* option) {
	for (int i = 1; option[i]; i++) {
		if (option[i] == 's' || option[i] == 'S')
			_algoType[STANDARD] = true;
		else if (option[i] == 'g' || option[i] == 'G')
			_algoType[GREEDY] = true;
		else if (option[i] == 'u' || option[i] == 'U')
			_algoType[UNIFORM] = true;
		else if (option[i] == 'h') {
			i++;
			if (option[i]) {
				if (option[i] == '0')
					_heuristicType = 0;
				else if (option[i] == '1')
					_heuristicType = 1;
				else if (option[i] == '2')
					_heuristicType = 2;
				else if (option[i] == '3')
					_heuristicType = 3;
				else
					throw std::invalid_argument("unknow heuristic");
			}
			else
				throw std::invalid_argument("no heuristic specified");
		}
		else
			throw std::invalid_argument("unknow option");
	}
}

void	NPuzzle::parse(int argc, char** argv) {
	bool	input_present = false;

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] != '-') {
			parseInput(argv[i]);
			input_present = true;
		}
		else {
			parseOptions(argv[i]);
		}
	}
	if (!input_present)
		throw std::invalid_argument("No input given");
	if (!_algoType[0] && !_algoType[1] && !_algoType[2])
		_algoType[0] = true;

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
		// if (closeSet.size() > max_nodes)
		// {
		// 	max_nodes = closeSet.size();
		// }
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