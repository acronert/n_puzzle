#include "Node.class.hpp"

// COPLIEN /////////////////////////////////////////////////////////////////////

Node::Node(std::vector<int> graph, std::vector<int> goal, std::size_t size) :
	_g(0), _h(0), _f(0),
	_graph(graph), _size(size), _parent(nullptr), _goal(goal)
{
	// Search '0' tile position
	for (int i = 0; i < (int)_graph.size(); i++) {
		if (_graph[i] == 0) {
			_pos = {i % _size, i / _size };
			break;
		}
	}

	this->h();
}

Node::~Node() {
	//std::cout << "destructor called on adress: " << this << std::endl;
}

Node::Node(const Node& other) {
	_g = other._g;
	_h = other._h;
	_f = other._f;
	_graph = other._graph;
	_size = other._size;
	_pos = other._pos;
	_parent = other._parent;
	_goal = other._goal;
}

Node& Node::operator=(const Node& other) {
	if (this != &other) {
		_g = other._g;
		_h = other._h;
		_f = other._f;
		_graph = other._graph;
		_size = other._size;
		_pos = other._pos;

		_parent = other._parent;
		_goal = other._goal;
	}
	return *this;
}

////////////////////////////////////////////////////////////////////////////////

std::vector<Node*>	Node::getChildren(){
	std::vector<Node*>	children;
	const s_coord directions[] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

	for (const s_coord& offset : directions) {
		s_coord dest = { _pos.x + offset.x, _pos.y + offset.y };

		// if out of range, continue
		if (dest.x < 0 || dest.x >= _size || dest.y < 0 || dest.y >= _size)
			continue;
		// if direction is parent
		if (this->_parent
			&& this->_parent->_pos.x == dest.x
			&& this->_parent->_pos.y == dest.y)
			continue;

		// else, create child
		Node	*child = new Node(*this);

		child->swapTiles(this->_pos, dest);
		child->_g++;
		child->h();
		child->_pos = dest;
		child->_parent = this;

		children.push_back(child);
	}
	return children;
}

std::vector<Node>	Node::buildPath() {
	std::vector<Node> path;
	Node *current = this;

	while (current != nullptr) {
		path.push_back(*current);
		current = current->_parent;
	}

	return path;
}

bool	Node::compare(const Node *a, const Node *b) {
	return a->_f < b->_f;
}

bool	Node::isGoal() const {
	return this->_graph == _goal;
}

int		Node::index(s_coord pos) {
	return pos.x + pos.y * _size;
}

void	Node::swapTiles(s_coord a, s_coord b) {
	std::swap(_graph[index(a)], _graph[index(b)]);
}

int	Node::distanceToGoal(int src) const {
	int graph_size = (int)this->_graph.size();
	int	dest = 0;

	for (dest = 0 ; dest < graph_size; dest++) {
		if (_graph[src] == _goal[dest])
			break;
	}

	s_coord	src_pos = {src % _size, src / _size };
	s_coord	dest_pos = {dest % _size, dest / _size};

	return std::abs(src_pos.x - dest_pos.x) + std::abs(src_pos.y - dest_pos.y);
}

void	Node::h() {
	this->_h = 0;

	int graph_size = (int)this->_graph.size();
	for (int src = 0; src < graph_size; src++) {
		if (!this->_graph[src])
			continue;
		this->_h += distanceToGoal(src);
	}

	this->_f = this->_h + this->_g;
}

// Check number of correctly placed tiles
// void	Node::h(const Node& goal) {
// 	float	new_h = 0;
// 	int graph_size = (int) this->_graph.size();
// 	for (int i = 0; i < graph_size; i++) {
// 		if (!this->_graph[i])
// 			continue;
// 		else if (this->_graph[i] != _goal[i])
// 			new_h += 1;
// 	}
// 	this->_h = new_h;
// }

void	Node::display() {
	for (int y = 0; y < _size; y++) {
		for (int x = 0; x < _size; x++) {
			int src = x + y * _size;
			int dist = distanceToGoal(src);

			std::string color;
			switch (dist) {
				case 0:
					color = GREEN;
					break;
				case 1:
					color = YELLOW;
					break;
				case 2:
					color = ORANGE;
					break;
				default:
					color = RED;
					break;
			}
			if (this->_graph[src] == 0)
				color = "";
			
			std::cout << color << std::setw(3) << this->_graph[src] << " " RESET;
		}
		std::cout << std::endl;
	}
	std::cout << "_g = " << _g << std::endl;
	std::cout << "_h = " << _h << std::endl;
	std::cout << "_f = " << _f << std::endl;
	std::cout << std::endl;
}

// std::ostream&	operator<<(std::ostream& os, const Node& node) {
// 	int size = node.getSize();
	
// 	for (int y = 0; y < size; y++) {
// 		for (int x = 0; x < size; x++) {
// 			int src = x + y * size;
// 			int dist = node.distanceToGoal(src);

// 			std::string color;
// 			switch (dist) {
// 				case 0:
// 					color = GREEN;
// 					break;
// 				case 1:
// 					color = YELLOW;
// 					break;
// 				case 2:
// 					color = ORANGE;
// 					break;
// 				default:
// 					color = RED;
// 					break;
// 			}
// 			if (node._graph[src] == 0)
// 				color = "";
			
// 			os << color << std::setw(3) << node._graph[src] << " " RESET;
// 		}
// 		os << "\n";
// 	}
// 	return os;
// }


float	Node::getSize() const					{ return _size; }
std::vector<int>	Node::getGraph() const		{ return _graph; }
float	Node::getG() const						{ return _g; }
float	Node::getH() const						{ return _h; }
float	Node::getF() const						{ return _f; }
void	Node::setG(float value)					{ _g = value; }
void	Node::setF(float value)					{ _f = value; }
void	Node::setGoal(std::vector<int> goal)	{ _goal = goal; }



