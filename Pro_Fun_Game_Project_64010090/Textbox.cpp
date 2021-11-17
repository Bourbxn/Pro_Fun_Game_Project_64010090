#include "Textbox.h"

void Textbox::initVariables()
{
	this->isSelected = false;
	this->hasLimit = false;
	this->textbox.setCharacterSize(100);
	this->textbox.setFillColor(Color(255, 215, 0));
}

Textbox::Textbox(bool sel)
{
	this->initVariables();
	this->initBackground();
	this->initText();
	this->isSelected = sel;
	if (sel)
	{
		this->textbox.setString("");
	}
	else
	{
		this->textbox.setString("");
	}
}

Textbox::~Textbox()
{

}



void Textbox::inputLogic(int charTyped)
{
	if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
	{
		this->text << static_cast<char>(charTyped);
	}
	else if (charTyped == DELETE_KEY)
	{
		if (this->text.str().length() > 0)
		{
			this->deleteLastChar();
		}
	}
	this->textbox.setString(this->text.str() + "");
}

void Textbox::initBackground()
{
	if (!this->backgroundTex.loadFromFile("Textures/menu_bg.png"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}
	this->background.setScale(1.f, 1.f);
	this->background.setTexture(this->backgroundTex);
}

void Textbox::initText()
{
	if (!this->font.loadFromFile("Fonts/ARCADECLASSIC.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";
	this->textEnterName.setFont(this->font);
	this->textEnterName.setPosition(375, 25);
	this->textEnterName.setString("enter  your  name");
	this->textEnterName.setOutlineThickness(10);
	this->textEnterName.setCharacterSize(150);
}

void Textbox::deleteLastChar()
{
	std::string t = this->text.str();
	std::string newT = "";
	for (int i = 0; i < t.length() - 1; i++)
	{
		newT += t[i];
	}
	this->text.str("");
	this->text << newT;
	this->textbox.setString(text.str());
}

void Textbox::setFont(Font& font)
{
	this->textbox.setFont(font);
}

void Textbox::setPosition(Vector2f pos)
{
	this->textbox.setPosition(pos);
}


void Textbox::setColor(Color color)
{
	this->textbox.setFillColor(color);
}


void Textbox::setLimit(bool ToF, int lim)
{
	this->hasLimit = ToF;
	this->limit = lim;
}


void Textbox::setCharSize(int size)
{
	this->textbox.setCharacterSize(size);
}

void Textbox::setOutline(int outlineSize,Color color)
{
	this->textbox.setOutlineColor(color);
	this->textbox.setOutlineThickness(outlineSize);
}

void Textbox::setSelected(bool sel)
{
	this->isSelected = sel;
	if (!sel)
	{
		std::string t = this->text.str();
		std::string newT = "";
		for (int i = 0; i < t.length() - 1; i++)
		{
			newT += t[i];
		}
		this->textbox.setString(newT);
	}
}

void Textbox::typedOn(Event input)
{
	if (this->isSelected)
	{
		int charTyped = input.text.unicode;
		if (charTyped < 128)
		{
			if (this->hasLimit)
			{
				if (this->text.str().length() <= this->limit)
				{
					this->inputLogic(charTyped);
				}
				else if (this->text.str().length() > this->limit && charTyped == DELETE_KEY)
				{
					this->deleteLastChar();
				}
			}
			else
			{
				this->inputLogic(charTyped);
			}
		}
	}
}

std::string Textbox::getText()
{
	return this->text.str();
}



void Textbox::render(RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->textbox);
	target.draw(this->textEnterName);
}




