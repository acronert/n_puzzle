#include "Node.class.hpp"
#include "unordered_map"
# include "Pool.class.hpp"

size_t	Node::_size = 0;
int		Node::_algoType = 0;
int		Node::_heuristicType = 0;
std::vector<uint16_t>	Node::_goal = {};


// COPLIEN /////////////////////////////////////////////////////////////////////

Node::Node(std::vector<uint16_t> graph, std::vector<uint16_t> goal, size_t size, int algoType, int heuriType) :
	_g(0), _h(0), _graph(graph), _parent(nullptr), _tiles()
{
	Node::_goal = goal;
	Node::_size = size;
	Node::_algoType = algoType;
	Node::_heuristicType = heuriType;


	// Search '0' tile position
	for (int i = 0; i < (int)_graph.size(); i++) {
		if (_graph[i] == 0) {
			// _pos = {i % _size, i / _size };
			_pos.x = i % _size;
			_pos.y = i / _size;
			break;
		}
	}
	_lc = 0;
	if (_heuristicType == LINEAR_CONFLICT)
		this->buildTiles();
	this->h(this->_pos);
}

void	Node::debugTiles()
{
	for (auto til: _tiles)
	{
		std::cout << "value = " << til.val << " goal index = " << til.goalIdx << " isCol, is Row " << til.isRightCol << ", " << til.isRightRow << std::endl;
		std::cout << "Row conflicts: ";
		for (auto x: til.rowConflict)
		{
			std::cout << x << ", ";
		}
		std::cout << std::endl << "Col conflicts: ";
		for (auto x: til.colConflict)
		{
			std::cout << x << ", ";
		}
		std::cout << std::endl;
	}
}

void	Node::buildTiles()
{
	this->_tiles.reserve(_size*_size);
	int	len = (int)(_size*_size);
	for (int i =0; i < len; i++)
	{
		s_tile	new_tile;

		new_tile.val = _graph[i];
		for (int j = 0; j < len; j++)
		{
			if (_goal[j] == new_tile.val)
			{
				new_tile.goalIdx =j;
				break;
			}
		}
		new_tile.isRightCol = new_tile.goalIdx % _size == i % _size;
		new_tile.isRightRow = new_tile.goalIdx / _size == i / _size;
		_tiles.push_back(new_tile);
	}
	for (int line = 0; line < (int)_size; line++)
	{
		for (int idx = 0; idx < (int)_size; idx++)
		{
			tile& t = _tiles[line*_size + idx];
			if (t.val == 0 || !t.isRightRow)
				continue;
			for (int j = idx+1; j < (int)_size; j++)
			{
				tile&	s = _tiles[line*_size + j];
				if (s.val == 0 || !s.isRightRow)
					continue;
				if (t.goalIdx % (int)_size > s.goalIdx % (int)_size)
				{
					t.rowConflict.insert(s.val);
					s.rowConflict.insert(t.val);
				}
			}
		}
	}
	for (int col = 0; col < (int)_size; col++)
	{
		for (int idx = 0; idx < (int)_size; idx++)
		{
			tile& t = _tiles[idx*_size + col];
			if (t.val == 0 || !t.isRightCol )
				continue;
			for (int j = idx+1; j < (int)_size; j++)
			{
				tile&	s = _tiles[j*_size + col];
				if (s.val == 0 || !s.isRightCol)
					continue;
				if (t.goalIdx / _size > s.goalIdx / _size)
				{
					t.colConflict.insert( s.val);
					s.colConflict.insert( t.val);
				}
				
			}
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
	_tiles = other._tiles;
	_lc = 0;
}

Node& Node::operator=(const Node& other) {
	if (this != &other) {
		_g = other._g;
		_h = other._h;
		_graph = other._graph;
		_pos = other._pos;
		_parent = other._parent;
		_tiles = other._tiles;
		_lc = 0;
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


void	Node::h(s_coord &dest) {
	if (_heuristicType == MANHATTAN)
		_h = manhattanDistance(dest);
	else if (_heuristicType == MISPLACED)
		_h = misplacedTiles(dest);
	else if (_heuristicType == GASHNIG)
		_h = gashnig(dest);
	else if (_heuristicType == LINEAR_CONFLICT)
	{	
		_h = manhattanDistance(dest);
		updateTile(index(this->_pos), index(dest));
		_lc = computeLinearConflicts();
	}

}

//Manhattan distance
uint32_t	Node::manhattanDistance(s_coord &dest) {

	uint32_t newh = 0;
	if (this->_parent == nullptr){
		int graph_size = (int)this->_graph.size();
		for (int src = 0; src < graph_size; src++) {
			if (!this->_graph[src])
				continue;
			newh += distanceToGoal(src);
		}
	}
	else{
		newh = this->_h;
		newh -= this->_parent->distanceToGoal(index(dest));
		newh += this->distanceToGoal((index(this->_pos)));
	}
	return newh;
}

// Misplaced tiles
uint32_t Node::misplacedTiles(s_coord &dest)
{
	uint32_t	newh = 0;
	if (this->_parent == nullptr){
		int graph_size = _size * _size;
		for (int i = 0; i < graph_size; i++)
		{
			if (this->_graph[i] != _goal[i])
				newh++;
		}
	}
	else{
		newh = this->_h;
		newh -= (this->_parent->_graph[index(dest)] == _goal[index(dest)]);
		newh += this->_graph[index(this->_pos)] == _goal[index(this->_pos)];
	}
	return newh;
}


// int	Node::isRightCol(int idx)
// {
// 	uint16_t	val = this->_graph[idx];
// 	int			goalidx = 0;
// 	for (goalidx = 0; goalidx < this->_size*this->_size; goalidx++)
// 	{
// 		if (this->_goal[goalidx] == val)
// 			break;
// 	}
// 	if (idx % this->_size != goalidx % this->_size)
// 		return (0);
// 	return ((goalidx / this->_size) - (idx / this->_size));
// }


//Manhattan + linear conflict
// void	Node::h2()
// {
	// this->_h = 0;
// }

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

// Gaschnig
uint32_t	Node::gashnig(s_coord &dest) {
	std::vector<uint16_t> tmp = _graph;
	int	blank_idx = index(this->_pos);
	uint32_t newh = 0;
	// START H
	if (this->_parent == nullptr) {
		while (tmp != _goal) {
			if (tmp[blank_idx] == _goal[blank_idx])	// emptytile is where it should be
			{
				// switch it with a misplaced tile
				for (std::size_t i = 0; i < tmp.size(); i++) {
					if (tmp[i] != _goal[i]) {
						std::swap(tmp[i], tmp[blank_idx]);
						blank_idx = i;
						break;
					}
				}
			} else {
				// find the tile that should be in blank pos
				int target = _goal[blank_idx];
				for (std::size_t i = 0; i < tmp.size(); i++) {
					if (tmp[i] == target){
						std::swap(tmp[i], tmp[blank_idx]);
						blank_idx = i;
						break;
					}
				}
			}
			newh++;
		}
	}
	else {
		newh = _h;
		// if parent 0 was placed
		if (_goal[index(dest)] == 0)
			newh--;
		// else if child 0 is placed
		else if (_goal[index(_pos)] == 0)
			newh++;

		// if moved tile was placed
		if (_graph[index(_pos)] == _goal[index(dest)])
			newh++;
		// else if moved tile is placed
		if (_graph[index(_pos)] == _goal[index(_pos)])
			newh--;
	}
	return (newh);
}

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
uint32_t	Node::getH() const					{ return _h+_lc; }

uint32_t	Node::getF() const
{
	if (_algoType == STANDARD)
		return _g + _h + _lc;
	else if (_algoType == GREEDY)
		return _h + _lc;
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


int	Node::computeRowConflict(int i)
{
	int	line = i*(int)_size;
	std::vector<int>	lc(_size, 0);
	int	max = -1;
	int	idxmax = 0;
	int	conflictsCount = 0;

	for (int idx = 0; idx < (int)_size; idx++)
	{
		lc[idx] = _tiles[line+idx].rowConflict.size();
		if (lc[idx] > max)
		{
			max = lc[idx];
			idxmax = idx;
		}
	}
	while (max > 0)
	{
		int	val = _tiles[line + idxmax].val;
		lc[idxmax] = 0;
		max = -1;
		idxmax = 0;
		for (int j = 0; j < (int)_size; j++)
		{
			if (_tiles[line+j].rowConflict.count(val))
				lc[j] -= 1;
			if (lc[j] > max)
			{
				max = lc[j];
				idxmax = j;
			}
		}
		conflictsCount += 1;
	}
	return (conflictsCount);
}

int	Node::computeColConflict(int j)
{
	std::vector<int>	lc(_size, 0);
	int max = -1;
	int idxmax = 0;
	int conflictsCount = 0;

	for (int line = 0; line < (int)_size; line++)
	{
		lc[line] = _tiles[line*_size + j].colConflict.size();
		if (lc[line] > max)
		{
			max = lc[line];
			idxmax = line;
		}
	}
	while (max > 0)
	{
		int val = _tiles[idxmax*_size + j].val;
		max = -1;
		lc[idxmax] = 0;
		idxmax = 0;
		for (int line = 0; line < (int)_size; line++)
		{
			if (_tiles[line*_size + j].colConflict.count(val))
			{
				lc[line] -= 1;
			}
			if (lc[line] > max)
			{
				max = lc[line];
				idxmax = line;
			}
		}
		conflictsCount += 1;
	}
	return (conflictsCount);
}

int		Node::computeLinearConflicts()
{
	int	conflicts = 0;

	for (int line = 0; line < (int)_size; line++)
	{
		conflicts += computeRowConflict(line);
	}
	for (int col = 0; col < (int)_size; col++)
	{
		conflicts += computeColConflict(col);
	}
	return (conflicts);
}

bool	Node::isRowConflict(int idx1, int idx2)
{
	if (idx1 / _size != idx2 / _size)
		return false;
	tile& t1 = _tiles[idx1];
	tile& t2 = _tiles[idx2];
	if (!t1.isRightRow || !t2.isRightRow ||  t1.val == 0 || t2.val == 0)
		return false;
	if (idx1 % _size < idx2 % _size)
	{
		return (t1.goalIdx % _size > t2.goalIdx % _size);
	}
	else{
		return (t2.goalIdx % _size < t2.goalIdx % _size);
	}
}

bool	Node::isColConflict(int idx1, int idx2)
{
	if (idx1 % _size != idx2 % _size)
		return false;
	tile& t1 = _tiles[idx1];
	tile& t2 = _tiles[idx2];
	if (!t1.isRightCol || !t2.isRightCol || t1.val == 0 || t2.val == 0)
		return false;
	if (idx1 / _size < idx2 / _size)
	{
		return (t1.goalIdx / _size > t2.goalIdx / _size);
	}
	else
	{
		return (t1.goalIdx / _size < t2.goalIdx / _size);
	}
}


void	Node::updateTileLine(int line, int idx, int oldval)
{
	_tiles[line*_size + idx].rowConflict.clear();
	for (int jdx = 0; jdx < (int)_size; jdx++)
	{
		if (jdx == idx)
			continue;
		_tiles[line*_size + jdx].rowConflict.erase(oldval);
		if (isRowConflict(line+idx, line+jdx))
		{
			_tiles[line*_size + idx].rowConflict.insert(_tiles[line*_size+jdx].val);
			_tiles[line*_size+jdx].rowConflict.insert(_tiles[line*_size+idx].val);
		}
	}
}

void	Node::updateTileCol(int col, int idx, int oldval)
{
	_tiles[idx*_size + col].colConflict.clear();
	for (int line = 0; line < (int)_size; line++)
	{
		if (line == idx)
			continue;
		_tiles[line*_size + col].colConflict.erase(oldval);
		if (isColConflict(line*_size+col, idx*_size+col))
		{
			_tiles[line*_size + col].colConflict.insert(_tiles[idx*_size+col].val);
			_tiles[idx*_size + col].colConflict.insert(_tiles[line*_size+col].val);
		}
	}

}
 //called when swapping two tiles when generating children -> will compute the two lines or columns affected by the swap
void Node::updateTile(int idx1, int idx2)
{
	int oldval1 = _tiles[idx1].val;
	int oldval2 = _tiles[idx2].val;
	std::swap(_tiles[idx1], _tiles[idx2]);
	_tiles[idx1].isRightCol = idx1 %  _size == _tiles[idx1].goalIdx % _size;
	_tiles[idx1].isRightRow = idx1 / _size == _tiles[idx1].goalIdx / _size;
	_tiles[idx2].isRightCol = idx2 %  _size == _tiles[idx2].goalIdx % _size;
	_tiles[idx2].isRightRow = idx2 / _size == _tiles[idx2].goalIdx / _size;

	if (idx1 / _size == idx2 / _size) // on a change de colomne
	{
		
		updateTileCol(idx1 % _size, idx1 / _size, oldval1);
		updateTileCol(idx2 % _size, idx2 / _size, oldval2);
	}
	else{ // on a change de ligne
		updateTileLine(idx1 / _size, idx1 % _size, oldval1);
		updateTileLine(idx2 / _size, idx2 % _size, oldval2);
	}
}


void	Node::debugSwapTile(int idx1, int idx2)
{
	updateTile(idx1, idx2);
}