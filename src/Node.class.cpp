#include "Node.class.hpp"

Node::Node(std::vector<int> graph, size_t size) :	_g(INFINITY_F),
													_h(INFINITY_F),
													_f(INFINITY_F),
													_graph(graph), _size(size),
													_parent(nullptr)
{}

Node::~Node() {}

Node::Node(const Node& other) {
	_g = other._g;
	_h = other._h;
	_f = other._f;
	_graph = other._graph;
	_size = other._size;

	_parent = other._parent;
}

Node& Node::operator=(const Node& other) {
	if (this != &other) {
		_g = other._g;
		_h = other._h;
		_f = other._f;
		_graph = other._graph;
		_size = other._size;

		_parent = other._parent;
	}
	return *this;
}




static bool	Node::compare(const Node &a, const Node &b) {
	return a._f < b._f;
}

bool	Node::isSameState(const Node& other) const {
	return this._graph == other._graph;
}

int		Node::index(coord pos) {
	return x + y * _size;
}

coord	Node::coord(int idx) {
	return { idx % _size, idx / _size };
}

void	Node::swapGraph(coord a, coord b) {
	std::swap(_grap[index(a)], _grap[index(b)]);
}

std::vector<Node>	Node::getChildren() const {
	std::vector<Node>	children;

	const coord directions[] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

	for (const coord& offset : directions) {
		coord dest = { _pos.x + offset.x, _pos.y + offset.y };

		// if out of range, continue
		if (dest.x < 0 || dest.x >= _size || dest.y < 0 || dest.y >= _size)
			continue;

		// else, create child
		Node	child(*this);

		child.swapGraph(child._pos, dest);
		child._g++;
		child._pos = dest;
		child._parent = this;

		children.push_back(child);
	}
	return children;
}

std::vector<Node>	Node::buildPath() {

}





// Check number of correctly placed tiles
void	Node::h(const Node& goal) {
	float	new_h = 0;

	for (int i = 0; i < this._graph.size(); i++) {
		if (!this._graph[i])
			continue;
		else if (this._graph[i] != goal._graph[i])
			new_h += 1;
	}
	this._h = new_h;
}




// Check sum of distances between tiles and their goals
float	distance(int a, int b) {
	coord	a_pos = coord(a);
	coord	b_pos = coord(b);

	return abs(a_pos.x - b_pos.x) + abs(a_pos.y - b_pos.y);
}

void	Node::h(const Node& goal) {
	float	new_h = 0;

	for (int src = 0;src < this._graph.size();src++) {
		if (!this._graph[src])
			continue;
		// calculate distance between tile and its goal
		int dest = 0;
		for ( ; dest < this._graph.size(); dest++) {
			if (goal._graph[dest] == this._graph[i])
				break;
		}
		new_h += distance(src, dest);
	}

	this._h = new_h;
}


float	Node::getG() const { return _g; }
float	Node::getH() const { return _h; }
float	Node::getF() const { return _f; }
void	Node::setG(float value) { _g = value; }
void	Node::setF(float value) { _f = value; }

void	Node::display() const {
	std::cout << "_g = " << _g << std::endl;
	std::cout << "_h = " << _h << std::endl;
	std::cout << "_f = " << _f << std::endl;
	std::cout << "_pos = " << _pos.x << _pos.y << std::endl;

	for (int y = 0; y++ ; y < _size) {
		for (int x = 0; x++ ; x < _size) {
			std::cout << this._graph[index(x, y)] << " ";
		}
		std::cout << std::endl;
	}

}