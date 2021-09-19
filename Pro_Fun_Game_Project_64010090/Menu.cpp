#include "Menu.h"

void Menu::initVariables()
{
	this->selectedItemIndex = 0;
	this->fontSize = 50;
}

void Menu::initMenu(float w,float h)
{
	this->menu[0].setFont(this->font);
	this->menu[0].setCharacterSize(this->fontSize);
	this->menu[0].setFillColor(Color::Red);
	this->menu[0].setOutlineColor(Color::Black);
	this->menu[0].setOutlineThickness(3);
	this->menu[0].setString("Play");
	this->menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
	this->menu[0].setPosition(Vector2f(w / 2, h / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	this->menu[1].setFont(this->font);
	this->menu[1].setCharacterSize(this->fontSize);
	this->menu[1].setFillColor(Color::White);
	this->menu[1].setOutlineColor(Color::Black);
	this->menu[1].setOutlineThickness(3);
	this->menu[1].setString("Leaderboard");
	this->menu[1].setOrigin(menu[1].getLocalBounds().width / 2, menu[1].getLocalBounds().height / 2);
	this->menu[1].setPosition(Vector2f(w / 2, h/ (MAX_NUMBER_OF_ITEMS + 1) * 2));

	this->menu[2].setFont(this->font);
	this->menu[2].setCharacterSize(this->fontSize);
	this->menu[2].setFillColor(Color::White);
	this->menu[2].setOutlineColor(Color::Black);
	this->menu[2].setOutlineThickness(3);
	this->menu[2].setString("Exit");
	this->menu[2].setOrigin(menu[2].getLocalBounds().width / 2, menu[2].getLocalBounds().height / 2);
	this->menu[2].setPosition(Vector2f(w / 2, h/ (MAX_NUMBER_OF_ITEMS + 1) * 3));
}

void Menu::initGUI()
{
	//Load font
	if (!this->font.loadFromFile("Fonts/ARCADECLASSIC.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";
}

Menu::Menu(float width, float height)
{
	this->initVariables();
	this->initGUI();
	this->initMenu(width,height);
}

Menu::~Menu()
{

}

int Menu::getPressedMenu()
{
	return selectedItemIndex;
}

void Menu::draw(RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(this->menu[i]);
	}
}

void Menu::moveUp()
{
	if (this->selectedItemIndex - 1 >= 0)
	{
		this->menu[this->selectedItemIndex].setFillColor(Color::White);
		this->selectedItemIndex--;
		this->menu[this->selectedItemIndex].setFillColor(Color::Red);
	}
}

void Menu::moveDown()
{
	if (this->selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		this->menu[selectedItemIndex].setFillColor(Color::White);
		this->selectedItemIndex++;
		this->menu[selectedItemIndex].setFillColor(Color::Red);
	}
}
