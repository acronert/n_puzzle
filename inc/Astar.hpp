#ifndef ASTAR_HPP
# define ASTAR_HPP

#include <Node.class.hpp>
#include <algorithm>

template <class NodeType>
std::vector<NodeType> astar(NodeType &start, NodeType &goal)
{
	std::vector<NodeType> openSet = { 0 };
	openSet.push_back(start);
	std::make_heap(openSet.begin(), openSet.end(), Node::compare);

	while (!openSet.empty())
	{
		NodeType current = openSet.back();
		std::cout << "current :" << &current << std::endl;
		current.display();
		// openSet.pop_back();
		if (current.isSameState(goal))
			return current.buildPath();
		std::vector<NodeType> children = current.getChildren(goal);
		std::cout << "BACK TO ASTAR\n";
		
		for (std::size_t i = 0; i < children.size(); i++)
		{
			// for (auto set:openSet) 
			// {
			// 	//if child in openSet compare g scores and keep the lowest one
			// 	if (child.isSameState(set) && child.getG() < set.getG())
			// 	{
			// 		std::cout << "updating already present\n";
			// 		set = child;

			// 	}
			// 	else //else push copy of child into openset
			// }
			std::cout << "pushing a child: " << &children[i] << std::endl;
			children[i].display();
			openSet.push_back(children[i]);
			
		}
		std::cout << "CHECKING OPENSET\n";
		for (std::size_t i = 0; i < openSet.size(); i++) {
		std::cout << "child parent = " << openSet[i]._parent << std::endl;
		if (openSet[i]._parent)
			std::cout << "child parent parent = " << openSet[i]._parent->_parent << std::endl;
		std::cout << "child = " << &openSet[i] << std::endl;
		openSet[i].display();
		}
		std::cout << "DONE\n";
		// delete children; //is it necessary ?
		std::make_heap(openSet.begin(), openSet.end(), Node::compare);
	}
	throw std::invalid_argument("No path found");
}

#endif