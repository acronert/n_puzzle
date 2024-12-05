#ifndef NODE_CLASS_HPP
# define NODE_CLASS_HPP

# include <vector>
# include <limits>

# define	INFINITY_F std::numeric_limits<float>::infinity()

class Node {
	public:
		float				_g;
		float				_h;
		float				_f;
		std::vector<int>	_graph;
		int					_size;
		Node*				_parent;
		void				h();
		Node(std::vector<int> graph, std::size_t size);
		Node(std::size_t size);

	private:
		// Node();
		~Node();
		Node(const Node& other);
		Node& operator=(const Node& other);

		static bool compare(const Node &a, const Node &b);

		bool	isSameState(const Node& other) const;
		std::vector<Node>	getChildren() const;
		std::vector<Node>	buildPath();

		float	getG() const;
		float	getH() const;
		float	getF() const;

		void	setG(float value);
		void	setF(float value);

		void	display() const;
};

#endif
