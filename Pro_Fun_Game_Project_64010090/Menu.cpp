#include "Menu.h"

void Menu::initVariables()
{
	this->selectedDelay = 0;
	this->selectedDelayMax = 10;
	this->selectedMenu = 0;
	this->GameState = 1;
}

void Menu::initTexture()
{
	if (!this->textureMenuBG.loadFromFile("Textures/menu_bg.png"))
	{
		std::cout << "ERROR::GUN::INITTEXTURE::Could not load textures file." << "\n";
	}
}

void Menu::initSprite()
{
	//Set the texture to the sprite
	this->spriteMenuBG.setTexture(this->textureMenuBG);

	//Resize the sprite
	this->spriteMenuBG.scale(1.f, 1.f);

	//Set Position the sprite
	this->spriteMenuBG.setPosition(Vector2f(0.f, 0.f));
}

void Menu::initText()
{
	this->fontSize = 80;
	this->fontThickness = 8;
	//Load font
	if (!this->font.loadFromFile("Fonts/ARCADECLASSIC.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";
	//Set text
	this->menu[0].setFont(this->font);
	this->menu[0].setOutlineThickness(this->fontThickness);
	this->menu[0].setCharacterSize(this->fontSize);
	this->menu[0].setFillColor(Color::Red);
	this->menu[0].setString("Play");
	this->menu[0].setPosition(Vector2f(200, 200));


	this->menu[1].setFont(this->font);
	this->menu[1].setOutlineThickness(this->fontThickness);
	this->menu[1].setCharacterSize(this->fontSize);
	this->menu[1].setFillColor(Color::White);
	this->menu[1].setString("Ranking");
	this->menu[1].setPosition(Vector2f(200, 400));

	this->menu[2].setFont(this->font);
	this->menu[2].setOutlineThickness(this->fontThickness);
	this->menu[2].setCharacterSize(this->fontSize);
	this->menu[2].setFillColor(Color::White);
	this->menu[2].setString("Exit");
	this->menu[2].setPosition(Vector2f(200, 600));
	
	
}

void Menu::initNameKMITL()
{
	if (!this->font.loadFromFile("Fonts/ARCADECLASSIC.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";
	this->nameKMITL.setFont(this->font);
	this->nameKMITL.setPosition({
		1920 / 2  + 540,
		1080 / 2  + 400});
	this->nameKMITL.setString("jakkapat paijit");
	this->nameKMITL.setFillColor(Color(252, 183, 138));
	this->nameKMITL.setOutlineThickness(5);
	this->nameKMITL.setCharacterSize(50);

	this->numberKMITL.setFont(this->font);
	this->numberKMITL.setPosition({
		1920 / 2 + 710,
		1080 / 2 + 450 });
	this->numberKMITL.setString("64010090");
	this->numberKMITL.setFillColor(Color(252, 183, 138));
	this->numberKMITL.setOutlineThickness(5);
	this->numberKMITL.setCharacterSize(50);
}

Menu::Menu()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initText();
	this->initNameKMITL();
}

Menu::~Menu()
{

}

const int& Menu::getGameState() const
{
	return this->GameState;
}

void Menu::updateInput()
{
	//Update Input Selected Menu
	if (Keyboard::isKeyPressed(Keyboard::Key::Up) && this->selectedDelay > this->selectedDelayMax)
	{
		this->menu[this->selectedMenu].setFillColor(Color::White);
		this->selectedMenu--;
		if (this->selectedMenu < 0)
			this->selectedMenu = 2;
		this->menu[this->selectedMenu].setFillColor(Color::Red);
		this->selectedDelay = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Down) && this->selectedDelay > this->selectedDelayMax)
	{
		this->menu[this->selectedMenu].setFillColor(Color::White);
		this->selectedMenu++;
		if (this->selectedMenu > 2)
			this->selectedMenu = 0;
		this->menu[this->selectedMenu].setFillColor(Color::Red);
		this->selectedDelay = 0;
	}
	//Update Enter Selected Menu
	if (Keyboard::isKeyPressed(Keyboard::Enter) && this->selectedDelay > this->selectedDelayMax)
	{
		if (this->selectedMenu == 0)
		{
			this->GameState = 6;
		}
		else if (this->selectedMenu == 1)
		{
			this->GameState = 4;
		}
		else if (this->selectedMenu == 2)
		{
			this->GameState = 5;
		}
		this->selectedDelay = 0;
	}
	this->selectedDelay++;



}

void Menu::setNewMenuState()
{
	this->GameState = 1;
}

void Menu::render(RenderTarget& target)
{
	target.draw(this->spriteMenuBG);
	for (int i = 0; i < maxItem; i++)
	{
		target.draw(this->menu[i]);
	}
	target.draw(this->nameKMITL);
	target.draw(this->numberKMITL);
}
