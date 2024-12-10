# include "Node.class.hpp"
# include "Astar.hpp"
# include "utils.hpp"



# include <chrono>

int	main(int argc, char** argv) {
	(void)argv;
	if (argc != 2)
		return -1;

	try {
		// Initialize
		std::vector<uint32_t> start = parse(argv[1]);
		int	size = std::sqrt(start.size());
		std::vector<uint32_t> goal = build_goal(size);

		Node *node = new Node(start, goal, size);

		std::cout << "===== Start =====\n";
		node->display();
		std::cout << "=================\n";


		auto start_time = std::chrono::high_resolution_clock::now();
		// Execute A*
		std::vector<Node> path = astar<Node, std::vector<uint32_t>>(node);

		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
		std::cout << "A* took " << duration.count() / 1000 << "ms\n";
		// Display Path
		// std::cout << "Path found, displaying: \n";
		// for (auto node = path.rbegin(); node != path.rend(); ++node)
		// 	node->display();

		while(1)
			replay(path);

	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
