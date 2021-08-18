#include "iostream"
#include "Game.h"
using namespace sf;

int main() {
	//Init Game Engine
	Game game;

	//Game loop
	while (game.running())
	{
	
		//Upddate
		game.update();

		//Render
		game.render();
	}
	return 0;
}