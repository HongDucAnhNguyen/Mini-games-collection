
#include "../Header Files/Game.h"

#include <time.h>


int main()
{

	srand(static_cast<unsigned int>(time(0)));

	try {
		Game game;
		game.run();
	}

	catch (std::exception& e
		) {
		std::cout << e.what() << std::endl;

	}


	return 0;
}