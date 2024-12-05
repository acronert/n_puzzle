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

std::vector<Node>	Node::getChildren() const {
	std::vector<Node>	children;

	

	return children;
}

std::vector<Node>	Node::buildPath() {

}

float	Node::getG() const { return _g; }
float	Node::getH() const { return _h; }
float	Node::getF() const { return _f; }

void	Node::setG(float value) { _g = value; }
void	Node::setF(float value) { _f = value; }

void	Node::display() const {

}


