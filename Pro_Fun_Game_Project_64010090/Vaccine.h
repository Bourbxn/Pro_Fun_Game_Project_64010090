#pragma once
#include "iostream"
#include "vector"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
using namespace sf;


class Vaccine
{
private:
	Sprite sprite;
	Texture texture;

	int infectedType;

	//Private Functions
	void initVariables();
	void initTexture();
	void initSprite();
public:
	Vaccine();
	virtual ~Vaccine();

	//Accessor

	//Functions
	void updateSpriteTextures(int infectedType);
	void updateSprite();
	void update();
	void render(RenderTarget& target);
};

