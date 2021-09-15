#include "Enemy.h"
#include "time.h"

/*
void Enemy::initShape()
{
	this->shape.setRadius(rand() % 50 + 20);
	this->shape.setPointCount(rand() % 20+ 3);
	this->shape.setFillColor(Color(rand() % 200 + 55, rand() % 255 + 1, rand() % 255 + 1));
}
*/

void Enemy::initTexture()
{
	//Load a texture from file
	if (!this->enemyTexture.loadFromFile("Textures/enemy.png"))
	{
		std::cout << "ERROR::ENEMY::INITTEXTURE::Could not load textures file." << "\n";
	}
}

void Enemy::initSprite()
{
	//Set the texture to the sprite
	this->enemySprite.setTexture(this->enemyTexture);

	//Resize the sprite
	this->enemySprite.scale(2.5f, 2.5f);
}

void Enemy::initVariables()
{
	this->type		= 0;
	this->speed		= 2.f;
	this->hp		= 10;
	this->hpMax		= 0;		
	this->damage	= 1;
	this->points	= 5;
}

Enemy::Enemy(float pos_x,float pos_y)
{
	this->initVariables();
	this->initTexture();
	//this->initShape();
	this->initSprite();
	this->enemySprite.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{
	 
}

//Accessors
const FloatRect Enemy::getBounds() const
{
	return this->enemySprite.getGlobalBounds();
}


//Functions
void Enemy::update()
{
	this->enemySprite.move(0.f, this->speed);
}

void Enemy::render(RenderTarget* target)
{
	target->draw(this->enemySprite);
}

