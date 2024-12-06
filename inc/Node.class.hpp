#ifndef NODE_CLASS_HPP
# define NODE_CLASS_HPP

# include <vector>
# include <limits>
#include <cmath>
#include <iostream>
# define	INFINITY_F std::numeric_limits<float>::infinity()

# define	UP 1
# define	DOWN 2
# define	LEFT 3
# define	RIGHT 4

typedef struct	coord {
	int x;
	int y;
} s_coord;


class Node {
	public:
		float				_g;
		float				_h;
		float				_f;
		s_coord				_pos;

		std::vector<int>	_graph;
		int					_size;
		Node*				_parent;
		Node(const Node& other);
		Node(std::vector<int> graph, std::size_t size);
		Node& operator=(const Node& other);
		Node(std::size_t size);
		~Node();

		float	getG() const;
		float	getH() const;
		float	getF() const;
		void	setG(float value);
		void	setF(float value);
		void	display();

		static bool	compare(const Node &a, const Node &b);

		bool		isSameState(const Node& other) const;
		std::vector<Node>	buildPath();
		std::vector<Node>	getChildren(Node& goal) const;

		void	h(const Node& goal);
		// void				h();

	private:
		// Node();

		int			index(s_coord pos);

		int			distance(int a, int b);
		void		swapGraph(s_coord a, s_coord b);





};

#endif
