#include "Player.h"

void Player::initVariables()
{
	this->animation = 0;
	this->animationDelay = 6;

	this->movementspeed = 5.f;
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;

	this->hpMax = 100;
	this->hp = this->hpMax;
}

void Player::initTexture()
{
	//Load a texture from file
	if (!this->texture.loadFromFile("Textures/Bourbxn_Movement4.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load textures file." << "\n";
	}
}

void Player::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(IntRect(0, 0, this->texture.getSize().x/3, this->texture.getSize().y / 4));
	

	//Resize the sprite
	this->sprite.scale(2.5f, 2.5f);

	//Set Position the sprite
	this->sprite.setPosition(800.f-(this->texture.getSize().x/3.f),600.f- (this->texture.getSize().y / 4.f));
	
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

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
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

void Player::updateSprite()
{
	if (Keyboard::isKeyPressed(Keyboard::Key::Left))
	{
		this->sprite.setTextureRect(IntRect(
			(this->animation/this->animationDelay) *(this->texture.getSize().x/3),
			(this->texture.getSize().y / 4) * 2,
			this->texture.getSize().x/3, 
			this->texture.getSize().y / 4));
		this->animation++;
		if (animation == (this->animationDelay * 3) - 1) this->animation = 0;
	}	
	if (Keyboard::isKeyPressed(Keyboard::Key::Right))
	{
		this->sprite.setTextureRect(IntRect(
			(this->animation / this->animationDelay) * (this->texture.getSize().x / 3),
			(this->texture.getSize().y / 4) * 1,
			this->texture.getSize().x / 3,
			this->texture.getSize().y / 4));
		this->animation++;
		if (animation == (this->animationDelay * 3)-1) this->animation = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Up))
	{
		this->sprite.setTextureRect(IntRect(
			(this->animation / this->animationDelay) * (this->texture.getSize().x / 3),
			(this->texture.getSize().y / 4) * 3,
			this->texture.getSize().x / 3,
			this->texture.getSize().y / 4));
		this->animation++;
		if (animation == (this->animationDelay * 3) - 1) this->animation = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Down))
	{
		this->sprite.setTextureRect(IntRect(
			(this->animation / this->animationDelay) * (this->texture.getSize().x / 3),
			(this->texture.getSize().y / 4) * 0,
			this->texture.getSize().x / 3,
			this->texture.getSize().y / 4));
		this->animation++;
		if (animation == (this->animationDelay * 3) - 1) this->animation = 0;
	}
}

void Player::updateAttackStatus(float attackCoolDownMaxUpdate)
{
	this->attackCooldownMax = attackCoolDownMaxUpdate;
}

void Player::updateAttack()
{
	if(this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;
}

//Functions
void Player::update()
{
	this->updateSprite();
	this->updateAttack();
}

void Player::render(RenderTarget& target)
{
	target.draw(this->sprite);
}
