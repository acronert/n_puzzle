# include <iostream>
# include <sstream>
# include <fstream>
# include <vector>



void	parse(char* filepath) {
	std::ifstream file(filepath);

	if (!file)
		throw std::invalid_argument("Invalid filepath");

	std::string	line;
	std::vector<int>	vec;

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

	// extract size

	for (auto num : vec) {
		std::cout << num << " ";
	}

	return;
}

int	main(int argc, char** argv) {

	// parse and fill grid
	if (argc != 2)
		return -1;
	try {
		parse(argv[1]);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	return 0;

}


// template <nodeType>
// std::stack<nodeType>	aStar(nodeType start, nodeType goal, float (*h)(nodeType *a, nodeType *b))