#pragma once
#include "Controller.h"
#include "EnterCardMenu.h"
#include "EnterPinMenu.h"
#include "CardService.h"

class EnterCardController : public Controller
{

private:

    EnterCardMenu& enterCardMenu;
    EnterPinMenu& enterPinMenu;

    CardService& cardService;

public:

    EnterCardController(RenderWindow& par, EnterCardMenu& enterCardMenu, EnterPinMenu& enterPinMenu, CardService& cardService) : enterCardMenu(enterCardMenu), enterPinMenu(enterPinMenu), cardService(cardService) {}
    ~EnterCardController() {}

    virtual void handleEvent(const Event& event) override
    {
        switch (event.type)
        {
        case Event::KeyPressed:
            if (Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                enterCardMenu.boxCardNum.setSelected(true);
            }
            else if (Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                enterCardMenu.boxCardNum.setSelected(false);
            }
            break;
            
        case Event::TextEntered:
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
            if (readCard())
            {
                enterCardMenu.setActive(false);
                enterPinMenu.setActive(true);
            }
            else
            {

            }
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
