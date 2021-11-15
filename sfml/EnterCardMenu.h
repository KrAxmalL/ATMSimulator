#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Button.h"
#include "TextBox.h"
#include "TextArea.h"
#include "Assets.h"
#include "Controller.h"
#include "Menu.h"

using namespace sf;

class EnterCardMenu : public Menu {

private:

	RenderWindow& window;

	void init() 
	{
		btnOkCard = Button ("OK", { 100,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
		btnOkCard.setPosition({ 450, 500 });
		btnOkCard.setFont(Assets::Instance().arial);
		btnOkCard.setVisible(false);

		areaCard = TextArea("Input card number", { 300,50 }, 20, Color::White, Color::Black, Assets::Instance().textureLabel);
		areaCard.setFont(Assets::Instance().arial);
		areaCard.setPosition({ 350,200 });
		areaCard.setVisible(false);

		boxCardNum = Textbox(25, Color::Black, true, Assets::Instance().textureBox);
		boxCardNum.setFont(Assets::Instance().arial);
		boxCardNum.setPosition({ 450,300 });
		boxCardNum.setVisible(false);
		boxCardNum.clear();
		boxCardNum.setSecret(false);
		boxCardNum.setlimit(true, 5);

	}

public:

	Button btnOkCard;
	TextArea areaCard;
	Textbox boxCardNum;
	EnterCardMenu(RenderWindow& par) : window(par) { init(); }

	~EnterCardMenu() {}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		// consider adding
		target.draw(btnOkCard);
		target.draw(areaCard);
		target.draw(boxCardNum);
		target.draw(errBox);
	}

private:

	void setVisibleAllMembers(bool isVisible) override
	{
		btnOkCard.setVisible(isVisible);
		areaCard.setVisible(isVisible);
		boxCardNum.setVisible(isVisible);
	}
};

