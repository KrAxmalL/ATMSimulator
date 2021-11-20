#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "TextBox.h"
#include "TextArea.h"
#include "Assets.h"
#include "Controller.h"
#include "Menu.h"

using namespace sf;

class BalanceMenu : public Menu {

private:

	void init()
	{
		btnOkBalance = Button("OK", { 100,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
		btnOkBalance.setPosition({ 450, 500 });
		btnOkBalance.setFont(Assets::Instance().arial);
		btnOkBalance.setVisible(false);

		areaBalance = TextArea("BALANCE:\n\n_balance_ hrn", { 300,200 }, 20, Color::White, Color::Black, Assets::Instance().textureLabel);
		areaBalance.setFont(Assets::Instance().arial);
		areaBalance.setPosition({ 350,250 });
		areaBalance.setVisible(false);
	}

public:

	Button btnOkBalance;
	TextArea areaBalance;

	explicit BalanceMenu() { init(); }

	~BalanceMenu() {}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(btnOkBalance);
		target.draw(areaBalance);
	}

private:

	void setVisibleAllMembers(bool isVisible) override
	{
		btnOkBalance.setVisible(isVisible);
		areaBalance.setVisible(isVisible);
	}
};

