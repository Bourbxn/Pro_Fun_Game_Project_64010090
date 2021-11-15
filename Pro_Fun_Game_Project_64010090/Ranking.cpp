#include "Ranking.h"

void Ranking::initBackground()
{
	if (!this->backgroundTex.loadFromFile("Textures/menu_bg.png"))
	{
		std::cout << "ERROR::GUN::INITTEXTURE::Could not load textures file." << "\n";
	}
	this->background.setTexture(this->backgroundTex);
	this->background.setScale(1.f, 1.f);
	this->background.setPosition(0, 0);
}

void Ranking::initText()
{

}

Ranking::Ranking(int x, int y, std::string word, Font* font)
{
	this->initBackground();
	this->text.setFont(*font);
	this->text.setPosition(x, y);
	this->text.setString(word);
	this->text.setOutlineThickness(10);
	this->text.setCharacterSize(100);
}

Ranking::~Ranking()
{

}

void Ranking::getSize()
{
	this->text.getGlobalBounds().width;
}

void Ranking::renderBackground(RenderTarget& target)
{
	target.draw(this->background);
}

void Ranking::render(RenderTarget& target)
{
	target.draw(this->text);
}
