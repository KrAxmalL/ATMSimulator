#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Controller.h"
#include "MainMenu.h"
#include "RemoveCardMenu.h"
#include "StartMenu.h"
#include "BlockCardMenu.h"
#include "CardService.h"

class BlockCardMenuController : public Controller
{
private:
    MainMenu& mainMenu;
    BlockCardMenu& blockCardMenu;
    StartMenu& startMenu;
    CardService& cardService;

    RenderWindow& window;

public:

    BlockCardMenuController(RenderWindow& par, MainMenu& mainMenu, BlockCardMenu& blockCardMenu, StartMenu& startMenu, CardService& cardService) :
        window(par), mainMenu(mainMenu), blockCardMenu(blockCardMenu), startMenu(startMenu), cardService(cardService) {}
    ~BlockCardMenuController() {}

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
        if (blockCardMenu.btnOk.isMouseOver(event)) {
            blockCardMenu.btnOk.setBackColor(Assets::Instance().Grey);
        }
        else
        {
            blockCardMenu.btnOk.setBackColor(Color::White);
        }
        if (blockCardMenu.btnCancel.isMouseOver(event)) {
            blockCardMenu.btnCancel.setBackColor(Assets::Instance().Grey);
        }
        else
        {
            blockCardMenu.btnCancel.setBackColor(Color::White);
        }
    }

    void mouseButtonPressed(const Event& event) {
        if (blockCardMenu.btnCancel.isMouseOver(event)) {
            blockCardMenu.setActive(false);
            mainMenu.setActive(true);
        }
        if (blockCardMenu.btnOk.isMouseOver(event))
        {
            std::time_t t = std::time(0);   // get time now
            std::tm* now = std::localtime(&t);
            std::tm expire = *now;
            expire.tm_year += 50;
            
            cardService.blockActiveCard(expire);
            blockCardMenu.setActive(false);
            startMenu.setActive(true);
        }
    }

    bool isActive() override
    {
        return blockCardMenu.isActive();
    }

    void setActive(bool isActive) override
    {
        blockCardMenu.setActive(isActive);
    }

    Menu& menu() override
    {
        return blockCardMenu;
    }
};
