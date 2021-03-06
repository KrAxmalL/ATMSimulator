#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "TextBox.h"
#include "TextArea.h"
#include "Assets.h"
#include "Controller.h"
#include "Menu.h"
#include <vector>
#include <map>

using namespace sf;

class MainMenuController;

class MainMenu : public Menu {

private:

    friend class MainMenuController;

    TextArea areaWelcome;

    Button btnf1;
    Button btnf2;
    Button btnf3;
    Button btnf4;
    Button btnf5;
    Button btnf6;
    Button btnf7;
    Button btnf8;

    std::vector<Button> buttons;

    void init()
    {
        areaWelcome = TextArea("Welcome, _Cust_Name_!", { 400,50 }, 20, Color::White, Color::Black, Assets::Instance().textureLabel);
        areaWelcome.setFont(Assets::Instance().arial);
        areaWelcome.setPosition({ 300,150 });
        areaWelcome.setVisible(false);

        btnf1 = Button("Balance", { 240,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
        btnf1.setPosition({ 250, 300 });
        btnf1.setFont(Assets::Instance().arial);
        btnf1.setVisible(false);

        btnf2 = Button("Transfer", { 240,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
        btnf2.setPosition({ 510, 300 });
        btnf2.setFont(Assets::Instance().arial);
        btnf2.setVisible(false);

        btnf3 = Button("Put Cash", { 240,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
        btnf3.setPosition({ 250, 370 });
        btnf3.setFont(Assets::Instance().arial);
        btnf3.setVisible(false);

        btnf4 = Button("Get Cash", { 240,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
        btnf4.setPosition({ 510, 370 });
        btnf4.setFont(Assets::Instance().arial);
        btnf4.setVisible(false);

        btnf5 = Button("Show transactions", { 240,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
        btnf5.setPosition({ 250, 440 });
        btnf5.setFont(Assets::Instance().arial);
        btnf5.setVisible(false);

        btnf6 = Button("Block card", { 240,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
        btnf6.setPosition({ 510, 440 });
        btnf6.setFont(Assets::Instance().arial);
        btnf6.setVisible(false);

        btnf7 = Button("Remove card", { 240,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
        btnf7.setPosition({ 250, 510 });
        btnf7.setFont(Assets::Instance().arial);
        btnf7.setVisible(false);

        btnf8 = Button("Change card pin", { 240,50 }, 25, Color::White, Color::Black, Assets::Instance().textureBox);
        btnf8.setPosition({ 510, 510 });
        btnf8.setFont(Assets::Instance().arial);
        btnf8.setVisible(false);

        buttons = { btnf1, btnf2, btnf3, btnf4, btnf5, btnf6, btnf7, btnf8 };
    }

    void setVisibleAllMembers(bool isVisible) override
    {
        for (auto& button : buttons)
        {
            button.setVisible(isVisible);
        }
        areaWelcome.setVisible(isVisible);
    }

    std::vector<Button>& getButtons()
    {
        return buttons;
    }

public:

    explicit MainMenu() { init(); }

    ~MainMenu() {}

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        for (auto const& button : buttons)
        {
            target.draw(button);
        }
        target.draw(areaWelcome);
    }
};