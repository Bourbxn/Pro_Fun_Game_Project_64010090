#include "Player.h"

void Player::initVariables()
{
	this->movementspeed = 6.f;
	this->attackCooldownMax = 15.f;
	this->attackCooldown = this->attackCooldownMax;
}

void Player::initTexture()
{
	//Load a texture from file
	if (!this->texture.loadFromFile("Textures/ship.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load textures file." << "\n";
	}
}

void Player::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);

	//Resize the sprite
	this->sprite.scale(2.5f, 2.5f);
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{

}

const Vector2f & Player::getPos() const
{
	return this->sprite.getPosition();
}

const FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}


void Player::move(const float dir_X, const float dir_Y)
{
	this->sprite.move(this->movementspeed * dir_X, this->movementspeed * dir_Y);
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}

	return false;
}

void Player::updateAttack()
{
	if(this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;
}

//Functions
void Player::update()
{
	this->updateAttack();
}

void Player::render(RenderTarget& target)
{
	target.draw(this->sprite);
}
