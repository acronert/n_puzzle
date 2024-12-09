# include "Node.class.hpp"
# include "Astar.hpp"
# include "utils.hpp"

int	main(int argc, char** argv) {
	(void)argv;
	if (argc != 2)
		return -1;

	try {
		// Initialize
		std::vector<int> start = parse(argv[1]);
		int	size = std::sqrt(start.size());
		std::vector<int> goal = build_goal(size);

		Node *node = new Node(start, goal, size);

		std::cout << "===== Start =====\n";
		node->display();
		std::cout << "=================\n";

		// Execute A*
		std::vector<Node> path = astar(node);

		// Display Path
		std::cout << "Path found, displaying: \n";
		for (auto node = path.rbegin(); node != path.rend(); ++node)
			node->display();

	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
