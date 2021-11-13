#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "TextBox.h"
#include "TextArea.h"
#include "Assets.h"
#include "Controller.h"
#include "Menu.h"

using namespace sf;

class EnterPinMenu : public Menu {

private:

	RenderWindow& window;

	void init()
	{
		btnOkPin = Button("OK", { 80,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
		btnOkPin.setPosition({ 450, 500 });
		btnOkPin.setFont(Assets::Instance().arial);
		btnOkPin.setVisible(false);

		areaCard = TextArea("Input PIN", { 300,50 }, 20, Color::White, Color::Black, Assets::Instance().textureLabel);
		areaCard.setFont(Assets::Instance().arial);
		areaCard.setPosition({ 350,200 });
		areaCard.setVisible(false);

		boxCardNum = Textbox(25, Color::Black, true, Assets::Instance().textureBox);
		boxCardNum.setFont(Assets::Instance().arial);
		boxCardNum.setPosition({ 450,300 });
		boxCardNum.setVisible(false);
		boxCardNum.clear();
		boxCardNum.setSecret(true);
		boxCardNum.setlimit(true, 4);
	}

public:

	Button btnOkPin;
	TextArea areaCard;
	Textbox boxCardNum;

	EnterPinMenu(RenderWindow& par) : window(par) { init(); }

	~EnterPinMenu() {}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(btnOkPin);
		target.draw(areaCard);
		target.draw(boxCardNum);
	}

private:

	void setVisibleAllMembers(bool isVisible) override
	{
		btnOkPin.setVisible(isVisible);
		boxCardNum.setVisible(isVisible);
		areaCard.setVisible(isVisible);
	}

};