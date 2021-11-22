#pragma once
#include <iostream> 
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Assets.h"
#include "Menu.h"

using namespace sf;

class StartMenuController;

class StartMenu : public Menu {

private:

    friend class StartMenuController;

    Button btnStart;

    void init()
    {
        btnStart = Button("Start", { 200,50 }, 20, Color::White, Color::Black, Assets::Instance().textureBox);
        btnStart.setPosition({ 400, 350 });
        btnStart.setFont(Assets::Instance().arial);
        btnStart.setVisible(false);
    }

    void setVisibleAllMembers(bool isVisible) override
    {
        btnStart.setVisible(isVisible);
    }

public:

    explicit StartMenu() { init(); }

    ~StartMenu() {}

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(btnStart);
    }
};