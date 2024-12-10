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

std::vector<uint32_t>	build_goal(uint16_t size);

std::vector<uint32_t>	parse(char* filepath);

std::vector<uint32_t>	random_vec(std::size_t size);

void	replay(std::vector<Node> path);

#endif