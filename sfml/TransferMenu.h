#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "TextBox.h"
#include "TextArea.h"
#include "TextBox.h"
#include "Assets.h"
#include "Controller.h"
#include "Menu.h"

using namespace sf;

class TransferController;

class TransferMenu : public Menu {

private:

	friend class TransferController;

	Button btnSend;
	Button btnCancel;
	TextArea areaSend;
	TextArea areaAmount;
	TextArea areaCardNum;
	Textbox boxAmount1;
	Textbox boxAmount2;
	Textbox boxCardNum;

	void init()
	{
		btnSend = Button("Send", { 100,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
		btnSend.setPosition({ 380, 500 });
		btnSend.setFont(Assets::Instance().arial);
		btnSend.setVisible(false);

		btnCancel = Button("Cancel", { 100,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
		btnCancel.setPosition({ 520, 500 });
		btnCancel.setFont(Assets::Instance().arial);
		btnCancel.setVisible(false);

		areaSend = TextArea("Transfer to card", { 300,100 }, 20, Color::White, Color::Black, Assets::Instance().textureLabel);
		areaSend.setFont(Assets::Instance().arial);
		areaSend.setPosition({ 350,150 });
		areaSend.setVisible(false);

		areaCardNum = TextArea("Card number:", { 300,50 }, 20, Color::White, Color::Black, Assets::Instance().textureLabel);
		areaCardNum.setFont(Assets::Instance().arial);
		areaCardNum.setPosition({ 250,300 });
		areaCardNum.setVisible(false);

		boxCardNum = Textbox(25, Color::Black, true, Assets::Instance().textureBox);
		boxCardNum.setFont(Assets::Instance().arial);
		boxCardNum.setPosition({ 550,300 });
		boxCardNum.setVisible(false);
		boxCardNum.clear();
		boxCardNum.setSelected(true);
		boxCardNum.setSecret(false);
		boxCardNum.setlimit(true, 5);

		areaAmount = TextArea("Amount:", { 300,50 }, 20, Color::White, Color::Black, Assets::Instance().textureLabel);
		areaAmount.setFont(Assets::Instance().arial);
		areaAmount.setPosition({ 250,400 });
		areaAmount.setVisible(false);

		boxAmount1 = Textbox(25, Color::Black, true, Assets::Instance().textureBox);
		boxAmount1.setFont(Assets::Instance().arial);
		boxAmount1.setPosition({ 550,400 });
		boxAmount1.setVisible(false);
		boxAmount1.clear();
		boxAmount1.setStartedValue("");
		boxAmount1.setSelected(false);
		boxAmount1.setSecret(false);
		boxAmount1.setlimit(true, 6);

		boxAmount2 = Textbox(25, Color::Black, true, Assets::Instance().textureBox);
		boxAmount2.setFont(Assets::Instance().arial);
		boxAmount2.setPosition({ 675,400 });
		boxAmount2.setVisible(false);
		boxAmount2.clear();
		boxAmount2.setStartedValue("");
		boxAmount2.setSelected(false);
		boxAmount2.setSecret(false);
		boxAmount2.setlimit(true, 2);
	}

	void setVisibleAllMembers(bool isVisible) override
	{
		btnSend.setVisible(isVisible);
		btnCancel.setVisible(isVisible);
		boxAmount1.setVisible(isVisible);
		boxAmount2.setVisible(isVisible);
		areaSend.setVisible(isVisible);
		areaCardNum.setVisible(isVisible);
		areaAmount.setVisible(isVisible);
		boxCardNum.setVisible(isVisible);
		//areaBalance.setText();
	}

public:

	explicit TransferMenu() { init(); }

	~TransferMenu() {}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(btnSend);
		target.draw(btnCancel);
		target.draw(areaSend);
		target.draw(areaCardNum);
		target.draw(areaAmount);
		target.draw(boxAmount1);
		target.draw(boxAmount2);
		target.draw(boxCardNum);
		target.draw(errBox);
	}
};

