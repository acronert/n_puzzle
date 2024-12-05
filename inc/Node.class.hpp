#ifndef NODE_CLASS_HPP
# define NODE_CLASS_HPP

# include <vector>

class Node {
	public:
		float		_g;
		float		_h;
		float		_f;
		std::vector<int>	graph;
		Node*		parent;
		void		h();

	private:
		Node();
		~Node();
		Node(const Node& other);
		Node& operator=(const Node& other);
		static bool compare(const Node &a, const Node &b);
};

#endif
