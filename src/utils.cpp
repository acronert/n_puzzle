# include "utils.hpp"

int	idx(int i, int j, int size)
{
	return (i*size + j);
}

std::vector<uint16_t>	build_goal(uint16_t size)
{
	int square = size * size;
	std::vector<uint16_t> inputs(square,0);

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


std::string	formatSize(size_t bytes) {
	std::string units[] = {"o", "Ko", "Mo", "Go", "To"};
	double size = static_cast<double>(bytes);
	size_t unitIndex = 0;

	while (size > 1024) {
		size /= 1024;
		unitIndex++;
	}

    std::ostringstream result;
	if (units[unitIndex] == "o")
		result << size << " " << units[unitIndex];
	else
		result << std::fixed << std::setprecision(2) << size << " " << units[unitIndex];

    return result.str();
}