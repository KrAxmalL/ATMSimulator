#pragma once
#include <SFML/Graphics.hpp>
#include <iomanip>
#include "Button.h"
#include "TextBox.h"
#include "TextArea.h"
#include "Assets.h"
#include "Controller.h"
#include "Menu.h"

using namespace sf;

class GetCashMenu : public Menu {

private:

	void init()
	{
		btn1000 = Button("1000", { 240,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
		btn1000.setPosition({ 250, 300 });
		btn1000.setFont(Assets::Instance().arial);
		btn1000.setVisible(false);

		btn500 = Button("500", { 240,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
		btn500.setPosition({ 510, 300 });
		btn500.setFont(Assets::Instance().arial);
		btn500.setVisible(false);

		btn200 = Button("200", { 240,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
		btn200.setPosition({ 250, 370 });
		btn200.setFont(Assets::Instance().arial);
		btn200.setVisible(false);

		btn100 = Button("100", { 240,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
		btn100.setPosition({ 510, 370 });
		btn100.setFont(Assets::Instance().arial);
		btn100.setVisible(false);

		btn50 = Button("50", { 240,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
		btn50.setPosition({ 250, 440 });
		btn50.setFont(Assets::Instance().arial);
		btn50.setVisible(false);

		btn20 = Button("20", { 240,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
		btn20.setPosition({ 510, 440 });
		btn20.setFont(Assets::Instance().arial);
		btn20.setVisible(false);

		btnRemoveCash = Button("Clear Amount", { 500,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
		btnRemoveCash.setPosition({ 250, 500 });
		btnRemoveCash.setFont(Assets::Instance().arial);
		btnRemoveCash.setVisible(false);

		btnOkCash = Button("Remove", { 120,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
		btnOkCash.setPosition({ 380, 570 });
		btnOkCash.setFont(Assets::Instance().arial);
		btnOkCash.setVisible(false);

		btnCancel = Button("Cancel", { 120,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
		btnCancel.setPosition({ 520, 570 });
		btnCancel.setFont(Assets::Instance().arial);
		btnCancel.setVisible(false);

		areaCash = TextArea("Amount to remove:\n\n0.00 hrn", { 300,150 }, 20, Color::White, Color::Black, Assets::Instance().textureLabel);
		areaCash.setFont(Assets::Instance().arial);
		areaCash.setPosition({ 350,120 });
		areaCash.setVisible(false);

		errBox.setPosition({ 370, 270 });

		buttons = { btn1000, btn500, btn200, btn100, btn50, btn20 };
	}

public:

	Button btn1000;
	Button btn500;
	Button btn200;
	Button btn100;
	Button btn50;
	Button btn20;

	std::vector<Button> buttons;

	Button btnRemoveCash;
	Button btnOkCash;
	Button btnCancel;
	TextArea areaCash;

	double getSum = 0.0;

	explicit GetCashMenu() { init(); }

	~GetCashMenu() {}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(btnRemoveCash);
		target.draw(btnOkCash);
		target.draw(btnCancel);
		target.draw(areaCash);
		for (auto const& button : buttons)
		{
			target.draw(button);
		}
		target.draw(errBox);
	}

	void addMoney(sf::String money) {
		getSum += stod(std::string(money));
		std::string line(std::to_string(getSum));
		line.pop_back();
		line.pop_back();
		line.pop_back();
		line.pop_back();
		areaCash.setText("Amount to remove:\n\n" + line + " hrn");
	}

	void clearSum() {
		getSum = 0;
		areaCash.setText("Amount to remove:\n\n0.00 hrn");
	}

	std::vector<Button>& getButtons()
	{
		return buttons;
	}

private:

	void setVisibleAllMembers(bool isVisible) override
	{
		btnRemoveCash.setVisible(isVisible);
		btnOkCash.setVisible(isVisible);
		btnCancel.setVisible(isVisible);
		areaCash.setVisible(isVisible);
		
		for (auto& button : buttons)
		{
			button.setVisible(isVisible);
		}
	}
};

