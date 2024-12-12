# include "NPuzzle.class.hpp"

NPuzzle::NPuzzle() {
	_algoType[0] = true;
	_algoType[1] = true;
	_algoType[2] = true;
}

NPuzzle::~NPuzzle() {

}

void	NPuzzle::run(char* filepath)
{
	// Initialize
	_start = parse(filepath);
	_size = std::sqrt(_start.size());
	_goal = build_goal(_size);

	// Display start
	Node nodeDisplay = Node(_start, _goal, _size, 0);
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
			std::cout << "Calculating path with " << str << " algorithm... ";
			Node *node = new Node(_start, _goal, _size, type);

			auto start_time = std::chrono::high_resolution_clock::now();

			Solution sol = astar<Node, std::vector<uint32_t>>(node);

			auto end_time = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

			sol.setDuration(duration);


			sol.setAlgoType(str);

			_solutions.push_back(sol);

			delete node;

			std::cout << "Path found !\n";
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
		usleep(400000);
	}

}

std::vector<uint32_t>	NPuzzle::parse(char* filepath) {
	std::ifstream file(filepath);
	std::string			line;
	std::vector<uint32_t>	vec;

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