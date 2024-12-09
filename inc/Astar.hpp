#ifndef ASTAR_HPP
# define ASTAR_HPP

#include <Node.class.hpp>
#include <algorithm>

template <class NodeType>
std::vector<NodeType> astar(NodeType *start)
{
	std::size_t	max_nodes = 1;
	int	loop_count = 0;
	if (!start){
		throw std::invalid_argument("Undefined start");
	}
	std::vector<NodeType*> openSet;
	openSet.push_back(start);
	std::make_heap(openSet.begin(), openSet.end(), Node::compare);
	while (!openSet.empty())
	{
		loop_count++;
		if (openSet.size() > max_nodes)
		{
			max_nodes = openSet.size();
		}
		NodeType *current = openSet.back();
		current->display();
		openSet.pop_back();
		if (current->isGoal())
		{
			std::vector<Node> path = current->buildPath();
			std::cout << "LOOP COUNT and MAX NODE are: " << loop_count << " " << max_nodes << std::endl;
			//free all the Node in Openset and the "cemetery"
			return path;
		}

		std::vector<NodeType*> children = current->getChildren();

		for (std::size_t i = 0; i < children.size(); i++)
		{
			for (auto set:openSet)
			{
				//if child in openSet compare g scores and keep the lowest one
				// probably slow, can have a map to check faster, more memory
				if (children[i]->getGraph() == set->getGraph()
					&& children[i]->getG() < set->getG())
				{
					*set = *children[i];
					delete children[i];
					children[i] = NULL;
					break;
				}
			}
			if (children[i] != NULL){
				openSet.push_back(children[i]);
			}

		}
		//Should not call make heap each time see algorithm c++
		std::make_heap(openSet.begin(), openSet.end(), Node::compare);
	}
	//free all
	throw std::invalid_argument("No path found");
}

#endif




