#include "Game.h"

void Game::initWindow()
{
	this->window = new RenderWindow(VideoMode(1920,1080),"Freaking Virus",Style::Close | Style::Fullscreen);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::initAudio()
{
	//Load Pistol shot sound
	if (!pistolShot.loadFromFile("Audio/pistol_shot_sfx.wav"))
		std::cout << "ERROR::GAME::Failed to load pistol shot audio" << "\n";
		pistolShotSFX.setBuffer(pistolShot);
		pistolShotSFX.setVolume(100);
	if (!alienShot.loadFromFile("Audio/Alien_shot_sfx.wav"))
		std::cout << "ERROR::GAME::Failed to load Alien shot audio" << "\n";
		alienShotSFX.setBuffer(alienShot);
		alienShotSFX.setVolume(40);
	//Combat Sound
	if (!zombieDeath.loadFromFile("Audio/zombie_death_sfx.wav"))
		std::cout << "ERROR::GAME::Failed to load zombie death audio" << "\n";
	zombieDeathSFX.setBuffer(zombieDeath);
	zombieDeathSFX.setVolume(80);
	if (!bourbxnHurt.loadFromFile("Audio/bourbxn_hurt_sfx.wav"))
		std::cout << "ERROR::GAME::Failed to load Bourbxn hurt audio" << "\n";
	bourbxnHurtSFX.setBuffer(bourbxnHurt);
	bourbxnHurtSFX.setVolume(100);
	//Item & Gun Sound
	if (!gunDropBuff.loadFromFile("Audio/Gun_drop_sfx.wav"))
		std::cout << "ERROR::GAME::Failed to load Gun drop audio" << "\n";
	gunDropSFX.setBuffer(gunDropBuff);
	gunDropSFX.setVolume(100);
	if (!gunCorrectBuff.loadFromFile("Audio/Gun_correct_sfx.wav"))
		std::cout << "ERROR::GAME::Failed to load Gun drop audio" << "\n";
	gunCorrectSFX.setBuffer(gunCorrectBuff);
	gunCorrectSFX.setVolume(100);
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
	this->pointText.setPosition(Vector2f(this->window->getSize().x - 200, 10.f));

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

	this->worldBackground.scale(3.f,3.f);
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

void Game::initGun()
{
	this->gun = new Gun();
	this->gunDropState = false;
	this->gunRandomTypeState = true;
	this->gunRandomState = true;
	this->gunType = 0;
	this->playerAttackCoolDownMax = 15.f;
	this->gunCorrectPlay = false;
	this->gunDropPlay = true;
	this->deltaTime = 0;
}

void Game::initEnemies()
{
	this->spawnTimerMaxUpDown = 50.f;
	this->spawnTimerUpDown = this->spawnTimerMaxUpDown;
	this->spawnTimerMaxLeftRight = 50.f;
	this->spawnTimerLeftRight = this->spawnTimerMaxLeftRight;
	this->spawnTimerRate = 0.1f;
}

//con/des
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initAudio();
	this->initGUI();
	this->initWorld();
	this->initSystems();
	this->initPlayer();
	this->initGun();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	delete this->gun;
	
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
	for (auto* i : this->enemiesUpDown)
	{
		delete i;
	}

	for (auto* i : this->enemiesLeftRight)
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
	if (Keyboard::isKeyPressed(Keyboard::Key::Left) && this->player->getPos().x > 0)
	{
		this->player->move(-1.f, 0.f);
		//Set each gun Type Direction "Left"
		//Pistol & Uzi
		if (this->gunType == 0 || this->gunType == 1)
		{
			this->gun->updatePosSprite(this->player->getPos().x - 10.f, this->player->getPos().y + 75.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) - 22;
			this->bulletPosY = (this->player->getPos().y) + 159;
		}
		//P90
		else if (this->gunType == 2)
		{
			this->gun->updatePosSprite(this->player->getPos().x - 50.f, this->player->getPos().y + 52.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) - 60;
			this->bulletPosY = (this->player->getPos().y) + 160;
		}
		//AK47
		else if (this->gunType == 3)
		{

			this->gun->updatePosSprite(this->player->getPos().x - 55.f, this->player->getPos().y + 52.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) - 75;
			this->bulletPosY = (this->player->getPos().y) + 160;
		}
		//M4A1
		else if (this->gunType == 4)
		{

			this->gun->updatePosSprite(this->player->getPos().x - 55.f, this->player->getPos().y + 52.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) - 75;
			this->bulletPosY = (this->player->getPos().y) + 159;
		}
		//Saxophone
		else if (this->gunType == 5)
		{

			this->gun->updatePosSprite(this->player->getPos().x - 55.f, this->player->getPos().y + 52.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) - 75;
			this->bulletPosY = (this->player->getPos().y) + 160;
		}
		//Alien
		else if (this->gunType == 6)
		{

			this->gun->updatePosSprite(this->player->getPos().x - 48.f, this->player->getPos().y + 52.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) - 128;
			this->bulletPosY = (this->player->getPos().y) + 158;
		}
		//Capricorn
		else if (this->gunType == 7)
		{

			this->gun->updatePosSprite(this->player->getPos().x - 48.f, this->player->getPos().y + 52.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) - 75;
			this->bulletPosY = (this->player->getPos().y) + 160;
		}
		this->bulletDirX = -1;
		this->bulletDirY = 0;
		this->bulletRotDeg = -90;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Right) && this->player->getPos().x < this->window->getSize().x - 100)
	{
		this->player->move(1.f, 0.f);
		//Set each gun Type Direction "Right"
		//Pistol & Uzi
		if (this->gunType == 0 || this->gunType == 1)
		{
			this->gun->updatePosSprite(this->player->getPos().x + 80.f, this->player->getPos().y + 75.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) + 30;
			this->bulletPosY = (this->player->getPos().y) + 145;
		}
		//P90
		else if (this->gunType == 2)
		{
			this->gun->updatePosSprite(this->player->getPos().x + 72.f, this->player->getPos().y + 48.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) + 65;
			this->bulletPosY = (this->player->getPos().y) + 149;
		}
		//AK47
		else if (this->gunType == 3)
		{
			this->gun->updatePosSprite(this->player->getPos().x + 77.f, this->player->getPos().y + 54.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) + 80;
			this->bulletPosY = (this->player->getPos().y) + 150;
		}
		//M4A1
		else if (this->gunType == 4)
		{
			this->gun->updatePosSprite(this->player->getPos().x + 77.f, this->player->getPos().y + 52.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) + 80;
			this->bulletPosY = (this->player->getPos().y) + 147;
		}
		//Saxophone
		else if (this->gunType == 5)
		{
			this->gun->updatePosSprite(this->player->getPos().x + 77.f, this->player->getPos().y + 53.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) + 80;
			this->bulletPosY = (this->player->getPos().y) + 150;
		}
		//Alien
		else if (this->gunType == 6)
		{
			this->gun->updatePosSprite(this->player->getPos().x + 70.f, this->player->getPos().y + 51.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) + 133;
			this->bulletPosY = (this->player->getPos().y) + 145;
		}
		//Capricon
		else if (this->gunType == 7)
		{
			this->gun->updatePosSprite(this->player->getPos().x + 70.f, this->player->getPos().y + 51.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) + 80;
			this->bulletPosY = (this->player->getPos().y) + 150;
		}
		this->bulletDirX = 1;
		this->bulletDirY = 0;
		this->bulletRotDeg = 90;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Up) && this->player->getPos().y > 0) {
		this->player->move(0.f, -1.f);
		//Set each gun Type Direction "Up"
		//Pistol & Uzi
		if (this->gunType == 0 || this->gunType == 1)
		{
			this->gun->updatePosSprite(this->player->getPos().x, this->player->getPos().y);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f);
			this->bulletPosY = (this->player->getPos().y) + 100;
		}
		//P90
		else if (this->gunType == 2)
		{
			this->gun->updatePosSprite(this->player->getPos().x  , this->player->getPos().y);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f);
			this->bulletPosY = (this->player->getPos().y) + 100;
		}
		//AK47
		else if (this->gunType == 3)
		{
			this->gun->updatePosSprite(this->player->getPos().x, this->player->getPos().y);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f);
			this->bulletPosY = (this->player->getPos().y) + 100;
		}
		//M4A1
		else if (this->gunType == 4)
		{
			this->gun->updatePosSprite(this->player->getPos().x, this->player->getPos().y);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f);
			this->bulletPosY = (this->player->getPos().y) + 100;
		}
		//Saxophone
		else if (this->gunType == 5)
		{
			this->gun->updatePosSprite(this->player->getPos().x, this->player->getPos().y);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f);
			this->bulletPosY = (this->player->getPos().y) + 100;
		}
		//Alien
		else if (this->gunType == 6)
		{
			this->gun->updatePosSprite(this->player->getPos().x, this->player->getPos().y);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f);
			this->bulletPosY = (this->player->getPos().y) + 40;
		}
		//Capricorn
		else if (this->gunType == 7)
		{
			this->gun->updatePosSprite(this->player->getPos().x, this->player->getPos().y);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f);
			this->bulletPosY = (this->player->getPos().y) + 100;
		}
		this->bulletDirX = 0;
		this->bulletDirY = -1;
		this->bulletRotDeg = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Down) && this->player->getPos().y < window->getSize().y-140)
	{
		this->player->move(0.f, 1.f);
		//Set each gun Type Direction "Down"
		//Pistol & Uzi
		if (this->gunType == 0 || this->gunType == 1)
		{
			this->gun->updatePosSprite(this->player->getPos().x + 34.f, this->player->getPos().y + 85.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) + 10;
			this->bulletPosY = (this->player->getPos().y) + 150;
		}
		//P90
		else if (this->gunType == 2)
		{
			this->gun->updatePosSprite(this->player->getPos().x + 12.f, this->player->getPos().y + 72.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) + 10;
			this->bulletPosY = (this->player->getPos().y) + 180;
		}
		//AK47
		else if (this->gunType == 3)
		{
			this->gun->updatePosSprite(this->player->getPos().x + 13.f, this->player->getPos().y + 72.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) + 10;
			this->bulletPosY = (this->player->getPos().y) + 180;
		}
		//M4A1
		else if (this->gunType == 4)
		{
			this->gun->updatePosSprite(this->player->getPos().x + 12.f, this->player->getPos().y + 72.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) + 9;
			this->bulletPosY = (this->player->getPos().y) + 187;
		}
		//Saxophone
		else if (this->gunType == 5)
		{
			this->gun->updatePosSprite(this->player->getPos().x + 12.f, this->player->getPos().y + 72.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) + 10;
			this->bulletPosY = (this->player->getPos().y) + 180;
		}
		//Alien
		else if (this->gunType == 6)
		{
			this->gun->updatePosSprite(this->player->getPos().x + 12.f, this->player->getPos().y + 72.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) + 10;
			this->bulletPosY = (this->player->getPos().y) + 180;
		}
		//Capricorn
		else if (this->gunType == 7)
		{
			this->gun->updatePosSprite(this->player->getPos().x + 12.f, this->player->getPos().y + 72.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) + 10;
			this->bulletPosY = (this->player->getPos().y) + 180;
		}
		this->bulletDirX = 0;
		this->bulletDirY = 1;
		this->bulletRotDeg = 180;
	}


	if (sf::Keyboard::isKeyPressed(Keyboard::Key::Space) && this->player->canAttack())
	{
		//Set sound for each gun Type
		if (this->gunType == 0)
		{
			this->pistolShotSFX.play();
		}
		else if (this->gunType == 1)
		{
			this->pistolShotSFX.play();
		}
		else if (this->gunType == 2)
		{
			this->pistolShotSFX.play();
		}
		else if (this->gunType == 3)
		{
			this->pistolShotSFX.play();
		}
		else if (this->gunType == 4)
		{
			this->pistolShotSFX.play();
		}
		else if (this->gunType == 5)
		{
			this->pistolShotSFX.play();
		}
		else if (this->gunType == 6)
		{
			this->alienShotSFX.play();
		}
		else if (this->gunType == 7)
		{
			this->pistolShotSFX.play();
		}
		this->bullets.push_back(
			new Bullet(
			this->textures["BULLET"],
			this->bulletRotDeg, //Set Rotation
			this->bulletPosX, //Set Bullet xy from Player 
			this->bulletPosY,
			this->bulletDirX,
			this->bulletDirY,
			50.f));
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

void Game::updateTextures()
{
	if (this->gunType == 0)
	{
		this->textures["BULLET"] = new Texture();
		this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
	}
	else if (this->gunType == 1)
	{
		this->textures["BULLET"] = new Texture();
		this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
	}
	else if (this->gunType == 2)
	{
		this->textures["BULLET"] = new Texture();
		this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
	}
	else if (this->gunType == 3)
	{
		this->textures["BULLET"] = new Texture();
		this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
	}
	else if (this->gunType == 4)
	{
		this->textures["BULLET"] = new Texture();
		this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
	}
	else if (this->gunType == 5)
	{
		this->textures["BULLET"] = new Texture();
		this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
	}
	else if (this->gunType == 6)
	{
		this->textures["BULLET"] = new Texture();
		this->textures["BULLET"]->loadFromFile("Textures/Alien_bullet.png");
	}
	else if (this->gunType == 7)
	{
		this->textures["BULLET"] = new Texture();
		this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
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

void Game::updateEnemiesUpDown()
{
	//Spawning
	this->spawnTimerUpDown += this->spawnTimerRate;
	if (this->spawnTimerUpDown >= this->spawnTimerMaxUpDown)
	{
		this->enemiesUpDown.push_back(new Enemy(rand() % this->window->getSize().x-20.f, -100.f));							//Down
		this->enemiesUpDown.push_back(new Enemy(rand() % this->window->getSize().x - 20.f,this->window->getSize().y));		//Up
		this->spawnTimerUpDown = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto* enemy : this->enemiesUpDown)
	{
		enemy->updateEnemyMoveUpDown();


		//Bullet culling (top of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//Delete enemy
			delete this->enemiesUpDown.at(counter);
			this->enemiesUpDown.erase(this->enemiesUpDown.begin() + counter);
		}
		//Enemy player Collision
		else if (enemy->getBounds().intersects(this->player->getBounds())) 
		{
			bourbxnHurtSFX.play();
			//std::cout << "Get Damage";
			this->player->loseHp(20);
			delete this->enemiesUpDown.at(counter);
			this->enemiesUpDown.erase(this->enemiesUpDown.begin() + counter);
		}
		++counter;
	}
}

void Game::updateEnemiesLeftRight()
{
	//Spawning
	this->spawnTimerLeftRight += this->spawnTimerRate;
	if (this->spawnTimerLeftRight >= this->spawnTimerMaxLeftRight)
	{
		this->enemiesLeftRight.push_back(new Enemy(0.f, rand() % this->window->getSize().y-20));									//Right
		this->enemiesLeftRight.push_back(new Enemy(this->window->getSize().x, rand() % this->window->getSize().y-20));			//Left
		this->spawnTimerLeftRight = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto* enemy : this->enemiesLeftRight)
	{
		enemy->updateEnemyMoveLeftRight();


		//Bullet culling (top of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//Delete enemy
			delete this->enemiesLeftRight.at(counter);
			this->enemiesLeftRight.erase(this->enemiesLeftRight.begin() + counter);
		}
		//Enemy player Collision
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			bourbxnHurtSFX.play();
			//std::cout << "Get Damage";
			this->player->loseHp(20);
			delete this->enemiesLeftRight.at(counter);
			this->enemiesLeftRight.erase(this->enemiesLeftRight.begin() + counter);
		}
		++counter;
	}
}

void Game::updateEnemiesPower()
{
	this->time = clock.getElapsedTime().asSeconds();
	if (this->time > 5)
	{
		this->spawnTimerRate += 0.01;
		clock.restart();
	}
}

void Game::updateCombatUpDown()
{
	for (int i = 0; i < this->enemiesUpDown.size(); ++i)
	{

		bool enemy_deleted = false;
		for (size_t k = 0; k<this->bullets.size() && enemy_deleted==false;k++)
		{
			if (this->enemiesUpDown[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->zombieDeathSFX.play();

				//Points in each gun type
				if (this->gunType == 0 || this->gunType == 1 || this->gunType == 2 || this->gunType == 3 || this->gunType == 4)
				{
					this->points += 1;
				}
				else if (this->gunType == 5)
				{
					this->points += 2;
				}
				else if (this->gunType == 6)
				{
					this->points += 2;
				}
				else if (this->gunType == 7)
				{
					this->points += 10;
				}

				delete this->enemiesUpDown[i];
				this->enemiesUpDown.erase(this->enemiesUpDown.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemy_deleted = true;
			}
		}
	}
}

void Game::updateCombatLeftRight()
{
	for (int i = 0; i < this->enemiesLeftRight.size(); ++i)
	{

		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			if (this->enemiesLeftRight[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->zombieDeathSFX.play();

				//Points in each gun type
				if (this->gunType == 0 || this->gunType == 1 || this->gunType == 2 || this->gunType == 3 || this->gunType == 4)
				{
					this->points += 1;
				}
				else if (this->gunType == 5)
				{
					this->points += 2;
				}
				else if (this->gunType == 6)
				{
					this->points += 2;
				}
				else if (this->gunType == 7)
				{
					this->points += 10;
				}

				delete this->enemiesLeftRight[i];
				this->enemiesLeftRight.erase(this->enemiesLeftRight.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemy_deleted = true;
			}
		}
	}
}

void Game::updateGunDrop()
{
	//Random Gun
	if (this->points % 50 == 0 && this->points != 0 && this->gunCorrect == false && this->gunRandomTypeState==true)
	{
		this->gunDropPercent = rand() % 99 + 1;
		std::cout << gunDropPercent << std::endl;
		if (this->gunDropPercent >= 1 && this->gunDropPercent <= 20)
		{
			this->gunDropItem = 1;
		}
		else if (this->gunDropPercent > 21 && this->gunDropPercent <= 40)
		{
			this->gunDropItem = 2;
		}
		else if (this->gunDropPercent > 41 && this->gunDropPercent <= 60)
		{
			this->gunDropItem = 3;
		}
		else if (this->gunDropPercent > 61 && this->gunDropPercent <= 80)
		{
			this->gunDropItem = 4;
		}
		else if (this->gunDropPercent > 81 && this->gunDropPercent <= 90)
		{
			this->gunDropItem = 5;
		}
		else if (this->gunDropPercent > 90 && this->gunDropPercent <= 96)
		{
			this->gunDropItem = 6;
		}
		else if (this->gunDropPercent > 96 && this->gunDropPercent <= 100)
		{
			this->gunDropItem = 7;
		}
		this->gunDropState = true;
		this->gunRandomState = false;
		this->gunRandomTypeState = false;
	}
	else if (this->points % 50 != 0 && this->gunCorrect == true)
	{
		this->gunCorrect = false;
	}

	//Random Position
	if (this->gunRandomState == true)
	{
		this->gunDropPos_x = rand() % 1201 + 300;		
		this->gunDropPos_y = rand() % 401 + 300;			
	}
	this->gunRandomState = false;

	//Gun Drop
	if (this->gunDropItem == 1)
	{
		if (!this->textureGunDrop.loadFromFile("Textures/Uzi_rare_01_drop.png"))
		{
			std::cout << "ERROR::GUN::INITTEXTURE::Could not load textures file." << "\n";
		}
		this->spriteGunDrop.setTexture(this->textureGunDrop);
		this->spriteGunDrop.setScale(1.25f, 1.25f);
		this->spriteGunDrop.setPosition(this->gunDropPos_x, this->gunDropPos_y);
		
	}
	else if (this->gunDropItem == 2)
	{
		if (!this->textureGunDrop.loadFromFile("Textures/P90_mythical_02_Drop.png"))
		{
			std::cout << "ERROR::GUN::INITTEXTURE::Could not load textures file." << "\n";
		}
		this->spriteGunDrop.setTexture(this->textureGunDrop);
		this->spriteGunDrop.setScale(1.25f, 1.25f);
		this->spriteGunDrop.setPosition(this->gunDropPos_x, this->gunDropPos_y);
	}
	else if (this->gunDropItem == 3)
	{
		if (!this->textureGunDrop.loadFromFile("Textures/AK47_legendary_03_Drop.png"))
		{
			std::cout << "ERROR::GUN::INITTEXTURE::Could not load textures file." << "\n";
		}
		this->spriteGunDrop.setTexture(this->textureGunDrop);
		this->spriteGunDrop.setScale(1.25f, 1.25f);
		this->spriteGunDrop.setPosition(this->gunDropPos_x, this->gunDropPos_y);
	}
	else if (this->gunDropItem == 4)
	{
		if (!this->textureGunDrop.loadFromFile("Textures/M4A1_ancient_04.png"))
		{
			std::cout << "ERROR::GUN::INITTEXTURE::Could not load textures file." << "\n";
		}
		this->spriteGunDrop.setTexture(this->textureGunDrop);
		this->spriteGunDrop.setScale(1.25f, 1.25f);
		this->spriteGunDrop.setPosition(this->gunDropPos_x, this->gunDropPos_y);
	}
	else if (this->gunDropItem == 5)
	{
		if (!this->textureGunDrop.loadFromFile("Textures/Saxophone_ExceedinglyRare_05_Drop.png"))
		{
			std::cout << "ERROR::GUN::INITTEXTURE::Could not load textures file." << "\n";
		}
		this->spriteGunDrop.setTexture(this->textureGunDrop);
		this->spriteGunDrop.setScale(1.25f, 1.25f);
		this->spriteGunDrop.setPosition(this->gunDropPos_x, this->gunDropPos_y);
	}
	else if (this->gunDropItem == 6)
	{
		if (!this->textureGunDrop.loadFromFile("Textures/Alien_immortal_06_Drop.png"))
		{
			std::cout << "ERROR::GUN::INITTEXTURE::Could not load textures file." << "\n";
		}
		this->spriteGunDrop.setTexture(this->textureGunDrop);
		this->spriteGunDrop.setScale(1.25f, 1.25f);
		this->spriteGunDrop.setPosition(this->gunDropPos_x, this->gunDropPos_y);
	}
	else if (this->gunDropItem == 7)
	{
		if (!this->textureGunDrop.loadFromFile("Textures/Capricorn_godmode_07_Drop.png"))
		{
			std::cout << "ERROR::GUN::INITTEXTURE::Could not load textures file." << "\n";
		}
		this->spriteGunDrop.setTexture(this->textureGunDrop);
		this->spriteGunDrop.setScale(1.25f, 1.25f);
		this->spriteGunDrop.setPosition(this->gunDropPos_x, this->gunDropPos_y);
	}

	//Collect Gun
	if (this->spriteGunDrop.getGlobalBounds().intersects(this->player->getBounds()) && this->gunDropState==true)
	{
		this->gunType = this->gunDropItem;
		this->gunRandomTypeState = true;
		this->gunRandomState = true;
		this->gunDropState = false;
		this->gunCorrect = true;
		this->deltaTime = 0;
	}
	else if(!this->spriteGunDrop.getGlobalBounds().intersects(this->player->getBounds()) && this->gunDropState==true)
	{
		this->deltaTime += 1;
		if (this->deltaTime == 600)
		{
			this->gunRandomTypeState = true;
			this->gunRandomState = true;
			this->gunDropState = false;
			this->gunCorrect = true;
			this->deltaTime = 0;
		}
		//std::cout << deltaTime << std::endl;
	}
}

void Game::updateGunType()
{
	if (this->gunType == 1)
	{
		this->playerAttackCoolDownMax = 10.f;
	}
	else if (this->gunType == 2)
	{
		this->playerAttackCoolDownMax = 7.5f;
	}
	else if (this->gunType == 3)
	{
		this->playerAttackCoolDownMax = 6.5f;
	}
	else if (this->gunType == 4)
	{
		this->playerAttackCoolDownMax = 5.f;
	}
	else if (this->gunType == 5)
	{
		this->playerAttackCoolDownMax = 5.f;
	}
	else if (this->gunType == 6)
	{
		this->playerAttackCoolDownMax = 2.f;
	}
	else if (this->gunType == 7)
	{
		this->playerAttackCoolDownMax = 5.f;
	}
}
	
void Game::update()
{
	this->updatePollEvents();
	this->updateInput();
	this->player->updateAttackStatus(this->playerAttackCoolDownMax);
	this->player->update();
	this->gun->updateSpriteTextures(this->gunType);
	this->updateGunType();
	this->gun->update();
	this->updateTextures();
	this->updateBullets();
	this->updateEnemiesUpDown();
	this->updateEnemiesLeftRight();
	this->updateEnemiesPower();
	this->updateCombatUpDown();
	this->updateCombatLeftRight();
	this->updateGunDrop();
	this->updateGUI();
	this->updateWorld();
}

void Game::renderGunDrop()
{
	if (this->gunDropState == true)
	{
		this->window->draw(this->spriteGunDrop);
	}
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
	this->gun->render(*this->window);
	this->renderGunDrop();
	for (auto *bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto *enemy : this->enemiesUpDown)
	{
		enemy->render(this->window);
	}

	for (auto* enemy : this->enemiesLeftRight)
	{
		enemy->render(this->window);
	}

	this->renderGUI();

	this->window->display();
}
