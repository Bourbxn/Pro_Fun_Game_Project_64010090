#pragma once
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "Gun.h"
#include "sstream"



class Game
{
private:
	//Window
	RenderWindow* window;

	//Resource
	std::map<std::string, Texture*>textures;
	std::vector<Bullet*> bullets;

	//SFX
	SoundBuffer pistolShot;
	Sound pistolShotSFX;
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

	//Time
	Clock clock;
	float time;
	int deltaTime;


	//Enemies
	float spawnTimerUpDown;
	float spawnTimerMaxUpDown;
	float spawnTimerLeftRight;
	float spawnTimerMaxLeftRight;
	float spawnTimerRate;
	std::vector<Enemy*> enemiesUpDown;
	std::vector<Enemy*> enemiesLeftRight;

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

	//Private functions
	void initWindow();
	void initTextures();
	void initAudio();
	void initGUI();
	void initWorld();
	void initSystems();
	void initPlayer();
	void initGun();
	void initEnemies();
public:
	Game();
	virtual ~Game();

	//Functions

	//Update
	void updatePollEvents();
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
	void updateGunDrop();
	void updateGunType();
	void update();

	//Render
	void renderGunDrop();
	void renderGUI();
	void renderWorld();
	void render();

	//Core
	void run();
};