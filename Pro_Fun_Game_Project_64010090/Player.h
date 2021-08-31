#pragma once
#include "iostream"
#include "vector"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
using namespace sf;


class Player
{
private:
	Sprite sprite;
	Texture texture;

	float movementspeed;

	float attackCooldown;
	float attackCooldownMax;

	//Private Functions
	void initVariables();
	void initTexture();
	void initSprite();
public:
	Player();
	virtual ~Player();

	//Accessor
	const Vector2f& getPos() const;

	//Functions
	void move(const float dir_X, const float dir_Y);
	const bool canAttack();

	void updateAttack();
	void update();
	void render(RenderTarget& target);
};

