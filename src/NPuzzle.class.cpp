# include "NPuzzle.class.hpp"

NPuzzle::NPuzzle() {
	_algoType[0] = true;
	_algoType[1] = true;
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

	// Execute A*
	for (int type = 0; type < 3; type++) {
		if (_algoType[type]) {
			Node *node = new Node(_start, _goal, _size, type);

			// auto start_time = std::chrono::high_resolution_clock::now();

			Solution sol = astar<Node, std::vector<uint32_t>>(node);

			// auto end_time = std::chrono::high_resolution_clock::now();
			
			// sol.setDuration(end_time - start_time);

			std::string str = "standard";
			if (type == GREEDY)
				str = "greedy";
			else if (type == UNIFORM)
				str = "uniform";
			sol.setAlgoType(str);

			_solutions.push_back(sol);

			delete node;
		}
	}

	// Display
	int max = 0;
	int n_solutions = _solutions.size();
	for (int i = 0; i < n_solutions; i++) {
		max = std::max(_solutions[i].getMoveCount(), max);

		_solutions[i].displayInfo(std::max(i * (_size * 5) + 1, i * 20));
		if (i < n_solutions - 1)
			std::cout << "\033[" << 5 << "A";
	}
	while (1) {
		for (int i = 0; i < max; i++) {
			for (int j = 0; j < n_solutions; j++) {
				if (i < _solutions[j].getMoveCount()) {
					_solutions[j].displayPath(i , std::max(j * (_size * 5) + 1, j * 20));
					std::cout << "\033[" << _size << "A";    // Move cursor up one line
				}
			}
			usleep(400000);
		}
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