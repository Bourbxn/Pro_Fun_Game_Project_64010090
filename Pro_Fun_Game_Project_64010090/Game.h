#pragma once

#include "map"
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

	//Player
	Player* player;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

	//Private functions
	void initWindow();
	void initTextures();
	void initPlayer();
	void initEnemies();
public:
	Game();
	virtual ~Game();

	//Functions

	void run();

	void updatePollEvents();
	void updateInput();
	void updateBullets();
	void updateEnemies();
	void update();
	void render();
};