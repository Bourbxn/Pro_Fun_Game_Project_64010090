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


	//Variables
	float dt;
	Clock dtClock;
	

	//Resource
	std::map<std::string, Texture*>textures;
	std::vector<Bullet*> bullets;

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
	void initGUI();
	void initWorld();
	void initSystems();
	void initPlayer();
	void initEnemies();
public:
	Game();
	virtual ~Game();

	//Functions

	//Regular
	void endApplication();

	//Update
	void updateDT();
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