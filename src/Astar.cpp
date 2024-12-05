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
		NodeType current = openSet.pop_back();
		if (current.isSameState(goal))
			return current.buildPath();
		std::vector<NodeType> children = current.getChildren();
		for (auto child:children)
		{
			for (auto set:openSet) 
			{
				//if child in openSet compare g scores and keep the lowest one
				if (child.isSameState(set) && child.getG() < set.getG())
					set = child;
				else //else push copy of child into openset
					openSet.push_back(NodeType(child));
			}
			
		}
		delete children; //is it necessary ?
		std::make_heap(openSet.begin(), openSet.end(), Node::compare);
	}
	return NULL;
}
