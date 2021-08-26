#ifndef BULLET_H
#define BULLET_H

#include "SFML/Graphics.hpp"
#include "iostream"
using namespace sf;

class Bullet
{
private:

	Sprite shape;
	Texture* texture;
	Vector2f direction;
	float movementspeed;
public:
	Bullet();
	Bullet(Texture * texture,float pos_x,float pos_y, float dir_x,float dir_y,float movement_speed);
	virtual ~Bullet();

	//Acecessor
	const FloatRect getBounds() const;
	void update();
	void render(RenderTarget* target);
};

#endif // !BULLET_H