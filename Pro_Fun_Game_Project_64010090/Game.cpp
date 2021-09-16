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

void Game::initGUI()
{
	//Load font
	if(!this->font.loadFromFile("Fonts/ARCADECLASSIC.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";

	//Init point text
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(30);
	this->pointText.setFillColor(Color::White);
	this->pointText.setOutlineColor(Color::Black);
	this->pointText.setOutlineThickness(3);
	this->pointText.setString("test");
	this->pointText.setPosition(Vector2f(this->window->getSize().x - 140, 10.f));

	//Init GUI
	this->playerHpBar.setSize(Vector2f(300.f, 25.f));

	this->playerHPBarBack = this->playerHpBar;
	this->playerHpBar.setFillColor(Color::Red);
	this->playerHpBar.setPosition(Vector2f(20.f, 20.f));

	this->playerHPBarBack = this->playerHpBar;
	this->playerHPBarBack.setFillColor(Color(25, 25, 25, 200));
}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/map.png"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}

	this->worldBackground.scale(2.5f,2.5f);
	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initSystems()
{
	this->points = 0;
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
	this->initGUI();
	this->initWorld();
	this->initSystems();
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
	//move player and update input init variables
	if (Keyboard::isKeyPressed(Keyboard::Key::Left) && this->player->getPos().x > -50)
	{
		this->player->move(-1.f, 0.f);
		this->bulletDirX = -1;
		this->bulletDirY = 0;
		this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) - 50;
		this->bulletPosY = (this->player->getPos().y) + 175;
		this->bulletRotDeg = -90;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Right) && this->player->getPos().x < 1500)
	{
		this->player->move(1.f, 0.f);
		this->bulletDirX = 1;
		this->bulletDirY = 0;
		this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) + 50;
		this->bulletPosY = (this->player->getPos().y) + 155;
		this->bulletRotDeg = 90;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Up) && this->player->getPos().y > -50) {
		this->player->move(0.f, -1.f);
		this->bulletDirX = 0;
		this->bulletDirY = -1;
		this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) - 10;
		this->bulletPosY = (this->player->getPos().y) + 50;
		this->bulletRotDeg = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Down) && this->player->getPos().y < 1050)
	{
		this->player->move(0.f, 1.f);
		this->bulletDirX = 0;
		this->bulletDirY = 1;
		this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) +10;
		this->bulletPosY = (this->player->getPos().y) + 200;
		this->bulletRotDeg = 180;
	}


	if (sf::Keyboard::isKeyPressed(Keyboard::Key::Space) && this->player->canAttack())
	{
		this->bullets.push_back(
			new Bullet(
			this->textures["BULLET"],
			this->bulletRotDeg, //Set Rotation
			this->bulletPosX, //Set Bullet xy from Player 
			this->bulletPosY,
			this->bulletDirX,
			this->bulletDirY,
			20.f));
	}
}

void Game::updateGUI()
{
	std::stringstream ss;
	ss << "Score  " << this->points;
	this->pointText.setString(ss.str());

	//Update Player GUI
	float hpPercent = static_cast<float>( this->player->getHp())/this->player->getHpMax();
	this->playerHpBar.setSize(Vector2f(300.f* hpPercent,this->playerHpBar.getSize().y));
}

void Game::updateWorld()
{
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
	//Spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x-20.f, -100.f));
		this->
			spawnTimer = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();


		//Bullet culling (top of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//Delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		//Enemy player Collision
		else if (enemy->getBounds().intersects(this->player->getBounds())) 
		{
			//std::cout << "Get Damage";
			this->player->loseHp(20);
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		++counter;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{

		bool enemy_deleted = false;
		for (size_t k = 0; k<this->bullets.size() && enemy_deleted==false;k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points += 1;

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemy_deleted = true;
			}
		}
	}
}

void Game::update()
{
	this->updatePollEvents();
	this->updateInput();
	this->player->update();
	this->updateBullets();
	this->updateEnemies();
	this->updateCombat();
	this->updateGUI();
	this->updateWorld();
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHPBarBack);
	this->window->draw(this->playerHpBar);

}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	this->window->clear(); 

	//Draw world
	this->renderWorld();
	
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

	this->renderGUI();

	this->window->display();
}
