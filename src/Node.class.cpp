#include "Node.class.hpp"

std::vector<int>	build_goal(std::size_t size);

Node::Node(std::vector<int> graph, std::size_t size) :	_g(INFINITY_F),
													_h(INFINITY_F),
													_f(INFINITY_F),
													_graph(graph), _size(size),
													_parent(nullptr)
{
	for (int i = 0; i < (int)_graph.size(); i++) {
		if (_graph[i] == 0) {
			_pos = {i % _size, i / _size };
			break;
		}
	}
}

Node::~Node() {

	std::cout << "destructor called on adress: " << this << std::endl;
}

Node::Node(const Node& other) {
	_g = other._g;
	_h = other._h;
	_f = other._f;
	_graph = other._graph;
	_size = other._size;
	_pos = other._pos;
	_parent = other._parent;
}

Node::Node(std::size_t size) : _g(INFINITY_F),
								_h(INFINITY_F),
								_f(INFINITY_F),
								_size(size),
								_parent(nullptr)
{
	this->_graph = build_goal(size);
	for (int i = 0; i < (int)_graph.size(); i++) {
		if (_graph[i] == 0) {
			_pos = {i % _size, i / _size };
			break;
		}
	}
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
	}
	return *this;
}

int	idx(int i, int j, int size)
{
	return (i*size + j);
}

std::vector<int>	build_goal(std::size_t size)
{
	int square = size * size;
	std::vector<int> inputs(square,0);

	int	top = 0;
	int bottom = size - 1;
	int	left = 0;
	int right = size -1;
	int	k = 1;
	while (k <  square)
	{
		for (int i = left; i<= right; i++){
			inputs[idx(top, i, size)] = k % square;
			k++;
		}
		top++;
		for (int j = top; j<= bottom; j++)
		{
			inputs[idx(j, right, size)] = k % square;
			k++;
		}
		right--;
		if (top < bottom)
		{
			for (int i = right; i >= left; i--)
			{
				inputs[idx(bottom,i,size)] = k % square;
				k++;
			}
			bottom--;

		}
		if (left < right)
		{
			for (int i = bottom; i >= top; i--)
			{
				inputs[idx(i, left, size)] = k % square;
				k++;
			}
			left++;

		}
}
	return inputs;
}

std::vector<Node>	Node::buildPath() {
	std::vector<Node> path;
	std::cout << "building Path from: " << this << std::endl;
	this->display();
	Node *current = this;
	while (current != nullptr) {
		// current.display();
		path.push_back(*current);
		current = current->_parent;
		std::cout << "update ptr to parent: " << current << std::endl;
		current->display();
		break;
	}

	return path;
}


bool	Node::compare(const Node &a, const Node &b) {
	return a._f < b._f;
}

bool	Node::isSameState(const Node& other) const {
	return this->_graph == other._graph;
}

int		Node::index(s_coord pos) {
	return pos.x + pos.y * _size;
}

void	Node::swapGraph(s_coord a, s_coord b) {
	std::swap(_graph[index(a)], _graph[index(b)]);
}

std::vector<Node>	Node::getChildren(Node& goal) const {
	std::vector<Node>	children;

	const s_coord directions[] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

	for (const s_coord& offset : directions) {
		s_coord dest = { _pos.x + offset.x, _pos.y + offset.y };

		// if out of range, continue
		if (dest.x < 0 || dest.x >= _size || dest.y < 0 || dest.y >= _size)
			continue;

		// else, create child
		Node	child = *this;

		child.swapGraph(this->_pos, dest);
		child._g++;
		child.h(goal);
		child._pos = dest;
		child._parent = (Node *)this;


		children.push_back(child);
	}

	for (std::size_t i = 0; i < children.size(); i++) {
		std::cout << "child parent = " << children[i]._parent << std::endl;
		std::cout << "child parent parent = " << children[i]._parent->_parent << std::endl;
		std::cout << "child = " << &children[i] << std::endl;
		children[i].display();
	}

	return children;
}

// std::vector<Node>	Node::buildPath() {
// 	return;
// }





// Check number of correctly placed tiles
// void	Node::h(const Node& goal) {
// 	float	new_h = 0;
// 	int graph_size = (int) this->_graph.size();
// 	for (int i = 0; i < graph_size; i++) {
// 		if (!this->_graph[i])
// 			continue;
// 		else if (this->_graph[i] != goal._graph[i])
// 			new_h += 1;
// 	}
// 	this->_h = new_h;
// }




// Check sum of distances between tiles and their goals
int	Node::distance(int a, int b) {
	s_coord	a_pos = {a % _size, a / _size };
	s_coord	b_pos = {b % _size, b / _size};
	return std::abs(a_pos.x - b_pos.x) + std::abs(a_pos.y - b_pos.y);
}

void	Node::h(const Node& goal) {
	float	new_h = 0;

	int graph_size = (int)this->_graph.size();
	for (int src = 0;src < graph_size ;src++) {
		if (!this->_graph[src])
			continue;
		// calculate distance between tile and its goal
		int dest = 0;
		for ( ; dest < graph_size; dest++) {
			if (goal._graph[dest] == this->_graph[src])
				break;
		}
		new_h += distance(src, dest);
	}

	this->_h = new_h;
	this->_f = this->_h + this->_g;
}


float	Node::getG() const { return _g; }
float	Node::getH() const { return _h; }
float	Node::getF() const { return _f; }
void	Node::setG(float value) { _g = value; }
void	Node::setF(float value) { _f = value; }

void	Node::display() {

	for (int y = 0; y < _size; y++) {
		for (int x = 0; x < _size; x++) {
			s_coord cd = {x,y};
			std::cout << this->_graph[index(cd)] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "_g = " << _g << std::endl;
	std::cout << "_h = " << _h << std::endl;
	std::cout << "_f = " << _f << std::endl;
	std::cout << "_pos = " << _pos.x << ", " << _pos.y << std::endl;
	std::cout << "_parent = " << _parent << std::endl;
	std::cout << std::endl;

}
