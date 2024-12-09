#ifndef NODE_CLASS_HPP
# define NODE_CLASS_HPP

# include <vector>
# include <limits>
# include <cmath>
# include <iostream>
# include <iomanip>
# include <sstream>
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

typedef struct	coord {
	int x;
	int y;
} s_coord;


class Node {
	private:
		float				_g;
		float				_h;
		float				_f;
		s_coord				_pos;

		std::vector<int>	_graph;
		int					_size;
		Node*				_parent;

		std::vector<int>	_goal;

		int		distanceToGoal(int src) const;
		int		index(s_coord pos);
		void	swapTiles(s_coord a, s_coord b);
		int		findDest(int value);



	public:
		
		// Coplien
		Node(std::vector<int> graph, std::vector<int> goal, std::size_t size);
		~Node();
		Node(const Node& other);
		Node& operator=(const Node& other);

		float	getSize() const;
		std::vector<int>	getGraph() const;
		float	getG() const;
		float	getH() const;
		float	getF() const;

		void	setGoal(std::vector<int> goal);
		void	setG(float value);
		void	setF(float value);

		static bool	compare(const Node *a, const Node *b);
		void	h();
		bool				isGoal() const;
		std::vector<Node>	buildPath();

		std::vector<Node*>	getChildren();
		void	display();




};

// std::ostream&	operator<<(std::ostream& os, const Node& node);

#endif
