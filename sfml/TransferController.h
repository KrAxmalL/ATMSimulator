#pragma once
#include "Controller.h"
#include "MainMenu.h"
#include "TransferMenu.h"

class TransferController : public Controller
{

private:

    MainMenu& mainMenu;
    TransferMenu& transferMenu;

    TransactionService& transactionService;

public:

    TransferController(RenderWindow& par, MainMenu& mainMenu, TransferMenu& transferMenu, TransactionService& transactionService) : mainMenu(mainMenu), transferMenu(transferMenu), transactionService(transactionService) {}
    ~TransferController() {}

    virtual void handleEvent(const Event& event) override
    {
        switch (event.type)
        {
        case Event::KeyPressed:
            if (Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                if (transferMenu.boxCardNum.isSelecte()) {
                    transferMenu.boxCardNum.setSelected(false);
                }
                if (transferMenu.boxAmount1.isSelecte()) {
                    transferMenu.boxAmount1.setSelected(false);
                }
                if (transferMenu.boxAmount2.isSelecte()) {
                    transferMenu.boxAmount2.setSelected(false);
                }
            }
            //else if (Keyboard::isKeyPressed(sf::Keyboard::Escape))
            //{
            //   transferMenu.boxCardNum.setSelected(false);
            //}
            break;
        case Event::TextEntered:
            transferMenu.boxCardNum.typedOn(event);
            transferMenu.boxAmount1.typedOn(event);
            transferMenu.boxAmount2.typedOn(event);
            break;
        case Event::MouseMoved:
            mouseMoved(event);
            break;
        case Event::MouseButtonPressed:
            mouseButtonPressed(event);
            break;
        }
    }

    void mouseMoved(const Event& event) {

        if (transferMenu.btnSend.isMouseOver(event)) {
            transferMenu.btnSend.setBackColor(Assets::Instance().Grey);
        }
        else
        {
            transferMenu.btnSend.setBackColor(Color::White);
        }
    }

    void mouseButtonPressed(const Event& event) {
        if (transferMenu.btnSend.isMouseOver(event)) {
            transferMenu.boxCardNum.clear();
            transferMenu.boxAmount1.clear();
            transferMenu.boxAmount2.clear();
            transferMenu.setActive(false);
            mainMenu.setActive(true);
        }
        if (transferMenu.boxCardNum.isMouseOver(event)) {
            transferMenu.boxCardNum.setSelected(true);
        }
        if (transferMenu.boxAmount1.isMouseOver(event)) {
            transferMenu.boxAmount1.setSelected(true);
        }
        if (transferMenu.boxAmount2.isMouseOver(event)) {
            transferMenu.boxAmount2.setSelected(true);
        }
    }

    bool isActive() override
    {
        return transferMenu.isActive();
    }

    void setActive(bool isActive) override
    {
        transferMenu.setActive(isActive);
    }

    Menu& menu() override
    {
        return transferMenu;
    }
};
