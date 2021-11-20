#pragma once
#include "Menu.h"

class RemoveCardMenu : public Menu
{

private:

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

		acceptText = TextArea("Are you sure you want to remove card?", { 500, 50 }, 18, Color::White, Color::Black, Assets::Instance().textureLabel);
		acceptText.setFont(Assets::Instance().arial);
		acceptText.setPosition({ 250,150 });
		acceptText.setVisible(false);
	}

	void setVisibleAllMembers(bool isVisible) override
	{
		btnOk.setVisible(isVisible);
		btnCancel.setVisible(isVisible);
		acceptText.setVisible(isVisible);
	}

public:

	Button btnOk;
	Button btnCancel;
	TextArea acceptText;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(btnOk);
		target.draw(btnCancel);
		target.draw(acceptText);
	}

	explicit RemoveCardMenu() { init(); }
	~RemoveCardMenu() {}
};
