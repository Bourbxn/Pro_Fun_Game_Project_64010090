#pragma once
#include "iostream"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
using namespace sf;

class Game
{
private:
	//Variables
	//Windows
	RenderWindow* window;
	VideoMode videoMode;
	Event ev;

	//Game objects
	RectangleShape enemy;

	//Private Functions
	void initVariables();
	void initWindow();
	void initEnemy();
public:
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;

	//Functions
	void pollEvents();
	void update();
	void render();
};


