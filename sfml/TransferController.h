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
    CardService& cardService;

    // todo: temp
    template<class T>
    void unselect(T& drawable) {
        if (drawable.isSelecte()) {
            drawable.setSelected(false);
        }
    }

public:

    TransferController(RenderWindow& par, MainMenu& mainMenu, TransferMenu& transferMenu, TransactionService& transactionService, CardService& cardService) : 
        mainMenu(mainMenu), transferMenu(transferMenu), transactionService(transactionService), cardService(cardService) {}
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
            if (Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                sendButtonHandler();
            }
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
            sendButtonHandler();
        }
        else if (transferMenu.btnCancel.isMouseOver(event)) {
            returnToMenu();
        }
        else if (transferMenu.boxCardNum.isMouseOver(event)) {
            transferMenu.boxCardNum.setSelected(true);
            unselect(transferMenu.boxAmount2);
            unselect(transferMenu.boxAmount1);
        }
        else if (transferMenu.boxAmount1.isMouseOver(event)) {
            transferMenu.boxAmount1.setSelected(true);
            unselect(transferMenu.boxCardNum);
            unselect(transferMenu.boxAmount2);
        }
        else if (transferMenu.boxAmount2.isMouseOver(event)) {
            transferMenu.boxAmount2.setSelected(true);
            unselect(transferMenu.boxCardNum);
            unselect(transferMenu.boxAmount1);
        }
    }

    void sendButtonHandler() {
        // todo: refactor
        try {
            if (performTransaction()) {
                returnToMenu();
            }
            else
                transferMenu.displayErrMessage("Invalid data");
        }
        catch (int e) {
            switch (e) {
            case -1:
                transferMenu.displayErrMessage("Invalid cards numbers");
                break;
            case -2:
                transferMenu.displayErrMessage("Cannot make transaction on your own card");
                break;
            case -3:
                transferMenu.displayErrMessage("Your card is blocked");
                break;
            case -4:
                transferMenu.displayErrMessage("Destination card is blocked");
                break;
            case -5:
                transferMenu.displayErrMessage("Not enough money");
                break;
            }
        }
        
    }

    bool performTransaction()
    {
        std::string cardToStr = transferMenu.boxCardNum.getText();
        std::cout << "card to: " << cardToStr << std::endl;
        if (cardToStr.empty())
        {
            return false;
        }

        int cardTo = std::atoi(cardToStr.c_str());
        if (!cardService.cardExists(cardTo))
            return false;

        double amountInt = std::atoi(transferMenu.boxAmount1.getText().c_str());
        double amountDec = std::atoi(transferMenu.boxAmount2.getText().c_str());
        amountDec /= 100;
        double finAmount = amountInt + amountDec;

        // todo: something like spinner 
        // "please wait, transaction is in progress"
        transactionService.transactionFromActiveCard(cardTo, finAmount);

        return true;
    }

    void returnToMenu() {
        transferMenu.boxCardNum.clear();
        transferMenu.boxAmount1.clear();
        transferMenu.boxAmount2.clear();
        transferMenu.setActive(false);
        mainMenu.setActive(true);
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
