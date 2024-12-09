#ifndef UTILS_HPP
# define UTILS_HPP

# include <vector>
# include <random>
# include <iostream>
# include <sstream>
# include <fstream>
# include <vector>
# include <set>
# include <algorithm>
# include <unistd.h>
# include "Node.class.hpp"

class Node;

std::vector<int>	build_goal(std::size_t size);

std::vector<int>	parse(char* filepath);

std::vector<int>	random_vec(std::size_t size);

void	replay(std::vector<Node> path);

#endif