#include "Node.class.hpp"

Node::Node() {

}

Node::~Node() {

}

Node::Node(const Node& other) {

}

Node& Node::operator=(const Node& other) {
	if (this != &other) {
		(void)other;
	}
	return *this;
}
