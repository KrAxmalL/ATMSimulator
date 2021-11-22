#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "TextBox.h"
#include "TextArea.h"
#include "Assets.h"
#include "Controller.h"
#include "Menu.h"

using namespace sf;

class EnterPinController;

class EnterPinMenu : public Menu {

private:

	friend class EnterPinController;

	Button btnOkPin;
	TextArea areaPin;
	Textbox boxCardPin;

	void init()
	{
		btnOkPin = Button("OK", { 80,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
		btnOkPin.setPosition({ 450, 500 });
		btnOkPin.setFont(Assets::Instance().arial);
		btnOkPin.setVisible(false);

		areaPin = TextArea("Input PIN", { 300,50 }, 20, Color::White, Color::Black, Assets::Instance().textureLabel);
		areaPin.setFont(Assets::Instance().arial);
		areaPin.setPosition({ 350,200 });
		areaPin.setVisible(false);

		boxCardPin = Textbox(25, Color::Black, true, Assets::Instance().textureBox);
		boxCardPin.setFont(Assets::Instance().arial);
		boxCardPin.setPosition({ 450,300 });
		boxCardPin.setVisible(false);
		boxCardPin.clear();
		boxCardPin.setSecret(true);
		boxCardPin.setlimit(true, 4);
	}

	void setVisibleAllMembers(bool isVisible) override
	{
		btnOkPin.setVisible(isVisible);
		boxCardPin.setVisible(isVisible);
		areaPin.setVisible(isVisible);
	}

public:

	explicit EnterPinMenu() { init(); }

	~EnterPinMenu() {}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(btnOkPin);
		target.draw(areaPin);
		target.draw(boxCardPin);
		target.draw(errBox);
	}
};