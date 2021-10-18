#include "Gun.h"

void Gun::initVariables()
{
	this->movementspeed = 5.f;
	this->gunType = 0;
}

void Gun::initTexture()
{
	if (!this->texture.loadFromFile("Textures/Pistol_common_01.png"))
	{
		std::cout << "ERROR::GUN::INITTEXTURE::Could not load textures file." << "\n";
	}
}

void Gun::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(IntRect(0, 0, this->texture.getSize().x , this->texture.getSize().y / 4));


	//Resize the sprite
	this->sprite.scale(0.7f, 0.7f);

	//Set Position the sprite
	this->sprite.setPosition(800.f - (this->texture.getSize().x / 3.f) + 12.5f, 600.f - (this->texture.getSize().y / 4.f) + 95.f);
}

Gun::Gun()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Gun::~Gun()
{

}

const Vector2f& Gun::getPos() const
{
	return this->sprite.getPosition();
}

void Gun::move(const float dir_X, const float dir_Y)
{
	this->sprite.move(this->movementspeed * dir_X, this->movementspeed * dir_Y);
}

void Gun::updateSpriteTextures(int gunType)
{
	if (gunType == 1)
	{
		if (!this->texture.loadFromFile("Textures/Uzi_rare_02.png"))
		{
			std::cout << "ERROR::GUN::INITTEXTURE::Could not load textures file." << "\n";
		}
	}

	else if (gunType == 2)
	{
		/*
		if (!this->texture.loadFromFile("Textures/Uzi_rare_02.png"))
		{
			std::cout << "ERROR::GUN::INITTEXTURE::Could not load textures file." << "\n";
		}
		*/
	}
}

void Gun::updateSprite()
{
	if (Keyboard::isKeyPressed(Keyboard::Key::Left))
	{
		this->sprite.setTextureRect(IntRect(
			0,
			(this->texture.getSize().y / 4)*2,
			this->texture.getSize().x,
			this->texture.getSize().y / 4));
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Right))
	{
		this->sprite.setTextureRect(IntRect(
			0,
			(this->texture.getSize().y / 4) * 1,
			this->texture.getSize().x,
			this->texture.getSize().y / 4));
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Up))
	{
		this->sprite.setTextureRect(IntRect(
			0,
			(this->texture.getSize().y / 4) * 3,
			this->texture.getSize().x,
			this->texture.getSize().y / 4));
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Down))
	{
		this->sprite.setTextureRect(IntRect(
			0,
			(this->texture.getSize().y / 4) * 0,
			this->texture.getSize().x,
			this->texture.getSize().y / 4));
	}
}


void Gun::updatePosSprite(float pos_x, float pos_y)
{
	this->sprite.setPosition(pos_x, pos_y);
}


//Functions
void Gun::update()
{
	this->updateSprite();
}

void Gun::render(RenderTarget& target)
{
	target.draw(this->sprite);
}
