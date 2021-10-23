#pragma once
#include "Controller.h"
#include "EnterCardMenu.h"
#include "EnterPinMenu.h"

class EnterCardController : public Controller
{

private:

    EnterCardMenu& enterCardMenu;
    EnterPinMenu& enterPinMenu;

public:

    EnterCardController(RenderWindow& par, EnterCardMenu& enterCardMenu, EnterPinMenu& enterPinMenu) : enterCardMenu(enterCardMenu), enterPinMenu(enterPinMenu) {}
    ~EnterCardController() {}

    virtual void handleEvent(const Event& event) override
    {
        switch (event.type)
        {
        case Event::KeyPressed:
            if (Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                //enterCardMenu.box->setSelected(true);
            }
            else if (Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                //boxCardNum->setSelected(false);
                
            }
            break;
            
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
            enterCardMenu.setActive(false);
            enterPinMenu.setActive(true);
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
