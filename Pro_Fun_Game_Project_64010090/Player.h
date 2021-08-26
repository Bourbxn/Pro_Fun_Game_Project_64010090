#pragma once
#include "iostream"
#include "vector"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
#include "ctime"
using namespace sf;


class Player
{
private:
	Sprite sprite;
	Texture texture;

	float movementspeed;

	//Private Functions
	void initTexture();
	void initSprite();
public:
	Player();
	virtual ~Player();

	//Accessor
	const Vector2f& getPos() const;

	//Functions
	void move(const float dirX, const float dirY);
	void update();
	void render(RenderTarget& target);
};

