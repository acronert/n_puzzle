#ifndef NODE_CLASS_HPP
# define NODE_CLASS_HPP

# include <vector>

class Node {
	public:
		float		g;
		float		h;
		float		f;
		vector<int>	graph;
		Node*		parent;

	private:
		Node();
		~Node();
		Node(const Node& other);
		Node& operator=(const Node& other);
}

#endif