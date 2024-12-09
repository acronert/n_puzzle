# include "utils.hpp"

int	idx(int i, int j, int size)
{
	return (i*size + j);
}

std::vector<int>	build_goal(std::size_t size)
{
	int square = size * size;
	std::vector<int> inputs(square,0);

	int	top = 0;
	int bottom = size - 1;
	int	left = 0;
	int right = size -1;
	int	k = 1;
	while (k <  square)
	{
		for (int i = left; i<= right; i++){
			inputs[idx(top, i, size)] = k % square;
			k++;
		}
		top++;
		for (int j = top; j<= bottom; j++)
		{
			inputs[idx(j, right, size)] = k % square;
			k++;
		}
		right--;
		if (top < bottom)
		{
			for (int i = right; i >= left; i--)
			{
				inputs[idx(bottom,i,size)] = k % square;
				k++;
			}
			bottom--;

		}
		if (left < right)
		{
			for (int i = bottom; i >= top; i--)
			{
				inputs[idx(i, left, size)] = k % square;
				k++;
			}
			left++;

		}
	}
	return inputs;
}

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

std::vector<int>	random_vec(std::size_t size)
{
	std::vector<int> nums(size*size);
	for (int i = 0; i < (int)(size*size); i++)
		nums[i] = i;
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(nums.begin(), nums.end(), g);
	return nums;
}

void	replay(std::vector<Node> path) {
	for (auto node = path.rbegin(); node != path.rend(); ++node) {
		node->display();
		usleep(400000);

		for (int i = 0; i < node->getSize() + 4; ++i) {
			std::cout << "\033[A"    // Move cursor up one line
					<< "\033[2K"; // Clear the entire line
		
		}
	}
}
