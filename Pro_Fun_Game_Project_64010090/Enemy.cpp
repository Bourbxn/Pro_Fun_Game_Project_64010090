#include "Enemy.h"
#include "time.h"

void Enemy::initShape()
{
	this->shape.setRadius(rand() % 50 + 20);
	this->shape.setPointCount(rand() % 20+ 3);
	this->shape.setFillColor(Color(rand() % 200 + 55, rand() % 255 + 1, rand() % 255 + 1));
}

void Enemy::initVariables()
{
	this->type		= 0;
	this->hp		= 10;
	this->hpMax		= 0;		
	this->damage	= 1;
	this->points	= 5;
}

Enemy::Enemy(float pos_x,float pos_y)
{
	this->initShape();
	this->initVariables();
	
	this->shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{
	 
}

//Functions
void Enemy::update()
{

}

void Enemy::render(RenderTarget* target)
{
	target->draw(this->shape);
}
