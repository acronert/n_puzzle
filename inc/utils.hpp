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

std::vector<uint16_t>	build_goal(uint16_t size);
std::vector<uint16_t>	parse(char* filepath);
void	                replay(std::vector<Node> path);
std::string	            formatSize(size_t bytes);
std::vector<uint16_t>	randomVec(uint16_t size);
void                    usage();

#endif