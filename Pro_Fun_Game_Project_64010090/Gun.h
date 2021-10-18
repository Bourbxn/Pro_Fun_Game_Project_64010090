#pragma once
#include "iostream"
#include "vector"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
using namespace sf;


class Gun
{
private:
	Sprite sprite;
	Texture texture;

	float movementspeed;

	int gunType;

	//Private Functions
	void initVariables();
	void initTexture();
	void initSprite();
public:
	Gun();
	virtual ~Gun();

	//Accessor
	const Vector2f& getPos() const;


	//Functions
	void move(const float dir_X, const float dir_Y);
	void updateSpriteTextures(int gunType);
	void updateSprite();
	void updatePosSprite(float pos_x,float pos_y);
	void update();
	void render(RenderTarget& target);
};

