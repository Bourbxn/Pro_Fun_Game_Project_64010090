#include "Game.h"

void Game::initWindow()
{
	this->window = new RenderWindow(VideoMode(1600,1200),"Freaking Virus",Style::Close | Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::initPlayer()
{
	this->player = new Player();
}

//con/des
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initPlayer();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete textures
	for (auto &i : this->textures)
	{
		delete i.second;
	}

	//Delete bullets
	for (auto *i : this->bullets)
	{
		delete i;
	}


}

//Functions
void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}

}

void Game::updatePollEvents()
{
	Event ev;
	while (this->window->pollEvent(ev))
	{
		if (ev.Event::type == Event::Closed)
			this->window->close();
		if (ev.Event::KeyPressed && ev.Event::key.code == Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateInput()
{
	//move player
	if (Keyboard::isKeyPressed(Keyboard::Key::Left))
		this->player->move(-1.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::Key::Right))
		this->player->move(1.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::Key::Up))
		this->player->move(0.f, -1.f);
	if (Keyboard::isKeyPressed(Keyboard::Key::Down))
		this->player->move(0.f, 1.f);

	if (sf::Keyboard::isKeyPressed(Keyboard::Key::S))
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"],(this->player->getPos().x)+10, this->player->getPos().y,0.f,0.f,0.f));
	}
}

void Game::updateBullets()
{
	for (auto* bullet : this->bullets)
	{
		bullet->update();
	}
}

void Game::update()
{
	this->updatePollEvents();
	this->updateInput();
	this->updateBullets();
}

void Game::render()
{
	this->window->clear(); 

	//Draw all the stuff
	this->player->render(*this->window);
	for (auto bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	this->window->display();
}
