#pragma once
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
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

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

	//Bullet
	float bulletDirX;
	float bulletDirY;
	float bulletPosX;
	float bulletPosY;
	float bulletRotDeg;

	//Private functions
	void initWindow();
	void initTextures();
	void initAudio();
	void initGUI();
	void initWorld();
	void initSystems();
	void initPlayer();
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
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void update();

	//Render
	void renderGUI();
	void renderWorld();
	void render();

	//Core
	void run();
};