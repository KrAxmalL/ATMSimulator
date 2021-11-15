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
        case Event::KeyPressed:
            if (Keyboard::isKeyPressed(sf::Keyboard::Enter) && getCash()) {
                gotoMenu();
            }
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
        if (getCashMenu.btnCancel.isMouseOver(event)) {
            getCashMenu.btnCancel.setBackColor(Assets::Instance().Grey);
        }
        else
        {
            getCashMenu.btnCancel.setBackColor(Color::White);
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
        if (getCashMenu.btnOkCash.isMouseOver(event) && getCash()) {
            gotoMenu();
        }
        else if (getCashMenu.btnCancel.isMouseOver(event)) {
            gotoMenu();
        }
        else if (getCashMenu.btnRemoveCash.isMouseOver(event)) {
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
        if (getCashMenu.getSum <= 1e-10) {
            getCashMenu.displayErrMessage("Cannot get zero money");
            return false;
        }

        double cash = -getCashMenu.getSum;
        std::cout << "cash: " << cash << std::endl;
        try {
            cardService.changeActiveCardBalance(cash);
        }
        catch (...) {
            getCashMenu.displayErrMessage("Not enough cash");
            return false;
        }
        
        return true;
    }

    void gotoMenu() {
        getCashMenu.clearSum();
        getCashMenu.setActive(false);
        mainMenu.setActive(true);
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
