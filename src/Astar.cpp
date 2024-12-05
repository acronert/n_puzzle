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
		//if current = goal return current.build_path()
		std::vector<NodeType> children = current.get_children();
		for (auto child:children)
		{
			//if child in openSet
			//compare g scores and keep the lowest one
			//else push copy of child into openset
		}
		delete children; //is it necessary ?
		std::make_heap(openSet.begin(), openSet.end(), Node::compare);
	}
	return NULL;

}
