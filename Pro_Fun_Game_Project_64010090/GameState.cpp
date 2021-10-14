#include "GameState.h"

GameState::GameState(RenderWindow* window)
	:State(window)
{

}

GameState::~GameState()
{

}

void GameState::endState()
{
	std::cout << "Ending States\n";
}

void GameState::updateKeyBinds(const float& dt)
{
	this->checkForQuit();
	if (Keyboard::isKeyPressed(Keyboard::A))
		std::cout << "A\n";
}

void GameState::update(const float& dt)
{
	this->updateKeyBinds(dt);

}

void GameState::render(RenderTarget* target)
{

}
