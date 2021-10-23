#pragma once
#include <iostream> 
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Assets.h"
#include "Menu.h"

using namespace sf;

class StartMenu : public Menu {

private:

    RenderWindow& window;

    void init()
    {
        btnStart = Button("Start", { 200,50 }, 20, Color::White, Color::Black, Assets::Instance().textureBox);
        btnStart.setPosition({ 400, 350 });
        btnStart.setFont(Assets::Instance().arial);
        btnStart.setVisible(false);
    }

public:

    Button btnStart;

    StartMenu(RenderWindow& par): window(par) { init(); }

    ~StartMenu() {}

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(btnStart);
    }

private:

    void setVisibleAllMembers(bool isVisible) override
    {
        btnStart.setVisible(isVisible);
    }
};