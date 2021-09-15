#ifndef ENEMY_H
#define ENEMY_H

#pragma once
#include "iostream"
#include "vector"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
#include "time.h"
using namespace sf;

class Enemy
{
private:
	Sprite enemySprite;
	Texture enemyTexture;
	//CircleShape shape;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initTexture();
	//void initShape();
	void initSprite();
	void initVariables();
public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	//Accessor
	const FloatRect getBounds() const;
	
	//Functions
	void update();
	void render(RenderTarget* target);
};

#endif //!ENEMY: