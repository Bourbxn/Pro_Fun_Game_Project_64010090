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

void Ranking::initBackgroundGameOver()
{
	if (!this->backgroundGameOverTex.loadFromFile("Textures/map.png"))
	{
		std::cout << "ERROR::GUN::INITTEXTURE::Could not load textures file." << "\n";
	}
	this->backgroundGameOver.setTexture(this->backgroundGameOverTex);
	this->backgroundGameOver.setScale(3.f, 3.f);
	this->backgroundGameOver.setPosition(0, 0);
	this->backgroundGameOver.setColor(Color(255,255,255,50));
}

void Ranking::initText()
{

}

Ranking::Ranking(int x, int y, std::string word, Font* font)
{
	this->initBackgroundGameOver();
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

void Ranking::setFontColor(Color color)
{
	this->text.setFillColor(color);
}

void Ranking::setFontSize(int size)
{
	this->text.setCharacterSize(size);
}

void Ranking::renderBackground(RenderTarget& target)
{
	target.draw(this->background);
}

void Ranking::renderBackgroundGameOver(RenderTarget& target)
{
	target.draw(this->backgroundGameOver);
}

void Ranking::render(RenderTarget& target)
{
	target.draw(this->text);
}
