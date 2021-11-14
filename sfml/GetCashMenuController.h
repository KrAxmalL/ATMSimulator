#pragma once
#include "Controller.h"
#include "MainMenu.h"
#include "GetCashMenu.h"

class GetCashMenuController : public Controller
{

private:

    MainMenu& mainMenu;
    GetCashMenu& getCashMenu;

    CardService& cardService;

public:

    GetCashMenuController(RenderWindow& par, MainMenu& mainMenu, GetCashMenu& getCashMenu, CardService& cardService) : mainMenu(mainMenu), getCashMenu(getCashMenu), cardService(cardService) {}
    ~GetCashMenuController() {}

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

        if (getCashMenu.btnOkCash.isMouseOver(event)) {
            getCashMenu.btnOkCash.setBackColor(Assets::Instance().Grey);
        }
        else
        {
            getCashMenu.btnOkCash.setBackColor(Color::White);
        }
        if (getCashMenu.btnRemoveCash.isMouseOver(event)) {
            getCashMenu.btnRemoveCash.setBackColor(Assets::Instance().Grey);
        }
        else
        {
            getCashMenu.btnRemoveCash.setBackColor(Color::White);
        }
        std::vector<Button>& buttons = getCashMenu.getButtons();
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
        if (getCashMenu.btnOkCash.isMouseOver(event)) {
            getCash();
            getCashMenu.clearSum();
            getCashMenu.setActive(false);
            mainMenu.setActive(true);
        }
        if (getCashMenu.btnRemoveCash.isMouseOver(event)) {
            getCashMenu.clearSum();
        }
        std::vector<Button>& buttons = getCashMenu.getButtons();
        for (auto& button : buttons)
        {
            if (button.isMouseOver(event))
            {
                getCashMenu.addMoney(button.getText());
            }
        }

    }

    bool getCash()
    {
        double cash = -getCashMenu.getSum;
        std::cout << "cash: " << cash << std::endl;
        cardService.changeActiveCardBalance(cash);
        return true;
    }

    bool isActive() override
    {
        return getCashMenu.isActive();
    }

    void setActive(bool isActive) override
    {
        getCashMenu.setActive(isActive);
    }

    Menu& menu() override
    {
        return getCashMenu;
    }
};
