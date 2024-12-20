#ifndef ASTAR_HPP
# define ASTAR_HPP

#include <Node.class.hpp>
#include <Solution.class.hpp>
#include <algorithm>
#include <map>
#include <heap.hpp>
#include <heap.tpp>

template <class NodeType, class GraphType>
Solution astar(NodeType *start)
{
	std::size_t	max_nodes = 1;
	int	loop_count = 0;
	if (!start){
		throw std::invalid_argument("Undefined start");
	}
	Heap<NodeType*, GraphType> openSet = Heap<NodeType*, GraphType>(&NodeType::get_graph, &NodeType::compare);
	std::map<GraphType, float>	closeSet;
	openSet.insert(start);
	closeSet[start->getGraph()] = start->getF();
	while (openSet.getSize() > 0)
	{
		loop_count++;
		if (openSet.getSize() > max_nodes)
		{
			max_nodes = openSet.getSize();
		}
		NodeType *current = openSet.popHead();
		if (current->isGoal())
		{
			Solution solution(current->buildPath(), loop_count, max_nodes);
			//free all the Node in Openset and the "cemetery"
			return solution;
		}

		std::vector<NodeType*> children = current->getChildren();

		for (std::size_t i = 0; i < children.size(); i++)
		{
			size_t	idx = 0;
			if (openSet.getIndex(children[i]->getGraph(), idx))
			{
				if (children[i] < openSet[idx]){
					openSet.modify(idx, children[i], &Node::updateNode);
					closeSet[children[i]->getGraph()] = children[i]->getF();
				}
				delete children[i];
				children[i] = NULL;
			}
			if (children[i] != NULL){ //pas ds openSet
				if (auto search = closeSet.find(children[i]->getGraph()); search != closeSet.end()) //dans closeSet
				{
					if (children[i]->getF() < closeSet[children[i]->getGraph()]) // nouveau score meilleur
					{
						openSet.insert(children[i]); //insertion ds openSet
						closeSet[children[i]->getGraph()] = children[i]->getF(); //modification closeSet
					}
					else{
						delete children[i];
					}
				}
				else{ // jamais vu du tout
					openSet.insert(children[i]);
					closeSet[children[i]->getGraph()] = children[i]->getF();
				}

			}

		}
	}
	throw std::invalid_argument("No path found");
}

#endif
