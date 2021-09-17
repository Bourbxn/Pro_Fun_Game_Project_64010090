#include "Enemy.h"
#include "time.h"

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
	this->hp		= 10;
	this->hpMax		= 0;		
	this->damage	= 1;
	this->points	= 5;
}

void Enemy::initDirectionVar(float dirX, float dirY)
{
	if (dirY == 1200 && dirX >= 0 && dirX <= 1600)		//Enemies move up
	{
		this->speed_y = -1.f;
		this->speed_x = 0.f;
	}
	if (dirY == -100 && dirX >= 0 && dirX <= 1600)		//Enemies move down
	{
		this->speed_y = 1.f;
		this->speed_x = 0.f;;
	}
	if (dirX == 0 && dirY >= 0 && dirY <= 1200)			//Enemies move right
	{
		this->speed_y = 0.f;
		this->speed_x = 1.f;
	}
	if (dirX == 1600 && dirY >= 0 && dirY <= 1200)		//Enemies move left
	{
		this->speed_y = 0.f;
		this->speed_x = -1.f;
	}
}

Enemy::Enemy(float pos_x,float pos_y)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->enemySprite.setPosition(pos_x, pos_y);
	this->initDirectionVar(pos_x, pos_y);
	
	

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
	this->enemySprite.move(this->speed_x, this->speed_y);
}

void Enemy::render(RenderTarget* target)
{
	target->draw(this->enemySprite);
}

