#pragma once
#include "Controller.h"
#include "MainMenu.h"
#include "BalanceMenu.h"
#include "PutCashMenu.h"
#include "GetCashMenu.h"
#include "TransferMenu.h"
#include <vector>

class MainMenuController : public Controller
{

private:

    MainMenu& mainMenu;
    BalanceMenu& balanceMenu;
    PutCashMenu& putCashMenu;
    GetCashMenu& getCashMenu;
    TransferMenu& transferMenu;

public:

    MainMenuController(RenderWindow& par, MainMenu& mainMenu, BalanceMenu& balanceMenu, PutCashMenu& putCashMenu, GetCashMenu& getCashMenu, TransferMenu& transferMenu)
        : mainMenu(mainMenu) 
        , balanceMenu(balanceMenu)
        , putCashMenu(putCashMenu)
        , getCashMenu(getCashMenu)
        , transferMenu(transferMenu) {}
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
        if (mainMenu.getButtons()[0].isMouseOver(event)) {
            mainMenu.setActive(false);
            balanceMenu.setActive(true);
        }
        if (mainMenu.getButtons()[1].isMouseOver(event)) {
            mainMenu.setActive(false);
            transferMenu.setActive(true);
        }
        if (mainMenu.getButtons()[2].isMouseOver(event)) {
            mainMenu.setActive(false);
            putCashMenu.setActive(true);
        }
        if (mainMenu.getButtons()[3].isMouseOver(event)) {
            mainMenu.setActive(false);
            getCashMenu.setActive(true);
        }
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
