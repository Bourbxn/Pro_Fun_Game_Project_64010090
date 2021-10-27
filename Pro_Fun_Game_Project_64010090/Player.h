#pragma once
#include "iostream"
#include "vector"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
using namespace sf;


class Player
{
private:
	Sprite sprite;
	Texture texture;

	int animation;
	int animationDelay;

	float movementspeed;

	float attackCooldown;
	float attackCooldownMax;

	int hp;
	int hpMax;

	//Private Functions
	void initVariables();
	void initTexture();
	void initSprite();
public:
	Player();
	virtual ~Player();

	//Accessor
	const Vector2f& getPos() const;
	const FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;

	//Modifiers
	void setHp(const int hp);
	void loseHp(const int value);
	void regainHP(const int value);

	//Functions
	void move(const float dir_X, const float dir_Y);
	const bool canAttack();

	void updateSprite();
	void updateAttackStatus(float attackCoolDownMaxUpdate);
	void updateAttack();
	void update();
	void render(RenderTarget& target);
};

