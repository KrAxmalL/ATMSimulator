#pragma once
#include "Controller.h"
#include "MainMenu.h"
#include "EnterPinMenu.h"

class EnterPinController : public Controller
{

private:

    EnterPinMenu& enterPinMenu;
    MainMenu& mainMenu;
    StartMenu& startMenu;

    CardService& cardService;

public:

    EnterPinController(RenderWindow& par, EnterPinMenu& enterPinMenu, StartMenu& startMenu, MainMenu& mainMenu, CardService& cardService) : 
        enterPinMenu(enterPinMenu), mainMenu(mainMenu), startMenu(startMenu), cardService(cardService) {}
    ~EnterPinController() {}

    virtual void handleEvent(const Event& event) override
    {
        switch (event.type)
        {
        case Event::KeyPressed:
            if (Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                enterPinMenu.boxCardPin.setSelected(true);
            }
            else if (Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                enterPinMenu.boxCardPin.setSelected(false);
            } 
            else if (Keyboard::isKeyPressed(sf::Keyboard::Enter) && !enterPinMenu.boxCardPin.isSelecte()) {
                okButtonHandler();
            }
            break;
        case Event::TextEntered:
            if (Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                okButtonHandler();
            }
            enterPinMenu.boxCardPin.typedOn(event);
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

        if (enterPinMenu.btnOkPin.isMouseOver(event)) {
            enterPinMenu.btnOkPin.setBackColor(Assets::Instance().Grey);
        }
        else
        {
            enterPinMenu.btnOkPin.setBackColor(Color::White);
        }
    }

    void mouseButtonPressed(const Event& event) {
        if (enterPinMenu.btnOkPin.isMouseOver(event)) {
            okButtonHandler();
        }
    }

    void okButtonHandler() {
        if (cardService.isActiveCardBlocked()) {
            enterPinMenu.displayErrMessage("Your card is blocked");
        }

        try {
            if (readPin())
            {
                enterPinMenu.boxCardPin.clear();
                enterPinMenu.setActive(false);
                mainMenu.setActive(true);
                cardService.resetPin();
            }
            else
            {
                enterPinMenu.displayErrMessage("Pin is incorrect");
            }
        }
        catch (...) {
            cardService.resetPin();
            enterPinMenu.setActive(false);
            enterPinMenu.boxCardPin.clear();
            startMenu.setActive(true);
            startMenu.displayErrMessage("Card has been blocked");
        }

    }

    bool readPin()
    {
        std::string pinStr = enterPinMenu.boxCardPin.getText();
        if (pinStr.length() <= 0)
        {
            return false;
        }
        int pin = std::stoi(pinStr);
        bool isPinCorrect = cardService.correctPinForActiveCard(pin);
        
        std::cout << "Entered pin: " << pin << std::endl;
        std::cout << "Is correct pin: " << isPinCorrect << std::endl;

        return isPinCorrect;
    }

    bool isActive() override
    {
        return enterPinMenu.isActive();
    }

    void setActive(bool isActive) override
    {
        enterPinMenu.setActive(isActive);
    }

    Menu& menu() override
    {
        return enterPinMenu;
    }
};

