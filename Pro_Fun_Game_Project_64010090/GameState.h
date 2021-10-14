#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"
class GameState:
	public State
{
private:

public:
	GameState(RenderWindow* window);
	virtual ~GameState();

	//Functions
	void endState();

	void updateKeyBinds(const float& dt);
	void update(const float& dt);
	void render(RenderTarget* target = nullptr);
};
#endif
