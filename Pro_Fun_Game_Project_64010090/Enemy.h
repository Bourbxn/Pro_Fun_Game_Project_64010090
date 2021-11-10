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
	Clock clock;

	int type;
	float time;
	float speed_y;
	float speed_x;
	int dir_y;
	int last_dir_x;
	int dir_x;
	int last_dir_y;
	int hp;
	int hpMax;
	int damage;
	int points;
	int animation;

	void initTexture();
	void initSprite();
	void initVariables();
	void initDirectionVar(float dirX,float dirY, float speedDependsPowerMinus, float speedDependsPowerPlus);

public:
	Enemy(float pos_x, float pos_y, float speedDependsPowerMinus, float speedDependsPowerPlus);
	virtual ~Enemy();

	//Accessor
	const FloatRect getBounds() const;
	
	//Functions
	void updateEnemyMoveUpDown();
	void updateEnemyMoveLeftRight();
	void update();
	void render(RenderTarget* target);
};

#endif //!ENEMY: