#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "Gun.h"
#include "Vaccine.h"
#include "sstream"
#include "Menu.h"
#include "Textbox.h"
#include "Ranking.h"


class Game
{
private:
	//Window
	RenderWindow* window;

	//Menu
	Menu* menu;

	//Input Name
	Textbox* textboxName;
	std::string name;

	//Ranking 
	Ranking* topic;
	Ranking* rankScore[6];
	Ranking* rankName[6];

	//Resource
	std::map<std::string, Texture*>textures;
	std::vector<Bullet*> bullets;

	//SFX
	SoundBuffer pistolShot;
	Sound pistolShotSFX;
	SoundBuffer alienShot;
	Sound alienShotSFX;
	SoundBuffer saxophoneShot;
	Sound saxophoneShotSFX;
	SoundBuffer capricornShot;
	Sound capricornShotSFX;
	SoundBuffer zombieDeath;
	Sound zombieDeathSFX;
	SoundBuffer bourbxnHurt;
	Sound bourbxnHurtSFX;
	SoundBuffer gunDropBuff;
	Sound gunDropSFX;
	SoundBuffer gunCorrectBuff;
	Sound gunCorrectSFX;

	//GUI
	Font font;
	Text pointText;
	Text gameOverText;
	Text gameOverExplain1;	//Press
	Text gameOverExplain2;  //"Enter"
	Text gameOverExplain3;	//for play again
	Text gameOverExplain4;	//"ESC"
	Text gameOverExplain5;	//for exit main menu

	//World
	Texture worldBackgroundTex;
	Sprite worldBackground;

	//Systems
	unsigned points;

	//Player
	Player* player;


	//Player GUI
	RectangleShape playerHpBar;
	RectangleShape playerHPBarBack;

	//Gun
	Gun* gun;
	Texture textureGunDrop;
	Sprite spriteGunDrop;


	//Vaccine
	Vaccine* vaccine;
	Texture textureVaccineDrop;
	Sprite spriteVaccineDrop;

	//Time
	Clock clock;
	float time;
	Clock clock2;
	float time2;
	int deltaTime;
	int deltaTime2;

	//Game State
	int GameState;
	bool gameOverBackMenu;
	bool gameRestart;
	bool nameInput;
	int deltaTime6to2;


	//Enemies
	float spawnTimerUpDown;
	float spawnTimerMaxUpDown;
	float spawnTimerLeftRight;
	float spawnTimerMaxLeftRight;
	float spawnTimerRate;
	std::vector<Enemy*> enemiesUpDown;
	std::vector<Enemy*> enemiesLeftRight;
	Enemy* enemyForFunction;
	int enemiesLevel;
	float enemySpeedDirPlus;
	float enemySpeedDirMinus;

	//Bullet
	float bulletDirX;
	float bulletDirY;
	float bulletPosX;
	float bulletPosY;
	float bulletRotDeg;

	//Gun
	bool gunDropState;
	bool gunRandomState;
	bool gunRandomTypeState;
	bool gunCorrect;
	int gunDropItem;
	unsigned int gunDropPercent;
	int gunDropPos_x;
	int gunDropPos_y;
	int gunType;
	float playerAttackCoolDownMax;
	bool gunDropPlay;
	bool gunCorrectPlay;
	int pointsDropGun;
	

	//Vaccine
	int vaccineType;
	bool vaccineDropState;
	bool infectPlayer;
	int infectedType;
	int vaccinePercentDrop;
	bool vaccineRandomRate;
	int vaccineTypeDrop;
	bool vaccineRandomPos;
	int vaccineDropPos_x;
	int vaccineDropPos_y;

	//GUI
	float gameOverExplainPosY;
	int gameOverExFontSize;
	int gameOverExThickness;
	float gameOverExStartPos;


	//Game State
	void initGameState();
	/*
	* GameState 1 is Menu
	* GameState 2 is Game Play
	* GameState 3 is Game Over
	* GameState 4 is Ranking
	* GameState 5 is Exit
	*/

	//Private functions
	void initWindow();
	void initMenu();
	void initTextboxName();
	void initRanking();
	void initTextures();
	void initAudio();
	void initGUI();
	void initWorld();
	void initSystems();
	void initPlayer();
	void initGun();
	void initVaccine();
	void initEnemies();
public:
	Game();
	virtual ~Game();

	//Functions
	void updateVaccineDrop();

	//PollEvents
	void updatePollEvents();
	void updatePollEventsInputName();

	//GameState
	void updateGameState();
	void updateDeltaTime6to2();

	//Update Game Play
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateTextures();
	void updateBullets();
	void updateEnemiesUpDown();
	void updateEnemiesLeftRight();
	void updateEnemiesPower();
	void updateCombatUpDown();
	void updateCombatLeftRight();
	void updateHP();
	void updateGunDrop();
	void updateGunType();
	void updateInfectedType();
	void updateVaccineCollected();

	//Update Menu
	void updateSelectedMenu();

	//Update Game Over
	void updateSelectedGameOver();
	void updateRestartGame();
	void updateRestartEnemies();

	//Update Name Input
	void updateSelectNameInput();

	//Main Update
	void update();
	void updateMenu();
	void updateGameOver();

	//Render
	void renderGunDrop();
	void renderVaccineDrop();
	void renderGUI();
	void renderWorld();

	//Main Render
	void render();
	void renderMenu();
	void renderGameOver();
	void renderRanking();
	//Sub Render
	void renderInputName();

	//Core
	void run();
};