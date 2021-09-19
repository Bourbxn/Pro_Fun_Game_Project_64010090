#pragma once
#include "iostream"
#include "SFML/Graphics.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
using namespace sf;
#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
private:
	Font font;
	Text menu[MAX_NUMBER_OF_ITEMS];

	//Init Variables
	int selectedItemIndex;
	int fontSize;

	//Private Functions
	void initVariables();
	void initMenu(float w, float h);
	void initGUI();
public:
	Menu(float width, float height);
	~Menu();
	//Variables
	int getPressedMenu();

	void draw(RenderWindow& window);
	void moveUp();
	void moveDown();
};

