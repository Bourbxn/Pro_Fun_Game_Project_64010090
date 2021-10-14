#ifndef ENTITY_H
#define ENTITY_H

#include "vector"
#include "stack"
#include "map"
#include "string"
#include "sstream"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<vector>
#include<stack>
#include<map>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"

class Entity
{

private:

protected:
	RectangleShape shape;
	float movementSpeed;

public:
	Entity();
	virtual ~Entity();

	//Functions
	virtual void move(const float& dt,const float x, const float y);

	virtual void update(const float& dt);
	virtual void render(RenderTarget& target);
};

#endif