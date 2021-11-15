#include "Game.h"

void Game::initGameState()
{
	this->gameRestart = false;
	this->GameState = 1;
	this->nameInput = false;
	this->deltaTime6to2 = 0;
}

void Game::initWindow()
{
	this->window = new RenderWindow(VideoMode(1920,1080),"Freaking Virus",Style::Close | Style::Default);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initMenu()
{
	this->menu = new Menu();
}

void Game::initTextures()
{
	this->textures["BULLET"] = new Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::initTextboxName()
{
	this->textboxName = new Textbox(true);
	this->textboxName->setFont(this->font);
	this->textboxName->setPosition({
		1920/2 - 300,
		1080/2 - 80 });
	this->textboxName->setOutline(5, Color::Black);
	this->textboxName->setLimit(true, 8);
}

void Game::initRanking()
{
	this->topic = new Ranking(
		this->window->getSize().x / 2 - 250,
		25, 
		"Ranking",
		&this->font);
	
	FILE* rankingFile;
	char tempRank[255];
	int scoreRank[10];
	std::string nameRank[10];
	std::vector <std::pair<int, std::string>> userScore;
	rankingFile = fopen("Score/Ranking.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(rankingFile,"%s", &tempRank);
		std::cout << tempRank << std::endl;
		nameRank[i] = tempRank;
		fscanf(rankingFile,"%d", &scoreRank[i]);
		userScore.push_back(std::make_pair(scoreRank[i], nameRank[i]));
		//cout << temp << " " << score;
	}
	nameRank[5] = "TEST";
	scoreRank[5] = 1234;
	userScore.push_back(std::make_pair(scoreRank[5], nameRank[5]));
	sort(userScore.begin(), userScore.end());
	fclose(rankingFile);

	fopen("Score / Ranking.txt", "w");
	for (int i = 5; i >= 1; i--)
	{
		strcpy(tempRank, userScore[i].second.c_str());
		fprintf(rankingFile, "%s %d\n", tempRank, userScore[i].first);
	}
	fclose(rankingFile);
	int posRankingNameX = 550;
	int posRankingScoreX = 1150;
	int PosRankingY = 650;

	for (int i = 0; i < 5; i++)
	{
		this->rankName[i] = new Ranking(posRankingNameX, PosRankingY - (i * 100), userScore[i].second, &this->font);
		this->rankScore[i] = new Ranking(posRankingScoreX, PosRankingY - (i * 100), std::to_string(userScore[i].first), &this->font);
	}
	/*this->rankFirstScore = new Ranking(10, 40, userScore[0].second, &this->font);
	this->rankFirstName = new Ranking(100, 40, std::to_string(userScore[5].first), &this->font);*/
	
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
		alienShotSFX.setVolume(30);
	if (!saxophoneShot.loadFromFile("Audio/Saxophone_shot_sfx.wav"))
		std::cout << "ERROR::GAME::Failed to load Saxophone shot audio" << "\n";
		saxophoneShotSFX.setBuffer(saxophoneShot);
		saxophoneShotSFX.setVolume(20);
	if (!capricornShot.loadFromFile("Audio/Capricorn_shot_sfx.wav"))
		std::cout << "ERROR::GAME::Failed to load Saxophone shot audio" << "\n";
		capricornShotSFX.setBuffer(capricornShot);
		capricornShotSFX.setVolume(20);
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

	//HP Bar
	this->playerHpBar.setSize(Vector2f(300.f, 25.f));

	this->playerHPBarBack = this->playerHpBar;
	this->playerHpBar.setFillColor(Color::Green);
	this->playerHpBar.setPosition(Vector2f(20.f, 20.f));
	//this->playerHpBar.setOutlineThickness(3.f);
	//this->playerHpBar.setOutlineColor(Color::Black);

	this->playerHPBarBack = this->playerHpBar;
	this->playerHPBarBack.setFillColor(Color(25, 25, 25, 200));

	//Game Over
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(150);
	this->gameOverText.setFillColor(Color::White);
	this->gameOverText.setOutlineColor(Color::Black);
	this->gameOverText.setOutlineThickness(10);
	this->gameOverText.setString("Game Over");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	//Game Over Explain
	this->gameOverExplainPosY = 940.f;
	this->gameOverExFontSize = 50;
	this->gameOverExThickness = 5;
	this->gameOverExStartPos = 180.f;

	this->gameOverExplain1.setFont(this->font);
	this->gameOverExplain1.setCharacterSize(this->gameOverExFontSize);
	this->gameOverExplain1.setFillColor(Color::Color(169,169,169));
	this->gameOverExplain1.setOutlineColor(Color::Black);
	this->gameOverExplain1.setOutlineThickness(this->gameOverExThickness);
	this->gameOverExplain1.setString("press  Enter  for  play  again  or  press  ESC  for  exit  to  main  menu");
	this->gameOverExplain1.setPosition(this->gameOverExStartPos,this->gameOverExplainPosY);
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
	this->pointsDropGun = 20;
	this->enemiesLevel = 1;
}

void Game::initVaccine()
{
	this->vaccine = new Vaccine();
	this->vaccineDropState = false;
	this->infectPlayer = false;
	this->infectedType = 0;
	this->vaccineRandomRate = false;
	this->vaccineRandomPos = false;
}

void Game::initEnemies()
{
	this->spawnTimerMaxUpDown = 50.f;
	this->spawnTimerUpDown = this->spawnTimerMaxUpDown;
	this->spawnTimerMaxLeftRight = 50.f;
	this->spawnTimerLeftRight = this->spawnTimerMaxLeftRight;
	this->spawnTimerRate = 0.1f;
	this->enemySpeedDirPlus = 1.f;
	this->enemySpeedDirMinus = -1.f;
}

//con/des
Game::Game()
{
	this->initGameState();
	this->initWindow();
	this->initMenu();
	this->initTextboxName();
	this->initRanking();
	this->initTextures();
	this->initAudio();
	this->initGUI();
	this->initWorld();
	this->initSystems();
	this->initPlayer();
	this->initGun();
	this->initVaccine();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	delete this->gun;
	delete this->vaccine;
	delete this->textboxName;
	
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

void Game::updateVaccineDrop()
{
	std::cout << "You have been kill enemy" << std::endl;
	//Random Rate / Pos
	if (this->vaccineRandomRate == true && this->vaccineDropState==false)
	{
		this->vaccinePercentDrop = rand() % 99 + 1;
		this->vaccineDropPos_x = rand() % 1201 + 300;
		this->vaccineDropPos_y = rand() % 401 + 300;
		this->vaccineDropState = true;
	}
	this->vaccineRandomRate = false;

	std::cout << this->vaccinePercentDrop << std::endl;
	std::cout << this->vaccineDropPos_x << std::endl;
	std::cout << this->vaccineDropPos_y << std::endl;


	//Random Drop Rate
	if (this->vaccinePercentDrop >= 1 && this->vaccinePercentDrop <= 10)
	{
		this->vaccineTypeDrop = 1;
	}
	else if (this->vaccinePercentDrop > 5 && this->vaccinePercentDrop <= 50)
	{
		this->vaccineTypeDrop = 0;
	}
	else if (this->vaccinePercentDrop > 50 && this->vaccinePercentDrop <= 53)
	{
		this->vaccineTypeDrop = 2;
	}
	else if (this->vaccinePercentDrop > 53 && this->vaccinePercentDrop <= 97)
	{
		this->vaccineTypeDrop = 0;
	}
	else if (this->vaccinePercentDrop > 97 && this->vaccinePercentDrop <= 100)
	{
		this->vaccineTypeDrop = 3;
	}

	//Drop Vaccine
	if (this->vaccineTypeDrop == 0)
	{
		this->vaccineRandomRate = true;
		this->vaccineDropState = false;
	}
	else if (this->vaccineTypeDrop == 1)
	{
		if (!this->textureVaccineDrop.loadFromFile("Textures/vaccine_01_Drop.png"))
		{
			std::cout << "ERROR::VACCINE::INITTEXTURE::Could not load textures file." << "\n";
		}
		this->spriteVaccineDrop.setTexture(this->textureVaccineDrop);
		this->spriteVaccineDrop.setScale(1.f, 1.f);
		this->spriteVaccineDrop.setPosition(this->vaccineDropPos_x, this->vaccineDropPos_y);
	}
	else if (this->vaccineTypeDrop == 2)
	{
		if (!this->textureVaccineDrop.loadFromFile("Textures/vaccine_02_Drop.png"))
		{
			std::cout << "ERROR::VACCINE::INITTEXTURE::Could not load textures file." << "\n";
		}
		this->spriteVaccineDrop.setTexture(this->textureVaccineDrop);
		this->spriteVaccineDrop.setScale(1.f, 1.f);
		this->spriteVaccineDrop.setPosition(this->vaccineDropPos_x, this->vaccineDropPos_y);
	}
	else if (this->vaccineTypeDrop == 3)
	{
		if (!this->textureVaccineDrop.loadFromFile("Textures/vaccine_03_Drop.png"))
		{
			std::cout << "ERROR::VACCINE::INITTEXTURE::Could not load textures file." << "\n";
		}
		this->spriteVaccineDrop.setTexture(this->textureVaccineDrop);
		this->spriteVaccineDrop.setScale(1.f, 1.f);
		this->spriteVaccineDrop.setPosition(this->vaccineDropPos_x, this->vaccineDropPos_y);
	}

	
}

//Functions
void Game::run()
{
	while (this->window->isOpen())
	{
		std::cout << this->GameState << std::endl;
		//std::cout << this->deltaTime6to2 << std::endl;

		//MAIN STATE
		//Menu
		if (this->GameState == 1)
		{
			this->updateRestartEnemies();
			this->updateMenu();
			this->renderMenu();
			this->updatePollEvents();
		}
		
		//Game Play
		else if (this->GameState == 2)
		{
			//this->updateRestartGame();
			this->updatePollEvents();
			this->updateGameState();
			this->update();
			this->render();
		}
		//Game Over
		else if (this->GameState == 3)
		{
			this->updateRestartEnemies();
			this->updateRestartGame();
			this->updateGameOver();
			this->renderGameOver();
		}
		//Ranking
		else if (this->GameState == 4)
		{
			this->updatePollEvents();
			this->renderRanking();
		}
		//Exit
		else if (this->GameState == 5)
		{
			this->window->close();
		}

		//SUB_STATE
		//Enter Name
		
		else if (this->GameState == 6)
		{
			this->updateDeltaTime6to2();
			this->updatePollEventsInputName();
			this->updateSelectNameInput();
			this->renderInputName();
		}
		
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
			this->GameState = 1;
	}
}

void Game::updatePollEventsInputName()
{
	Event ev;
	while (this->window->pollEvent(ev))
	{
		switch (ev.type) {

		case Event::TextEntered:
			this->textboxName->typedOn(ev);
		}
	}
}

void Game::updateGameState()
{
	//Update Game Over
	if (this->player->getHp() <= 0)
	{
		
		this->GameState = 3;
		this->initSystems();
		this->initPlayer();
		this->initGun();
		this->initVaccine();
		this->initEnemies();
		//Delete enemies
	}
}

void Game::updateDeltaTime6to2()
{
	this->deltaTime6to2++;
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
			this->bulletPosY = (this->player->getPos().y) + 190;
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
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) - 130;
			this->bulletPosY = (this->player->getPos().y) + 180;
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
			this->bulletPosY = (this->player->getPos().y) + 110;
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
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) + 135;
			this->bulletPosY = (this->player->getPos().y) + 135;
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
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) - 34;
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
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f)-18;
			this->bulletPosY = (this->player->getPos().y) + 40;
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
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) + 42;
			this->bulletPosY = (this->player->getPos().y) + 200;
		}
		//Alien
		else if (this->gunType == 6)
		{
			this->gun->updatePosSprite(this->player->getPos().x + 12.f, this->player->getPos().y + 72.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) + 10;
			this->bulletPosY = (this->player->getPos().y) + 242;
		}
		//Capricorn
		else if (this->gunType == 7)
		{
			this->gun->updatePosSprite(this->player->getPos().x + 12.f, this->player->getPos().y + 72.f);
			this->bulletPosX = (this->player->getPos().x) + (this->player->getBounds().width / 2.f) + 26;
			this->bulletPosY = (this->player->getPos().y) + 250;
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
			this->saxophoneShotSFX.play();
		}
		else if (this->gunType == 6)
		{
			this->alienShotSFX.play();
		}
		else if (this->gunType == 7)
		{
			this->capricornShotSFX.play();
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
	if (this->infectedType == 2)
	{
		this->playerHpBar.setFillColor(Color::Color(191,155,48));
	}
	else if (this->infectedType == 0)
	{
		this->playerHpBar.setFillColor(Color::Color(89,197,61));
	}
	else if(this->infectedType == 1)
	{
		this->playerHpBar.setFillColor(Color::Color(238,38,38));
	}
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
		this->textures["BULLET"]->loadFromFile("Textures/Saxophone_bullet.png");
	}
	else if (this->gunType == 6)
	{
		this->textures["BULLET"] = new Texture();
		this->textures["BULLET"]->loadFromFile("Textures/Alien_bullet.png");
	}
	else if (this->gunType == 7)
	{
		this->textures["BULLET"] = new Texture();
		this->textures["BULLET"]->loadFromFile("Textures/Capricorn_bullet.png");
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
		this->enemiesUpDown.push_back(new Enemy(
			rand() % this->window->getSize().x-20.f, -100.f,
			this->enemySpeedDirMinus,
			this->enemySpeedDirPlus));							//Down
		this->enemiesUpDown.push_back(new Enemy(
			rand() % this->window->getSize().x - 20.f,
			this->window->getSize().y,
			this->enemySpeedDirMinus,
			this->enemySpeedDirPlus));							//Up
		this->spawnTimerUpDown = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto* enemy : this->enemiesUpDown)
	{
		enemy->updateEnemyMoveUpDown();


		//Bullet culling (top of screen)
		if (enemy->getBounds().top > this->window->getSize().y )
		{
			//Delete enemy
			delete this->enemiesUpDown.at(counter);
			this->enemiesUpDown.erase(this->enemiesUpDown.begin() + counter);
		}
		if (enemy->getBounds().top < -150 )
		{
			//Delete enemy
			delete this->enemiesUpDown.at(counter);
			this->enemiesUpDown.erase(this->enemiesUpDown.begin() + counter);
		}
		//Enemy player Collision
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			//Play SFX
			bourbxnHurtSFX.play();
			//Player ger infect
			this->infectPlayer = true;
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
		this->enemiesLeftRight.push_back(new Enemy(
			0.f, 
			rand() % this->window->getSize().y-20,
			this->enemySpeedDirMinus,
			this->enemySpeedDirPlus));									//Right
		this->enemiesLeftRight.push_back(new Enemy(
			this->window->getSize().x, 
			rand() % this->window->getSize().y-20,
			this->enemySpeedDirMinus,
			this->enemySpeedDirPlus));			//Left
		this->spawnTimerLeftRight = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto* enemy : this->enemiesLeftRight)
	{
		enemy->updateEnemyMoveLeftRight();


		//Bullet culling (top of screen)
		if (enemy->getBounds().left > this->window->getSize().x )
		{
			//Delete enemy
			delete this->enemiesLeftRight.at(counter);
			this->enemiesLeftRight.erase(this->enemiesLeftRight.begin() + counter);
		}
		if (enemy->getBounds().left < 0 )
		{
			//Delete enemy
			delete this->enemiesLeftRight.at(counter);
			this->enemiesLeftRight.erase(this->enemiesLeftRight.begin() + counter);
		}
		//Enemy player Collision
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			//Play SFX
			bourbxnHurtSFX.play();
			//Player ger infect
			this->infectPlayer = true;
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

	//Update frequency of enemies spawning
	this->time = clock.getElapsedTime().asSeconds();
	if (this->time > 5)
	{
		this->spawnTimerRate += 0.01f;
		if (this->spawnTimerRate > 1.2f)
			this->spawnTimerRate = 1.2f;
		if (this->enemiesLevel == 6)
		{
			this->enemySpeedDirMinus -= 0.1f;
			this->enemySpeedDirPlus += 0.1f;
		}
		clock.restart();
	}

	//Set enemy speed
	if (this->enemySpeedDirMinus > 5)
		this->enemySpeedDirMinus = 5;
	if (this->enemySpeedDirPlus > 5)
		this->enemySpeedDirPlus = 5;

	//Update enemies level
	if (this->spawnTimerRate <= 0.2f)
	{
		this->enemiesLevel = 1;
	}
	else if (this->spawnTimerRate > 0.2f && this->spawnTimerRate <= 0.4f)
	{
		this->enemiesLevel = 2;
	}
	else if (this->spawnTimerRate > 0.4f && this->spawnTimerRate <= 0.6f)
	{
		this->enemiesLevel = 3;
	}
	else if (this->spawnTimerRate > 0.6f && this->spawnTimerRate <= 0.8f)
	{
		this->enemiesLevel = 4;
	}
	else if (this->spawnTimerRate > 0.8f && this->spawnTimerRate <= 1.f)
	{
		this->enemiesLevel = 5;
	}
	else if (this->spawnTimerRate > 1.f)
	{
		this->enemiesLevel = 6;
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
				this->vaccineRandomPos = true;
				this->vaccineRandomRate = true;
				this->updateVaccineDrop();
				//Points in each gun type
				if (this->gunType == 0 || this->gunType == 1 || this->gunType == 2 || this->gunType == 3 || this->gunType == 4)
				{
					this->points += 1;
				}
				else if (this->gunType == 5)
				{
					this->points += 1;
				}
				else if (this->gunType == 6)
				{
					this->points += 1;
				}
				else if (this->gunType == 7)
				{
					this->points += 1;
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
				this->vaccineRandomPos = true;
				this->vaccineRandomRate = true;
				this->updateVaccineDrop();

				//Points in each gun type
				if (this->gunType == 0 || this->gunType == 1 || this->gunType == 2 || this->gunType == 3 || this->gunType == 4)
				{
					this->points += 1;
				}
				else if (this->gunType == 5)
				{
					this->points += 1;
				}
				else if (this->gunType == 6)
				{
					this->points += 1;
				}
				else if (this->gunType == 7)
				{
					this->points += 1;
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

void Game::updateHP()
{
	this->time2 = clock2.getElapsedTime().asSeconds();
	if (this->time2 > 1 && this->infectPlayer==true)
	{
		this->player->loseHp(this->enemiesLevel*4);
		clock2.restart();
	}
}

void Game::updateGunDrop()
{
	//std::cout << this->spawnTimerRate << std::endl;
	//std::cout << this->enemiesLevel << std::endl;
	//Random Gun
	if (this->points % this->pointsDropGun == 0
		&& this->points != 0 
		&& this->gunCorrect == false  
		&& this->gunRandomTypeState == true)
	{
		this->gunDropPercent = rand() % 99 + 1;
		//Enemies level 1
		if (this->enemiesLevel == 1)
		{
			gunDropItem = 1;
		}
		//Enemies level 2
		else if (this->enemiesLevel == 2)
		{
			if (this->gunDropPercent >= 1 && this->gunDropPercent <= 5)
			{
				this->gunDropItem = 1;
			}
			else if (this->gunDropPercent > 5 && this->gunDropPercent <= 50)
			{
				this->gunDropItem = 2;
			}
			else if (this->gunDropPercent > 50 && this->gunDropPercent <= 95)
			{
				this->gunDropItem = 3;
			}
			else if (this->gunDropPercent > 95 && this->gunDropPercent <= 100)
			{
				this->gunDropItem = 4;
			}
		}
		//Enemies level 3
		else if (this->enemiesLevel == 3)
		{
			if (this->gunDropPercent >= 1 && this->gunDropPercent <= 5)
			{
				this->gunDropItem = 2;
			}
			else if (this->gunDropPercent > 5 && this->gunDropPercent <= 50)
			{
				this->gunDropItem = 3;
			}
			else if (this->gunDropPercent > 50 && this->gunDropPercent <= 95)
			{
				this->gunDropItem = 4;
			}
			else if (this->gunDropPercent > 95 && this->gunDropPercent <= 100)
			{
				this->gunDropItem = 5;
			}
		}
		//Enemies level 4
		else if (this->enemiesLevel == 4)
		{
			if (this->gunDropPercent >= 1 && this->gunDropPercent <= 5)
			{
				this->gunDropItem = 3;
			}
			else if (this->gunDropPercent > 5 && this->gunDropPercent <= 50)
			{
				this->gunDropItem = 4;
			}
			else if (this->gunDropPercent > 50 && this->gunDropPercent <= 95)
			{
				this->gunDropItem = 5;
			}
			else if (this->gunDropPercent > 95 && this->gunDropPercent <= 100)
			{
				this->gunDropItem = 6;
			}
		}
		//Enemies level 4
		else if (this->enemiesLevel == 5)
		{
			if (this->gunDropPercent >= 1 && this->gunDropPercent <= 5)
			{
				this->gunDropItem = 4;
			}
			else if (this->gunDropPercent > 5 && this->gunDropPercent <= 50)
			{
				this->gunDropItem = 5;
			}
			else if (this->gunDropPercent > 50 && this->gunDropPercent <= 95)
			{
				this->gunDropItem = 6;
			}
			else if (this->gunDropPercent > 95 && this->gunDropPercent <= 100)
			{
				this->gunDropItem = 7;
			}
		}
		//Enemies level 4
		else if (this->enemiesLevel == 6)
		{
			if (this->gunDropPercent >= 1 && this->gunDropPercent <= 40)
			{
				this->gunDropItem = 5;
			}
			else if (this->gunDropPercent > 40 && this->gunDropPercent <= 80)
			{
				this->gunDropItem = 6;
			}
			else if (this->gunDropPercent > 80 && this->gunDropPercent <= 100)
			{
				this->gunDropItem = 7;
			}
		}
		
		this->gunDropState = true;
		this->gunRandomState = false;
		this->gunRandomTypeState = false;
	}
	else if (this->points%this->pointsDropGun && this->gunCorrect == true)
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
		this->infectPlayer = false;
	}
}

void Game::updateInfectedType()
{
	if (this->gunType == 7 && this->infectPlayer == false)
	{
		this->infectedType = 2;
	}
	else if (this->infectPlayer == false)
	{
		this->infectedType = 0;
	}
	else if (this->infectPlayer == true)
	{
		this->infectedType = 1;
	}
}

void Game::updateVaccineCollected()
{
	//Collect Vaccine
	if (this->spriteVaccineDrop.getGlobalBounds().intersects(this->player->getBounds()) && this->vaccineDropState == true)
	{
		std::cout << "player intersect vaccine" << std::endl;
		this->vaccineType = this->vaccineTypeDrop;
		this->vaccineDropState = false;
		this->vaccineRandomRate = true;
		this->vaccineRandomPos = true;
		this->vaccineDropState = false;
		this->deltaTime2 = 0;
		//Vaccine Active
		if (this->vaccineType == 1)
		{
			this->player->regainHP(20);
		}
		else if (this->vaccineType == 2)
		{
			this->infectPlayer = false;
		}
		else if (this->vaccineType == 3)
		{
			this->player->regainHP(50);
			this->infectPlayer = false;
		}
	}
	else if (!this->spriteVaccineDrop.getGlobalBounds().intersects(this->player->getBounds()) && this->vaccineDropState == true)
	{
		this->deltaTime2 += 1;
		if (this->deltaTime2 == 600)
		{
			this->gunRandomTypeState = true;
			this->vaccineDropState = false;
			this->vaccineRandomRate = true;
			this->vaccineRandomPos = true;
			this->vaccineDropState = false;
			this->deltaTime2 = 0;
		}
		//std::cout << deltaTime << std::endl;
	}
}

void Game::updateSelectedMenu()
{
	this->GameState = this->menu->getGameState();
}

void Game::updateSelectedGameOver()
{
	//Update Input Selected Menu
	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		this->GameState = 2;
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		this->GameState = 1;
	}
}

void Game::updateSelectNameInput()
{
	//Update Input Name
	if (Keyboard::isKeyPressed(Keyboard::Enter) && this->deltaTime6to2 > 10)
	{
		this->GameState = 2;
		this->deltaTime6to2 = 0;
		this->name = this->textboxName->getText();
		std::cout << this->name << std::endl;
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape) && this->deltaTime6to2 > 10)
	{
		this->GameState = 1;
		this->deltaTime6to2 = 0;
		this->initTextboxName();
	}
}

void Game::updateRestartGame()
{
	this->initSystems();
	this->initPlayer();
	this->initGun();
	this->initVaccine();
	this->initEnemies();
}

void Game::updateRestartEnemies()
{
	for (int i = 0; i < this->enemiesUpDown.size(); ++i)
	{
		delete this->enemiesUpDown[i];
		this->enemiesUpDown.erase(this->enemiesUpDown.begin() + i);
	}

	for (int i = 0; i < this->enemiesLeftRight.size(); ++i)
	{
		delete this->enemiesLeftRight[i];
		this->enemiesLeftRight.erase(this->enemiesLeftRight.begin() + i);
	}
}
	
void Game::update()
{
	this->updateInput();
	this->player->updateAttackStatus(this->playerAttackCoolDownMax);
	this->player->update();
	this->gun->updateSpriteTextures(this->gunType);
	this->vaccine->updateSpriteTextures(this->infectedType);
	this->updateGunType();
	this->updateInfectedType();
	this->gun->update();
	this->updateTextures();
	this->updateBullets();
	this->updateEnemiesUpDown();
	this->updateEnemiesLeftRight();
	this->updateEnemiesPower();
	this->updateCombatUpDown();
	this->updateCombatLeftRight();
	this->updateHP();
	this->updateEnemiesPower();
	this->updateGunDrop();
	this->updateVaccineCollected();
	this->updateGUI();
	this->updateWorld();
}

void Game::updateMenu()
{
	this->menu->updateInput();
	this->updateSelectedMenu();
	this->menu->setNewMenuState();
}

void Game::updateGameOver()
{
	this->updateSelectedGameOver();
	this->gameRestart = true;
}

void Game::renderGunDrop()
{
	if (this->gunDropState == true)
	{
		this->window->draw(this->spriteGunDrop);
	}
}

void Game::renderVaccineDrop()
{
	if (this->vaccineDropState == true)
	{
		this->window->draw(this->spriteVaccineDrop);
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
	this->renderGunDrop();
	this->renderVaccineDrop();
	this->gun->render(*this->window);
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
	this->vaccine->render(*this->window);
	this->window->display();
	
}

void Game::renderMenu()
{
	this->window->clear();
	this->menu->render(*this->window);
	this->window->display();
}

void Game::renderGameOver()
{
	this->window->clear();
	this->window->draw(this->gameOverText);
	this->window->draw(this->gameOverExplain1);
	this->window->draw(this->gameOverExplain2);
	this->window->draw(this->gameOverExplain3);
	this->window->draw(this->gameOverExplain4);
	this->window->draw(this->gameOverExplain5);
	this->window->display();
}

void Game::renderRanking()
{
	this->window->clear();
	this->topic->renderBackground(*this->window);
	this->topic->render(*this->window);
	for (int i = 0; i < 5; i++) {
		this->rankScore[i]->render(*this->window);
		this->rankName[i]->render(*this->window);
	}
	/*this->rankFirstScore->render(*this->window);
	this->rankFirstName->render(*this->window);*/
	this->window->display();
}

void Game::renderInputName()
{
	this->window->clear();
	this->textboxName->render(*this->window);
	this->window->display();
}
