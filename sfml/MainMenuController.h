#pragma once
#include "Controller.h"
#include "MainMenu.h"
#include "BalanceMenu.h"
#include "PutCashMenu.h"
#include "GetCashMenu.h"
#include "TransferMenu.h"
#include "RemoveCardMenu.h"
#include "ChangePinMenu.h"
#include "BankCard.h"

#include "CustomerService.h"

#include <vector>
#include "BlockCardMenu.h"

class MainMenuController : public Controller
{

private:

    MainMenu& mainMenu;
    BalanceMenu& balanceMenu;
    PutCashMenu& putCashMenu;
    GetCashMenu& getCashMenu;
    TransferMenu& transferMenu;
    TransactionsMenu& transactionsMenu;
    RemoveCardMenu& removeCardMenu;
    ChangePinMenu& changePinMenu;
    BlockCardMenu& blockCardMenu;

    CustomerService& customerService;

public:

    MainMenuController(RenderWindow& par, MainMenu& mainMenu, BalanceMenu& balanceMenu, PutCashMenu& putCashMenu, GetCashMenu& getCashMenu, TransferMenu& transferMenu, TransactionsMenu& transactionsMenu, RemoveCardMenu& removeCardMenu, ChangePinMenu& changePinMenu, BlockCardMenu& blockCardMenu, CustomerService& customerService)
        : mainMenu(mainMenu) 
        , balanceMenu(balanceMenu)
        , putCashMenu(putCashMenu)
        , getCashMenu(getCashMenu)
        , transferMenu(transferMenu),
        transactionsMenu(transactionsMenu) 
        , removeCardMenu(removeCardMenu)
        , changePinMenu(changePinMenu)
        , blockCardMenu(blockCardMenu)
        , customerService(customerService) {}
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
        if (mainMenu.getButtons()[4].isMouseOver(event)) {
            mainMenu.setActive(false);
            transactionsMenu.setActive(true);
        }
        if (mainMenu.getButtons()[5].isMouseOver(event)) {
            mainMenu.setActive(false);
            blockCardMenu.setActive(true);
        }
        if (mainMenu.getButtons()[6].isMouseOver(event)) {
            mainMenu.setActive(false);
            removeCardMenu.setActive(true);
        }
        if (mainMenu.getButtons()[7].isMouseOver(event)) {
            mainMenu.setActive(false);
            changePinMenu.setActive(true);
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
        const Customer& activeCustomer = customerService.getActiveCustomer();
        std::string fullName{ activeCustomer.getFName() + " " + activeCustomer.getSName() };
        mainMenu.areaWelcome.setText("Welcome, " + fullName);

        return mainMenu;
    }
};
