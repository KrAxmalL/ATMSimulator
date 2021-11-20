#pragma once
#include "Controller.h"
#include "EnterCardMenu.h"
#include "EnterPinMenu.h"
#include "CardService.h"
#include "CustomerService.h"

class EnterCardController : public Controller
{

private:

    EnterCardMenu& enterCardMenu;
    EnterPinMenu& enterPinMenu;

    CardService& cardService;
    CustomerService& customerService;

public:

    EnterCardController(RenderWindow& par, EnterCardMenu& enterCardMenu, EnterPinMenu& enterPinMenu, CardService& cardService, CustomerService& customerService) : enterCardMenu(enterCardMenu), enterPinMenu(enterPinMenu), cardService(cardService), customerService(customerService) {}
    ~EnterCardController() {}

    virtual void handleEvent(const Event& event) override
    {
        switch (event.type)
        {
        case Event::KeyPressed:
            keyPressed(event);
            break;
            
        case Event::TextEntered:
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                okButtonHandler();
            }
            enterCardMenu.boxCardNum.typedOn(event);
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

        if (enterCardMenu.btnOkCard.isMouseOver(event)) {
            enterCardMenu.btnOkCard.setBackColor(Assets::Instance().Grey);
        }
        else
        {
            enterCardMenu.btnOkCard.setBackColor(Color::White);
        }
    }

    void mouseButtonPressed(const Event& event) {
        if (enterCardMenu.btnOkCard.isMouseOver(event)) {
            okButtonHandler();
        }
    }

    void okButtonHandler() {
        if (readCard())
        {
            enterCardMenu.boxCardNum.clear();
            enterCardMenu.setActive(false);
            enterPinMenu.setActive(true);
        }
        else
        {
            enterCardMenu.displayErrMessage("Card number is invalid.");
        }
    }

    void keyPressed(const Event& event) {

        if (Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            enterCardMenu.boxCardNum.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            enterCardMenu.boxCardNum.setSelected(false);
        }
        // second check is cause TextEntered triggers right after this one (to handle 'enter' there)
        // todo: test if err message appeares when cardNumInput loses(somehow) focus
        else if (Keyboard::isKeyPressed(sf::Keyboard::Enter) && !enterCardMenu.boxCardNum.isSelecte()) {
            okButtonHandler();
        }
    }

    bool readCard()
    {
       
        std::string cardNumStr = enterCardMenu.boxCardNum.getText();
        if (cardNumStr.length() <= 0)
        {
            return false;
        }

        int cardNum = std::stoi(cardNumStr);
        if (cardService.cardExists(cardNum))
        {
            cardService.makeActiveCard(cardNum);
            if (!cardService.isActiveCardBlocked())
            {
                customerService.makeActiveCustomer();
                return true;
            }
            else
            {
                //message box that card is blocked
                //maybe also show block expire date
                return false;
            }
        }
        else
        {
            //message box that wrong card number
            return false;
        }

    }

    bool isActive() override
    {
        return enterCardMenu.isActive();
    }

    void setActive(bool isActive) override
    {
        enterCardMenu.setActive(isActive);
    }

    Menu& menu() override
    {
        return enterCardMenu;
    }
};
