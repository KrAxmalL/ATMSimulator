#pragma once
#include "Controller.h"
#include "MainMenu.h"
#include "ChangePinMenu.h"
#include "CardService.h"

class ChangePinMenuController : public Controller
{
private:

    MainMenu& mainMenu;
    ChangePinMenu& changePinMenu;

    CardService& cardService;

    // todo: temp
    template<class T>
    void unselect(T& drawable) {
        if (drawable.isSelecte()) {
            drawable.setSelected(false);
        }
    }

public:

    ChangePinMenuController(RenderWindow& par, MainMenu& mainMenu, ChangePinMenu& changePinMenu, CardService& cardService) :
        mainMenu(mainMenu), changePinMenu(changePinMenu), cardService(cardService) {}
    ~ChangePinMenuController() {}

    virtual void handleEvent(const Event& event) override
    {
        switch (event.type)
        {
        case Event::KeyPressed:
            if (Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                if (changePinMenu.boxOldCardPin.isSelecte()) {
                    changePinMenu.boxOldCardPin.setSelected(false);
                }
                if (changePinMenu.boxNewCardPin.isSelecte()) {
                    changePinMenu.boxNewCardPin.setSelected(false);
                }
                if (changePinMenu.boxNewCardPinRepeat.isSelecte()) {
                    changePinMenu.boxNewCardPinRepeat.setSelected(false);
                }
            }
            break;

        case Event::TextEntered:
            if (Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                changeButtonHandler();
            }
            changePinMenu.boxOldCardPin.typedOn(event);
            changePinMenu.boxNewCardPin.typedOn(event);
            changePinMenu.boxNewCardPinRepeat.typedOn(event);
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

        if (changePinMenu.btnOk.isMouseOver(event)) {
            changePinMenu.btnOk.setBackColor(Assets::Instance().Grey);
        }
        else
        {
            changePinMenu.btnOk.setBackColor(Color::White);
        }
        if (changePinMenu.btnCancel.isMouseOver(event)) {
            changePinMenu.btnCancel.setBackColor(Assets::Instance().Grey);
        }
        else
        {
            changePinMenu.btnCancel.setBackColor(Color::White);
        }
    }

    void mouseButtonPressed(const Event& event) {
        if (changePinMenu.btnOk.isMouseOver(event)) {
            changeButtonHandler();
        }
        else if (changePinMenu.btnCancel.isMouseOver(event)) {
            gotoMenu();
        }
        else if (changePinMenu.boxOldCardPin.isMouseOver(event)) {
            changePinMenu.boxOldCardPin.setSelected(true);
            unselect(changePinMenu.boxNewCardPin);
            unselect(changePinMenu.boxNewCardPinRepeat);
        }
        else if (changePinMenu.boxNewCardPin.isMouseOver(event)) {
            changePinMenu.boxNewCardPin.setSelected(true);
            unselect(changePinMenu.boxOldCardPin);
            unselect(changePinMenu.boxNewCardPinRepeat);
        }
        else if (changePinMenu.boxNewCardPinRepeat.isMouseOver(event)) {
            changePinMenu.boxNewCardPinRepeat.setSelected(true);
            unselect(changePinMenu.boxOldCardPin);
            unselect(changePinMenu.boxNewCardPin);
        }
    }

    void changeButtonHandler() {
        try {
            changePin();
            gotoMenu();
        }
        catch (const std::exception& ex) {
            std::cout << "changePinEx: " << ex.what() << std::endl;
            changePinMenu.displayErrMessage(ex.what());
        }
    }

    void changePin()
    {
        //todo - fix bug with input of pins in changePinMenu
        if (changePinMenu.boxOldCardPin.getText().length() < 4)
        {
            throw std::exception("Old pin length must be 4!");
        }
        if (changePinMenu.boxNewCardPin.getText().length() < 4)
        {
            throw std::exception("New pin length must be 4!");
        }
        if (changePinMenu.boxNewCardPinRepeat.getText().length() < 4)
        {
            throw std::exception("Repeated pin length must be 4!");
        }

        int oldPin = std::atoi(changePinMenu.boxOldCardPin.getText().c_str());
        int newPin = std::atoi(changePinMenu.boxNewCardPin.getText().c_str());
        int newPinRepeat = std::atoi(changePinMenu.boxNewCardPinRepeat.getText().c_str());

        if (oldPin != cardService.getActiveCard().getPin())
        {
            throw std::exception("Incorrect old pin!");
        }

        if (newPin == oldPin)
        {
            throw std::exception("New pin can't be the same as old pin!");
        }

        if (newPin != newPinRepeat)
        {
            throw std::exception("New pin and repeated pin are not equal!");
        }

        cardService.changeActiveCardPin(newPin);
    }

    void gotoMenu() {
        changePinMenu.boxOldCardPin.clear();
        changePinMenu.boxNewCardPin.clear();
        changePinMenu.boxNewCardPinRepeat.clear();
        changePinMenu.setActive(false);
        mainMenu.setActive(true);
    }

    bool isActive() override
    {
        return changePinMenu.isActive();
    }

    void setActive(bool isActive) override
    {
        changePinMenu.setActive(isActive);
    }

    Menu& menu() override
    {
        return changePinMenu;
    }
};
