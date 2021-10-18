#include "Enemy.h"
#include "time.h"

void Enemy::initTexture()
{
	//Load a texture from file
	if (!this->enemyTexture.loadFromFile("Textures/Zombie_Movement.png"))
	{
		std::cout << "ERROR::ENEMY::INITTEXTURE::Could not load textures file." << "\n";
	}
}

void Enemy::initSprite()
{
	//Set the texture to the sprite
	this->enemySprite.setTexture(this->enemyTexture);
	this->enemySprite.setTextureRect(IntRect(0, 0, this->enemyTexture.getSize().x / 3, this->enemyTexture.getSize().y / 4));

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
	this->animation = 0;
	this->dir_x = 0;
	this->dir_y = 0;
	this->last_dir_x = -1;
	this->last_dir_y = -1;
}

void Enemy::initDirectionVar(float dirX, float dirY)
{
	if (dirY == 1080 && dirX >= 0 && dirX <= 1920)		//Enemies move up
	{
		this->speed_y = -1.f;
		this->speed_x = 0.f;
		this->enemySprite.setTextureRect(IntRect(
			(this->enemyTexture.getSize().x/3)*(this->animation),		//Position of model x
			(this->enemyTexture.getSize().y / 4) * 3,					//Postion of model y
			this->enemyTexture.getSize().x / 3,							//Set size x
			this->enemyTexture.getSize().y / 4));						//Set size y
	}
	if (dirY == -100 && dirX >= 0 && dirX <= 1920)		//Enemies move down
	{
		this->speed_y = 1.f;
		this->speed_x = 0.f;
		this->enemySprite.setTextureRect(IntRect(
			(this->enemyTexture.getSize().x / 3) * (this->animation),		//Position of model x
			(this->enemyTexture.getSize().y / 4) * 0,						//Postion of model y
			this->enemyTexture.getSize().x / 3,								//Set size x
			this->enemyTexture.getSize().y / 4));							//Set size y
	}
	if (dirX == 0 && dirY >= 0 && dirY <= 1080)			//Enemies move right
	{
		this->speed_y = 0.f;
		this->speed_x = 1.f;
		this->enemySprite.setTextureRect(IntRect(
			(this->enemyTexture.getSize().x / 3) * (this->animation),		//Position of model x
			(this->enemyTexture.getSize().y / 4) * 1,						//Postion of model y
			this->enemyTexture.getSize().x / 3,								//Set size x
			this->enemyTexture.getSize().y / 4));							//Set size y
	}
	if (dirX == 1920 && dirY >= 0 && dirY <= 1080)		//Enemies move left
	{
		this->speed_y = 0.f;
		this->speed_x = -1.f;
		this->enemySprite.setTextureRect(IntRect(
			(this->enemyTexture.getSize().x / 3) * (this->animation),		//Position of model x
			(this->enemyTexture.getSize().y / 4) * 2,						//Postion of model y
			this->enemyTexture.getSize().x / 3,								//Set size x
			this->enemyTexture.getSize().y / 4));							//Set size y
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

void Enemy::updateEnemyMoveUpDown()
{
	this->time = clock.getElapsedTime().asSeconds();
	if (this->time > 1)
	{
		if (this->dir_x == 0)
		{
			this->dir_x = rand() % 2 - 1;
			if (this->dir_x == 0) this->dir_x = 1;
		}
		else if (this->dir_x == -1)
		{
			this->dir_x = rand() % 2;
		}
		else if (this->dir_x == 1)
		{
			this->dir_x = rand() % 2 - 1;
		}
		clock.restart();
	}

	this->enemySprite.move(this->speed_x + this->dir_x, this->speed_y);
}

void Enemy::updateEnemyMoveLeftRight()
{
	this->time = clock.getElapsedTime().asSeconds();
	if (this->time > 1)
	{
		if (this->dir_y == 0)
		{
			this->dir_y = rand() % 2 - 1;
			if (this->dir_y == 0) this->dir_y = 1;
		}
		else if (this->dir_y == -1)
		{
			this->dir_y = rand() % 2;
		}
		else if (this->dir_y == 1)
		{
			this->dir_y = rand() % 2 - 1;
		}
		clock.restart();
	}

	this->enemySprite.move(this->speed_x, this->speed_y + this->dir_y);
}

//Functions
void Enemy::update()
{

}

void Enemy::render(RenderTarget* target)
{
	target->draw(this->enemySprite);
}

