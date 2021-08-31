#include "Game.h"
#include "time.h"

int main()
{
	srand(time(NULL));
	

	Game game;

	game.run();

	//End of application
	return 0;
}