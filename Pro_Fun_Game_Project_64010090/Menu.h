#pragma once
#include "iostream"
#include "vector"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
using namespace sf;

#define maxItem 3


class Menu
{
private:
	Sprite spriteMenuBG;
	Texture textureMenuBG;
	Sprite spriteMenuLogo;
	Texture textureMenuLogo;
	Text menu[maxItem];
	Text nameKMITL;
	Text numberKMITL;
	Text moveH2P;
	Text shootH2P;
	Text enterH2P;
	Text escH2P;
	Font font;

	//Private Function
	void initVariables();
	void initTexture();
	void initSprite();
	void initText();
	void initHowToPlay();
	void initNameKMITL();

	//Variables
	int selectedMenu;
	int fontSize;
	int fontThickness;
	int selectedDelay;
	int selectedDelayMax;
	int GameState;

public:
	Menu();
	virtual ~Menu();
	
	//Assescor
	const int& getGameState() const;

	//Update
	void updateInput();
	void setNewMenuState();


	//render
	void render(RenderTarget& target);
};

