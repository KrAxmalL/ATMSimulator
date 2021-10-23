#pragma once
#include "Controller.h"
#include "MainMenu.h"
#include "EnterPinMenu.h"

class EnterPinController : public Controller
{

private:

    EnterPinMenu& enterPinMenu;
    MainMenu& mainMenu;

public:

    EnterPinController(RenderWindow& par, EnterPinMenu& enterPinMenu, MainMenu& mainMenu) : enterPinMenu(enterPinMenu), mainMenu(mainMenu) {}
    ~EnterPinController() {}

    virtual void handleEvent(const Event& event) override
    {
        switch (event.type)
        {
        case Event::TextEntered:
            //boxCardNum->typedOn(event);
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
            enterPinMenu.setActive(false);
            mainMenu.setActive(true);
        }
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

