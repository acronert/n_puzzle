# include "Node.class.hpp"
# include "Astar.hpp"
# include "utils.hpp"



# include <chrono>
# include <algorithm>

int	main(int argc, char** argv) {
	(void)argv;

	bool	algoType[3] = {true, true, false};
	std::vector<std::vector<Node>>	paths;
	if (argc != 2)
		return -1;

	try {
		// Initialize
		std::vector<uint32_t> start = parse(argv[1]);
		int	size = std::sqrt(start.size());

		std::vector<uint32_t> goal = build_goal(size);

		for (int i = 0; i < 3; i++) {
			if (algoType[i]) {
				Node *node = new Node(start, goal, size, i);

				std::cout << "===== Start =====\n";
				node->display(0);
				std::cout << "=================\n";

				auto start_time = std::chrono::high_resolution_clock::now();
				// Execute A*
				paths.push_back(astar<Node, std::vector<uint32_t>>(node));

				auto end_time = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
				std::string type = "standard";
				if (i == GREEDY)
					type = "greedy";
				else if (i == UNIFORM)
					type = "uniform";

				std::cout << "A* (" << type << ") took " << duration.count() / 1000 << "ms\n";
			}
		}



		std::size_t max = 0;
		for (size_t i = 0; i < paths.size(); i++) {
			max = std::max(paths[i].size(), max);
		}
		while (1) {
			for (size_t i = 0; i < max; i++) {
				for (size_t j = 0; j < paths.size(); j++) {
					if (i < paths[j].size()) {
						paths[j][i].display(j * (paths[0][0].getSize() * 5) + 1);
						std::cout << "\033[" << paths[0][0].getSize() << "A";    // Move cursor up one line
					}
				}
				usleep(400000);
			}
		}


		// while(1)
			// replay(path);

	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
