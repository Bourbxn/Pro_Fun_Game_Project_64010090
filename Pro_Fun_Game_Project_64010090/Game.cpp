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

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

//con/des
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initPlayer();
	this->initEnemies();
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

	//Delete bullets
	for (auto* i : this->enemies)
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

	if (sf::Keyboard::isKeyPressed(Keyboard::Key::Space) && this->player->canAttack())
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"],(this->player->getPos().x)+10, (this->player->getPos().y)-60,0.f,-1.f,20.f));
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();
		

		//Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}
		++counter;
	}
}

void Game::updateEnemies()
{
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % 200, rand() % 200));
		this->spawnTimer = 0.f;
	}

	for (auto* enemy : this->enemies)
	{
		enemy->update();
	}
}

void Game::update()
{
	this->updatePollEvents();
	this->updateInput();
	this->player->update();
	this->updateBullets();
	this->updateEnemies();
}

void Game::render()
{
	this->window->clear(); 

	//Draw all the stuff
	this->player->render(*this->window);
	for (auto *bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto *enemy : this->enemies)
	{
		enemy->render(this->window);
	}


	this->window->display();
}
