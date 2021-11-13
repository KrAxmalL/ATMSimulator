#pragma once
#include "Controller.h"
#include "MainMenu.h"
#include "PutCashMenu.h"

class PutCashMenuController : public Controller
{

private:

    MainMenu& mainMenu;
    PutCashMenu& putCashMenu;

public:

    PutCashMenuController(RenderWindow& par, MainMenu& mainMenu, PutCashMenu& putCashMenu) : mainMenu(mainMenu), putCashMenu(putCashMenu) {}
    ~PutCashMenuController() {}

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

    void mouseMoved(const Event& event) {

        if (putCashMenu.btnOkCash.isMouseOver(event)) {
            putCashMenu.btnOkCash.setBackColor(Assets::Instance().Grey);
        }
        else
        {
            putCashMenu.btnOkCash.setBackColor(Color::White);
        }
        std::vector<Button>& buttons = putCashMenu.getButtons();
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

    void mouseButtonPressed(const Event& event) {
        if (putCashMenu.btnOkCash.isMouseOver(event)) {
            putCashMenu.clearSum();
            putCashMenu.setActive(false);
            mainMenu.setActive(true);
        }
        std::vector<Button>& buttons = putCashMenu.getButtons();
        for (auto& button : buttons)
        {
            if (button.isMouseOver(event))
            {
                putCashMenu.addMoney(button.getText());
            }
        }
        
    }

    bool isActive() override
    {
        return putCashMenu.isActive();
    }

    void setActive(bool isActive) override
    {
        putCashMenu.setActive(isActive);
    }

    Menu& menu() override
    {
        return putCashMenu;
    }
};
