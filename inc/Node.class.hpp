#ifndef NODE_CLASS_HPP
# define NODE_CLASS_HPP

# include <vector>
# include <limits>

# define	INFINITY_F std::numeric_limits<float>::infinity()

# define	UP 1
# define	DOWN 2
# define	LEFT 3
# define	RIGHT 4

struct	coord {
	int x;
	int y;
};

class Node {
	public:
		float				_g;
		float				_h;
		float				_f;
		coord				_pos;

		std::vector<int>	_graph;
		int					_size;
		Node*				_parent;

		// void				h();

	private:
		// Node();
		~Node();
		Node(const Node& other);
		Node& operator=(const Node& other);

		static bool	compare(const Node &a, const Node &b);
		bool		isSameState(const Node& other) const;
		int			index(coord pos);
		coord		coord(int idx);

		void		swapGraph(coord a, coord b);
		std::vector<Node>	getChildren() const;

		std::vector<Node>	buildPath();

		void	h(const Node& goal);

		float	getG() const;
		float	getH() const;
		float	getF() const;

		void	setG(float value);
		void	setF(float value);

		void	display() const;

};

#endif
