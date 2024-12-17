#ifndef NODE_CLASS_HPP
# define NODE_CLASS_HPP

# include <vector>
# include <limits>
# include <cmath>
# include <iostream>
# include <iomanip>
# include <sstream>
# include "utils.hpp"
# include <set>

# define	INFINITY_F std::numeric_limits<float>::infinity()

# define	RESET		"\033[0m"
# define	RED			"\033[30;48;5;196m"
# define	DARK_ORANGE	"\033[30;48;5;208m"
# define	ORANGE		"\033[30;48;5;214m"
# define	YELLOW		"\033[30;48;5;226m"
# define	GREEN		"\033[30;42m"
# define	BLUE		"\033[30;44m"

# define	UP 1
# define	DOWN 2
# define	LEFT 3
# define	RIGHT 4

class Pool;
class PoolStack;

enum
{
	STANDARD,
	GREEDY,
	UNIFORM
};

enum
{
	MANHATTAN,
	MISPLACED,
	GASHNIG,
	LINEAR_CONFLICT
};

typedef struct	coord {
	int8_t 	x;			// -> 8 bit, +24bit
	int8_t 	y;
} s_coord;

typedef struct tile
{
	uint16_t	val;
	uint16_t	goalIdx;
	bool		isRightCol;
	bool		isRightRow;
	std::set<uint16_t>	rowConflict;
	std::set<uint16_t>	colConflict;	

} s_tile;


class Node {
	private:

		uint32_t				_g;
		uint32_t				_h;
		uint32_t				_lc;
		s_coord					_pos;
		std::vector<uint16_t>	_graph;
		Node*					_parent;

		static size_t		_size;
		static std::vector<uint16_t>	_goal;
		static int		_algoType;
		static int		_heuristicType;

		int		distanceToGoal(int src) const;
		int		index(s_coord pos);
		void	swapTiles(s_coord a, s_coord b);
		
		void	buildTiles();
		int		computeRowConflict(int i);
		int		computeColConflict(int i);
		int		computeLinearConflicts();
		void	updateTileLine(int line, int idx, int oldval);
		void	updateTileCol(int Col, int idx, int oldval);
		void	updateTile(int idx1, int idx2);
		
		bool	isColConflict(int idx1, int idx2);
		bool	isRowConflict(int idx1, int idx2);

		// for linear conflicts
		std::vector<s_tile>	_tiles;
	





	public:

		// Coplien
		Node();
		Node(std::vector<uint16_t> graph, std::vector<uint16_t> goal, size_t size, int algoType, int heuristicType);
		~Node();
		Node(const Node& other);
		Node& operator=(const Node& other);

		// Getters
		size_t		getSize() const;
		const std::vector<uint16_t>	&getGraph() const;
		uint32_t	getG() const;
		uint32_t	getH() const;
		uint32_t	getF() const;

		// Setters
		void	setGoal(std::vector<uint16_t> goal);
		void	setG(uint32_t value);
		void	setH(uint32_t value) {_h = value;}


		static void	updateNode(Node *old, Node* update);

		std::vector<Node *>	getChildren(PoolStack &pool);
		std::vector<Node>	buildPath();
		using NodePtr = Node*;
		static bool			compare(const NodePtr &a, const NodePtr &b);
		bool	operator<(const Node& other) const;
		bool	operator>(const Node& other) const;

		typedef void (Node::*heuristic_func)(void);
		heuristic_func	heu[3];

		void			h(s_coord &dest);
		uint32_t		manhattanDistance(s_coord &dest);
		uint32_t 		misplacedTiles(s_coord &dest);
		uint32_t		gashnig(s_coord &dest);

		bool	isGoal() const;
		void	display(int offset_x);
		void	debug();
		static	std::vector<uint16_t>	get_graph(const NodePtr &a)
		{
			return (a->_graph);
		}

		void	debugTiles();
	
		void	debugSwapTile(int idx1, int idx2);
};

// std::ostream&	operator<<(std::ostream& os, const Node& node);

#endif


