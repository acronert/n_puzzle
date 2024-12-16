# include "NPuzzle.class.hpp"


int	main(int argc, char** argv) {
	(void)argv;

	if (argc < 2)
		return -1;

	try {
		NPuzzle n_puzzle;
		n_puzzle.run(argc, argv);

	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}



