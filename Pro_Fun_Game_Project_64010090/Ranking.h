#pragma once
#pragma once
#include <stdio.h>
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

class Ranking
{
private:
	Text text;
	Texture backgroundTex;
	Sprite background;

	void initBackground();
	void initText();

public:
	Ranking(int x, int y, std::string word,Font* font);
	virtual ~Ranking();

	//Functinos
	void getSize();

	//Render 
	void renderBackground(RenderTarget& target);
	void render(RenderTarget& target);
};
