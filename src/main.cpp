# include "NPuzzle.class.hpp"


int	main(int argc, char** argv) {
	try {
		NPuzzle n_puzzle;
		n_puzzle.run(argc, argv);

	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "USAGE :" << std::endl;
		std::cout << "	./n_puzzle INPUT_FILE [OPTIONS]" << std::endl;
		std::cout << std::endl;
		std::cout << "OPTIONS :" << std::endl;
		std::cout << "	Algorithm: " << std::endl;
		std::cout << "		-s	standard A*" << std::endl;
		std::cout << "		-g	greedy A*" << std::endl;
		std::cout << "		-u	uniform A*" << std::endl;
		std::cout << "	Heuristics (choose one) :" << std::endl;
		std::cout << "		-h1	Manhattan Distance" << std::endl;
		std::cout << "		-h2	Misplaced Tiles" << std::endl;
		std::cout << "		-h3	Linear Conflict" << std::endl;
	}
	return 0;
}



