# include "NPuzzle.class.hpp"

int	main(int argc, char** argv) {
	try {
		NPuzzle n_puzzle;
		n_puzzle.run(argc, argv);

	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		usage();
	}
	return 0;
}
