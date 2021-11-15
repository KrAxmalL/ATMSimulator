#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"

#include "Assets.h"
#include "Menu.h"
#include "TransactionsListView.h"
using namespace sf;

class TransactionsMenu : public Menu
{
private:

	RenderWindow& window;

	void init()
	{		
		btnOk = Button("Ok", { 100,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
		btnOk.setPosition({ 450, 570 });
		btnOk.setFont(Assets::Instance().arial);
		btnOk.setVisible(false);

		btnNextPage = Button("=>", { 100,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
		btnNextPage.setPosition({ 620, 500 });
		btnNextPage.setFont(Assets::Instance().arial);
		btnNextPage.setVisible(false);

		pageNum = TextArea("", { 150,50 }, 20, Color::White, Color::Black, Assets::Instance().textureLabel);
		pageNum.setFont(Assets::Instance().arial);
		pageNum.setPosition({ 420,500 });
		pageNum.setVisible(false);

		btnPrevPage = Button("<=", { 100,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
		btnPrevPage.setPosition({ 280, 500 });
		btnPrevPage.setFont(Assets::Instance().arial);
		btnPrevPage.setVisible(false);
	}

	void setVisibleAllMembers(bool isVisible) override
	{
		btnOk.setVisible(isVisible);
		pageNum.setVisible(isVisible);
		transactionsListView.setVisible(isVisible);
		btnNextPage.setVisible(isVisible);
		btnPrevPage.setVisible(isVisible);
	}

public:
	Button btnOk;
	Button btnNextPage;
	Button btnPrevPage;
	TextArea pageNum;
	TransactionsListView transactionsListView;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(btnOk);
		target.draw(pageNum);
		target.draw(btnNextPage);
		target.draw(btnPrevPage);
		target.draw(transactionsListView);
	}

	TransactionsMenu(RenderWindow& par) : window(par) { init(); }
	~TransactionsMenu() {}

};