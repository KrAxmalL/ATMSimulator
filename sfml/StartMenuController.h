#pragma once
#include "Controller.h"
#include "StartMenu.h"

class StartMenuController : public Controller
{

private:
    StartMenu& startMenu;
    EnterCardMenu& enterCardMenu;

    RenderWindow& window;

public:

    StartMenuController(RenderWindow& par, StartMenu& startMenu, EnterCardMenu& enterCardMenu) : window(window), startMenu(startMenu), enterCardMenu(enterCardMenu) {}
	~StartMenuController() {}

	virtual void handleEvent(const Event& event) override
	{
        switch (event.type)
        {
        case Event::MouseMoved:
            mouseMoved(event);
            break;
        case Event::MouseButtonPressed:
            std::cout << "Mouse pressed!: " << std::endl;
            mouseButtonPressed(event);
            break;
        }
	}

    void mouseMoved(const Event& event) {

        if (startMenu.btnStart.isMouseOver(event)) {
            startMenu.btnStart.setBackColor(Assets::Instance().Grey);
        }
        else
        {
            startMenu.btnStart.setBackColor(Color::White);
        }
    }

    void mouseButtonPressed(const Event& event) {
        if (startMenu.btnStart.isMouseOver(event)) {
            startMenu.setActive(false);
            enterCardMenu.setActive(true);
            enterCardMenu.setVisible(true);
            std::cout << "EnterCardMenu is active: " << enterCardMenu.isActive() << std::endl;
        }
    }

    bool isActive() override
    {
        return startMenu.isActive();
    }

    void setActive(bool isActive) override
    {
        startMenu.setActive(isActive);
    }

    Menu& menu() override
    {
        return startMenu;
    }
};