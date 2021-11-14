#pragma once
#include "Controller.h"
#include "MainMenu.h"
#include "BalanceMenu.h"

class BalanceMenuController : public Controller
{

private:
    
        MainMenu& mainMenu;
        BalanceMenu& balanceMenu;

        CardService& cardService;

public:

    BalanceMenuController(RenderWindow& par, MainMenu& mainMenu, BalanceMenu& balanceMenu, CardService& cardService) : mainMenu(mainMenu), balanceMenu(balanceMenu), cardService(cardService) {}
    ~BalanceMenuController() {}

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

        if (balanceMenu.btnOkBalance.isMouseOver(event)) {
            balanceMenu.btnOkBalance.setBackColor(Assets::Instance().Grey);
        }
        else
        {
            balanceMenu.btnOkBalance.setBackColor(Color::White);
        }
    }

    void mouseButtonPressed(const Event& event) {
        if (balanceMenu.btnOkBalance.isMouseOver(event)) {
            balanceMenu.setActive(false);
            mainMenu.setActive(true);
        }
    }

    bool isActive() override
    {
        return balanceMenu.isActive();
    }

    void setActive(bool isActive) override
    {
        balanceMenu.setActive(isActive);
    }

    Menu& menu() override
    {
        if (isActive())
        {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << cardService.getActiveCard().getBalance();
            balanceMenu.areaBalance.setText("BALANCE:\n\n" + stream.str());
            //std::cout << "Text in balanceMenu: " << balanceMenu.areaBalance.getText() << endl;
        }
        return balanceMenu;
    }
};
