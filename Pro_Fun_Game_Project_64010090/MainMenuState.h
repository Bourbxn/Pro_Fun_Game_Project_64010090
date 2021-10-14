#ifndef  MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "State.h"

class MainMenuState :
	public State 
{
private:
	//Functions
	void initKeybinds();

public:
	MainMenuState(RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~MainMenuState();

	//Functions
	void endState();
	
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};

#endif
