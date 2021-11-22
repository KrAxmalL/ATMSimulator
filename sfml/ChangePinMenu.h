#pragma once
#include "Menu.h"

class ChangePinMenuController;

class ChangePinMenu : public Menu
{
private:

	friend class ChangePinMenuController;

	Button btnOk;
	Button btnCancel;

	TextArea areaOldPin;
	Textbox boxOldCardPin;

	TextArea areaNewPin;
	Textbox boxNewCardPin;

	TextArea areaNewPinRepeat;
	Textbox boxNewCardPinRepeat;

	void init()
	{
		btnOk = Button("Ok", { 100,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
		btnOk.setPosition({ 380, 500 });
		btnOk.setFont(Assets::Instance().arial);
		btnOk.setVisible(false);

		btnCancel = Button("Cancel", { 100,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
		btnCancel.setPosition({ 520, 500 });
		btnCancel.setFont(Assets::Instance().arial);
		btnCancel.setVisible(false);

		areaOldPin = TextArea("Enter current pin", { 300,50 }, 20, Color::White, Color::Black, Assets::Instance().textureLabel);
		areaOldPin.setFont(Assets::Instance().arial);
		areaOldPin.setPosition({ 275, 200 });
		areaOldPin.setVisible(false);

		boxOldCardPin = Textbox(25, Color::Black, true, Assets::Instance().textureBox);
		boxOldCardPin.setFont(Assets::Instance().arial);
		boxOldCardPin.setPosition({ 600, 200 });
		boxOldCardPin.setVisible(false);
		boxOldCardPin.clear();
		boxOldCardPin.setSecret(true);
		boxOldCardPin.setlimit(true, 4);
		boxOldCardPin.setSelected(false);

		areaNewPin = TextArea("Enter new pin", { 300,50 }, 20, Color::White, Color::Black, Assets::Instance().textureLabel);
		areaNewPin.setFont(Assets::Instance().arial);
		areaNewPin.setPosition({ 275, 300 });
		areaNewPin.setVisible(false);

		boxNewCardPin = Textbox(25, Color::Black, true, Assets::Instance().textureBox);
		boxNewCardPin.setFont(Assets::Instance().arial);
		boxNewCardPin.setPosition({ 600, 300 });
		boxNewCardPin.setVisible(false);
		boxNewCardPin.clear();
		boxNewCardPin.setSecret(true);
		boxNewCardPin.setlimit(true, 4);
		boxNewCardPin.setSelected(false);

		areaNewPinRepeat = TextArea("Repeat new pin", { 300,50 }, 20, Color::White, Color::Black, Assets::Instance().textureLabel);
		areaNewPinRepeat.setFont(Assets::Instance().arial);
		areaNewPinRepeat.setPosition({ 275, 400 });
		areaNewPinRepeat.setVisible(false);

		boxNewCardPinRepeat = Textbox(25, Color::Black, true, Assets::Instance().textureBox);
		boxNewCardPinRepeat.setFont(Assets::Instance().arial);
		boxNewCardPinRepeat.setPosition({ 600, 400 });
		boxNewCardPinRepeat.setVisible(false);
		boxNewCardPinRepeat.clear();
		boxNewCardPinRepeat.setSecret(true);
		boxNewCardPinRepeat.setlimit(true, 4);
		boxNewCardPinRepeat.setSelected(false);
		
		setErrMessagePosition(400, 150);
	}

	void setVisibleAllMembers(bool isVisible) override
	{
		btnOk.setVisible(isVisible);
		btnCancel.setVisible(isVisible);
		areaOldPin.setVisible(isVisible);
		boxOldCardPin.setVisible(isVisible);
		areaNewPin.setVisible(isVisible);
		boxNewCardPin.setVisible(isVisible);
		areaNewPinRepeat.setVisible(isVisible);
		boxNewCardPinRepeat.setVisible(isVisible);
	}

public:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(btnOk);
		target.draw(btnCancel);
		target.draw(areaOldPin);
		target.draw(boxOldCardPin);
		target.draw(areaNewPin);
		target.draw(boxNewCardPin);
		target.draw(areaNewPinRepeat);
		target.draw(boxNewCardPinRepeat);
		target.draw(errBox);
	}

	explicit ChangePinMenu() { init(); }
	~ChangePinMenu() {}
};
