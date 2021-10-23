#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "TextBox.h"
#include "TextArea.h"

using namespace sf;

class Assets {

private:
	Assets() {};

	~Assets() {};

	Assets(Assets const&) = delete;
	Assets& operator= (Assets const&) = delete;
	Assets(Assets&&) = delete;
	Assets& operator=(Assets&&) = delete;


public:

	Texture textureFon;
	Texture textureBox;
	Texture textureLabel;
	Texture textureButton;
	Font arial;
	Color Grey;
	Sprite background;

	static Assets& Instance()
	{
		static Assets s;
		return s;
	}

	void load()
	{
		if (!(textureFon.loadFromFile("Forest.png")))
		{

		}
		if (!(textureBox.loadFromFile("blank.png")))
		{

		}
		if (!(textureLabel.loadFromFile("label1.png")))
		{

		}
		if (!(textureButton.loadFromFile("buttonFon.png")))
		{

		}

		arial.loadFromFile("arial.ttf");

		Grey = { 200, 200, 200 };

		background = Sprite{textureFon};
	}
};
