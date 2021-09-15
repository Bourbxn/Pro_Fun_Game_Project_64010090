#pragma once

#include "map"
#include "string"
#include "sstream"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class Game
{
private:
	//Window
	RenderWindow* window;

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

	void run();

	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void update();
	void renderGUI();
	void renderWorld();
	void render();
};