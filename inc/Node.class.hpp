#ifndef NODE_CLASS_HPP
# define NODE_CLASS_HPP

# include <vector>
# include <limits>
# include <cmath>
# include <iostream>
# include <iomanip>
# include <sstream>
# include "utils.hpp"

# define	INFINITY_F std::numeric_limits<float>::infinity()

# define RESET		"\033[0m"
# define RED		"\033[30;41m"
# define GREEN		"\033[30;42m"
# define YELLOW		"\033[30;43m"
# define BLUE		"\033[30;44m"
# define ORANGE		"\033[30;48;5;208m"

# define	UP 1
# define	DOWN 2
# define	LEFT 3
# define	RIGHT 4

enum
{
	STANDARD,
	GREEDY,
	UNIFORM
};

typedef struct	coord {
	int16_t x;
	int16_t y;
} s_coord;

class Node {
	private:

		uint32_t			_g;
		uint32_t			_h;
		s_coord					_pos;
		std::vector<uint32_t>	_graph;
		Node*					_parent;

		static uint16_t			_size;
		static std::vector<uint32_t>	_goal;


		int		distanceToGoal(int src) const;
		int		index(s_coord pos);
		void	swapTiles(s_coord a, s_coord b);

		static int16_t		_algoType;

	public:

		// Coplien
		Node(std::vector<uint32_t> graph, std::vector<uint32_t> goal, uint16_t size, int16_t algoType);
		~Node();
		Node(const Node& other);
		Node& operator=(const Node& other);
		bool	operator<(const Node &b) const;

		// Getters
		uint16_t	getSize() const;
		const std::vector<uint32_t>	&getGraph() const;
		uint32_t	getG() const;
		uint32_t	getH() const;
		uint32_t	getF() const;

		// Setters
		void	setGoal(std::vector<uint32_t> goal);
		void	setG(uint32_t value);

		static void	updateNode(Node *old, Node* update);

		std::vector<Node*>	getChildren();
		std::vector<Node>	buildPath();
		using NodePtr = Node*;
		static bool			compare(const NodePtr &a, const NodePtr &b);
		bool	operator<(const Node& other) const;
		bool	operator>(const Node& other) const;
		void	h();
		bool	isGoal() const;
		void	display(int offset_x);
		static	std::vector<uint32_t>	get_graph(const NodePtr &a)
		{
			return (a->_graph);
		}
};

// std::ostream&	operator<<(std::ostream& os, const Node& node);

#endif


