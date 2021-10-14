#include "MainMenuState.h"

void MainMenuState::initKeybinds()
{

}



MainMenuState::MainMenuState(RenderWindow* window, std::map<std::string, int>* supportedKeys)
{

}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::endState()
{
	std::cout << "Ending States\n";
}

void MainMenuState::updateInput(const float& dt)
{

}

void MainMenuState::update(const float& dt)
{
	this->updateKeyBinds(dt);

}

void MainMenuState::render(RenderTarget* target)
{

}
