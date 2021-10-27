#include "Vaccine.h"

void Vaccine::initVariables()
{
	this->infectedType = 0;
}

void Vaccine::initTexture()
{
	if (!this->texture.loadFromFile("Textures/player_not_infected.png"))
	{
		std::cout << "ERROR::GUN::INITTEXTURE::Could not load textures file." << "\n";
	}
}

void Vaccine::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);

	//Resize the sprite
	this->sprite.scale(1.f, 1.f);

	//Set Position the sprite
	this->sprite.setPosition(Vector2f(18.f,45.f));
}

Vaccine::Vaccine()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Vaccine::~Vaccine()
{

}

void Vaccine::updateSpriteTextures(int infectedType)
{
	if (infectedType == 0)
	{
		if (!this->texture.loadFromFile("Textures/player_not_infected.png"))
		{
			std::cout << "ERROR::GUN::INITTEXTURE::Could not load textures file." << "\n";
		}
	}
	else if (infectedType == 1)
	{
		if (!this->texture.loadFromFile("Textures/player_infected.png"))
		{
			std::cout << "ERROR::GUN::INITTEXTURE::Could not load textures file." << "\n";
		}
	}
	else if (infectedType == 2)
	{
		if (!this->texture.loadFromFile("Textures/player_no_way_infected.png"))
		{
			std::cout << "ERROR::GUN::INITTEXTURE::Could not load textures file." << "\n";
		}
	}
}

void Vaccine::updateSprite()
{
	this->sprite.setTexture(this->texture);
}

void Vaccine::update()
{
	this->updateSprite();
}

void Vaccine::render(RenderTarget& target)
{
	target.draw(this->sprite);
}
