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
	CircleShape shape;
	int type;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initShape();
	void initVariables();
public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	//Functions
	void update();
	void render(RenderTarget* target);
};

#endif //!ENEMY: