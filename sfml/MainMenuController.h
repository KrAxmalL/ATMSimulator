#pragma once
#include "Controller.h"
#include "MainMenu.h"
#include <vector>

class MainMenuController : public Controller
{

private:

    MainMenu& mainMenu;

public:

    MainMenuController(RenderWindow& par, MainMenu& mainMenu) : mainMenu(mainMenu) {}
    ~MainMenuController() {}

    virtual void handleEvent(const Event& event) override
    {
        switch (event.type)
        {
        case Event::MouseMoved:
            mouseMoved(event);
            break;
        case Event::MouseButtonPressed:
            mouseButtonPressed(event);
            break;
        }
    }

    void mouseMoved(const Event& event) 
    {
        std::vector<Button>& buttons = mainMenu.getButtons();
        for (auto& button : buttons)
        {
            if (button.isMouseOver(event))
            {
                button.setBackColor(Assets::Instance().Grey); break;
            }
            else {
                button.setBackColor(Color::White);
            }
        }
    }

    void mouseButtonPressed(const Event& event) 
    {
       //move to any other menu
    }

    bool isActive() override
    {
        return mainMenu.isActive();
    }

    void setActive(bool isActive) override
    {
        mainMenu.setActive(isActive);
    }

    Menu& menu() override
    {
        return mainMenu;
    }

};
