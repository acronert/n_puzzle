#include "Node.class.hpp"
#include "unordered_map"
# include "Pool.class.hpp"

size_t	Node::_size = 0;
int		Node::_algoType = 0;
std::vector<uint16_t>	Node::_goal = {};

// COPLIEN /////////////////////////////////////////////////////////////////////

Node::Node(std::vector<uint16_t> graph, std::vector<uint16_t> goal, size_t size, int algoType) :
	_g(0), _h(0), _graph(graph), _parent(nullptr)
{
	Node::_goal = goal;
	Node::_size = size;
	Node::_algoType = algoType;

	// Search '0' tile position
	for (int i = 0; i < (int)_graph.size(); i++) {
		if (_graph[i] == 0) {
			// _pos = {i % _size, i / _size };
			_pos.x = i % _size;
			_pos.y = i / _size;
			break;
		}
	}
	this->h(this->_pos);
}

Node::Node()
{
}

Node::~Node() {
	//std::cout << "destructor called on adress: " << this << std::endl;
}

Node::Node(const Node& other) {
	_g = other._g;
	_h = other._h;
	_graph = other._graph;
	_pos = other._pos;
	_parent = other._parent;
}

Node& Node::operator=(const Node& other) {
	if (this != &other) {
		_g = other._g;
		_h = other._h;
		_graph = other._graph;
		_pos = other._pos;
		_parent = other._parent;
	}
	return *this;
}

////////////////////////////////////////////////////////////////////////////////

std::vector<Node*>	Node::getChildren(PoolStack &pool){
	std::vector<Node*>	children;
	const s_coord directions[] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

	for (size_t i = 0; i < 4; i++) {
		const s_coord	&offset = directions[i];
		s_coord dest;
		dest.x = _pos.x + offset.x;
		dest.y = _pos.y + offset.y;

		// if out of range, continue
		if (dest.x < 0 || dest.x >= (int)_size || dest.y < 0 || dest.y >= (int)_size)
		{
			continue;
		}

		// if direction is parent && not GREEDY
		if (this->_parent
			&& this->_parent->_pos.x == dest.x
			&& this->_parent->_pos.y == dest.y)
			{
				continue;
			}


		// verifier si le node existe deja
			// si son g est meilleur
				// update ( And dont create a child)
			// else, create child
		//Node	*child = new Node(*this);
		Node *child = pool.next();
		*child = *this;

		child->swapTiles(this->_pos, dest);

		child->_g++;
		child->h(dest);
		child->_pos = dest;
		child->_parent = this;

		children.push_back(child);
	}
	return (children);
}

std::vector<Node>	Node::buildPath(){
	std::vector<Node> path;
	Node *current = this;

	while (current != nullptr) {
		path.push_back(*current);
		current = current->_parent;
	}
	std::reverse(path.begin(), path.end());
	return path;
}

bool	Node::operator<(const Node& other) const {
	return this->getF() < other.getF();
}

bool	Node::operator>(const Node& other) const {
	return this->getF() > other.getF();
}

// temporaire
bool	Node::compare(const NodePtr &a, const NodePtr &b) {
	return a->getF() < b->getF();
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

	s_coord	src_pos;
	src_pos.x = src % _size;
	src_pos.y = src / _size ;
	s_coord	dest_pos;
	dest_pos.x = dest % _size;
	dest_pos.y = dest / _size;

	return std::abs(src_pos.x - dest_pos.x) + std::abs(src_pos.y - dest_pos.y);
}



//Manhattan distance
void	Node::h(s_coord &dest) {

	if (this->_parent == nullptr){
		int graph_size = (int)this->_graph.size();
		this->_h = 0;
		for (int src = 0; src < graph_size; src++) {
			if (!this->_graph[src])
				continue;
			this->_h += distanceToGoal(src);
		}
	}
	else{
		this->_h -= this->_parent->distanceToGoal(index(dest));
		this->_h += this->distanceToGoal((index(this->_pos)));
	}
}

// Misplaced tiles
void Node::h1(s_coord &dest)
{
	if (this->_parent == nullptr){
		this->_h = 0;
		int graph_size = _size * _size;
		for (int i = 0; i < graph_size; i++)
		{
			if (this->_graph[i] != _goal[i])
				_h++;
		}
	}
	else{
		this->_h -= (this->_parent->_graph[index(dest)] == _goal[index(dest)]);
		this->_h += this->_graph[index(this->_pos)] == _goal[index(this->_pos)];
	}
}



//Manhattan + linear conflict
void	Node::h2()
{
	this->_h = 0;
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

void	Node::display(int offset_x) {
	for (int y = 0; y < (int)_size; y++) {
		std::cout << "\033[" << offset_x << "C";
		for (int x = 0; x < (int)_size; x++) {
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
				case 3:
					color = DARK_ORANGE;
					break;
				default:
					color = RED;
					break;
			}
			if (this->_graph[src] == 0)
				color = "";

			std::cout << color << std::setw(3) <<  this->_graph[src] << RESET;
		}
		std::cout << std::endl;
	}
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


size_t	Node::getSize() const					{ return _size; }
const std::vector<uint16_t>	&Node::getGraph() const	{ return _graph; }
uint32_t	Node::getG() const					{ return _g; }
uint32_t	Node::getH() const					{ return _h; }

uint32_t	Node::getF() const
{
	if (_algoType == STANDARD)
		return _g + _h;
	else if (_algoType == GREEDY)
		return _h;
	else
		return _g;
}

void	Node::setG(uint32_t value)					{ _g = value; }
void	Node::setGoal(std::vector<uint16_t> goal)	{ _goal = goal; }



void	Node::updateNode(Node *old, Node *update)
{
	*old = *update;
}

void	Node::debug()
{
	std::cout << "Node state " << this->_graph[0] << std::endl;
	std::cout << "g & h = " << this->getG() << " & " << this->getH();
	std::cout << "/n======\n";
 }
