#pragma once
#include "iostream"
#include "vector"
#include "sstream"
#include<utility>
#include<algorithm>
#include<string>
#include<vector>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
using namespace sf;

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox
{
private:
	Text textbox;
	Text textEnterName;
	Texture backgroundTex;
	Sprite background;
	Font font;
	std::ostringstream text;
	bool isSelected;
	bool hasLimit;
	int limit;
	//Init
	void initVariables();
	void initBackground();
	void initText();

	//Function
	void inputLogic(int charTyped);
	void deleteLastChar();

	
public:
	Textbox(bool sel);
	virtual ~Textbox();

	//Functions
	void setFont(Font& font);
	void setPosition(Vector2f pos);
	void setColor(Color color);
	void setCharSize(int size);
	void setLimit(bool ToF, int lim);
	void setOutline(int outlineSize,Color color);
	void setSelected(bool sel);
	void typedOn(Event input);

	//Assescor
	std::string getText();

	//render
	void render(RenderTarget& target);
};

