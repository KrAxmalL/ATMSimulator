#pragma once
#include "Controller.h"
#include "MainMenu.h"
#include "RemoveCardMenu.h"
#include "StartMenu.h"

class RemoveCardMenuController : public Controller
{
private:
    MainMenu& mainMenu;
    RemoveCardMenu& removeCardMenu;
    StartMenu& startMenu;

    RenderWindow& window;

public:

    RemoveCardMenuController(RenderWindow& par, MainMenu& mainMenu, RemoveCardMenu& removeCardMenu, StartMenu& startMenu) : window(par), mainMenu(mainMenu), removeCardMenu(removeCardMenu), startMenu(startMenu)  {}
    ~RemoveCardMenuController() {}

    void handleEvent(const Event& event) override
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
        if (removeCardMenu.btnOk.isMouseOver(event)) {
            removeCardMenu.btnOk.setBackColor(Assets::Instance().Grey);
        }
        else
        {
            removeCardMenu.btnOk.setBackColor(Color::White);
        }
        if (removeCardMenu.btnCancel.isMouseOver(event)) {
            removeCardMenu.btnCancel.setBackColor(Assets::Instance().Grey);
        }
        else
        {
            removeCardMenu.btnCancel.setBackColor(Color::White);
        }
    }

    void mouseButtonPressed(const Event& event) {
        if (removeCardMenu.btnCancel.isMouseOver(event)) {
            removeCardMenu.setActive(false);
            mainMenu.setActive(true);
        }
        if (removeCardMenu.btnOk.isMouseOver(event))
        {
            removeCardMenu.setActive(false);
            startMenu.setActive(true);
        }
    }

    bool isActive() override
    {
        return removeCardMenu.isActive();
    }

    void setActive(bool isActive) override
    {
        removeCardMenu.setActive(isActive);
    }

    Menu& menu() override
    {
        return removeCardMenu;
    }
};
