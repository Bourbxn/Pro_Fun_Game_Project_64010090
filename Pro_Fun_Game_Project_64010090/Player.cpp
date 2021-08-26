#include "Player.h"

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
	this->sprite.scale(0.3f, 0.3f);
}

Player::Player()
{
	this->movementspeed = 7.f;
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


void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementspeed * dirX, this->movementspeed * dirY);
}

//Functions
void Player::update()
{

}

void Player::render(RenderTarget& target)
{
	target.draw(this->sprite);
}
