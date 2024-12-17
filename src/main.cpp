# include "NPuzzle.class.hpp"


// int	main(int argc, char** argv) {
// 	(void)argv;

// 	if (argc != 2)
// 		return -1;

// 	try {
// 		NPuzzle n_puzzle;
// 		n_puzzle.run(argv[1]);

// 	} catch (const std::exception& e) {
// 		std::cout << e.what() << std::endl;
// 	}
// 	return 0;
// }


int	main()
{
	Node	start = Node({7,2,3,1,0,4,8,6,5}, {1,2,3,8,0,4,7,6,5}, 3, 0,2);
	start.debugTiles();
	start.debugSwapTile(3,4);
	std::cout << "\nTILE SWAPPED" << std::endl;
	start.debugTiles();
}

