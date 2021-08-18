#include "Game.h"

//Private Functions
void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new RenderWindow(this->videoMode, "Game Project", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(144);
}

void Game::initEnemy()
{
	this->enemy.setPosition(10.f,10.f);
	this->enemy.setSize(Vector2f(100.f, 100.f));
	this->enemy.setScale(Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(Color::Cyan);
	this->enemy.setOutlineColor(Color::Green);
	this->enemy.setOutlineThickness(1.f);
}

//Constructors / Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemy();
}

Game::~Game()
{
	delete this->window;
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->ev.key.code == Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

//Functions
void Game::update()
{
	this->pollEvents();

	//Update Mouse Position
	//Relative to the screen
	//std::cout << "Mouse pos :" << Mouse::getPosition().x << " " << Mouse::getPosition().y << '\n';
	//Relative ti the window
	std::cout << "Mouse pos :" << Mouse::getPosition(*this->window).x << " " << Mouse::getPosition(*this->window).y << '\n';
}

void Game::render()
{
	this->window->clear();

	//Draw Game objects
	this->window->draw(this->enemy);
	this->window->display();
}
