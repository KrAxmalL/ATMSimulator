#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "TextBox.h"
#include "TextArea.h"
#include "Controller.h"
#include "MainMenu.h"
#include "BalanceMenu.h"
#include "PutCashMenu.h"
#include "GetCashMenu.h"
#include "StartMenu.h"
#include "EnterCardMenu.h"
#include "EnterPinMenu.h"
#include "TransferMenu.h"

#include "StartMenuController.h"
#include "EnterCardController.h"
#include "EnterPinController.h"
#include "MainMenuController.h"
#include "BalanceMenuController.h"
#include "PutCashMenuController.h"
#include "GetCashMenuController.h"
#include "TransferController.h"
#include "vector"

using namespace sf;

class AtmManager {

private:

    RenderWindow* window;

    MainMenu mainMenu;
    
    StartMenu startMenu;
    EnterCardMenu enterCardMenu;
    EnterPinMenu enterPinMenu;
    BalanceMenu balanceMenu;
    PutCashMenu putCashMenu;
    GetCashMenu getCashMenu;
    TransferMenu transferMenu;
    std::vector<Menu*> menus;

    StartMenuController* startMenuController;
    EnterCardController* enterCardController;
    EnterPinController* enterPinController;
    MainMenuController* mainMenuController;
    BalanceMenuController* balanceMenuController;
    PutCashMenuController* putCashMenuController;
    GetCashMenuController* getCashMenuController;
    TransferController* transferController;
    std::vector<Controller*> controllers;

    CardService cardService;

	void init() {
       for (auto& menu : menus)
       {
            menu->setVisible(true);
            menu->setActive(false);
       }

       for (auto& controller : controllers)
       {
           controller -> setActive(false);
       }
  
       startMenuController->setActive(true);
	}

public: 
    AtmManager(): window(new RenderWindow(VideoMode(1000, 750), "SFML works!")), mainMenu(*window), 
        startMenu(*window), 
        balanceMenu(*window),
        putCashMenu(*window),
        getCashMenu(*window),
        enterCardMenu(*window), 
        enterPinMenu(*window),
        transferMenu(*window),
        cardService{},
        startMenuController(new StartMenuController(*window, startMenu, enterCardMenu)),
        enterCardController(new EnterCardController(*window, enterCardMenu, enterPinMenu, cardService)),
        enterPinController(new EnterPinController(*window, enterPinMenu, mainMenu, cardService)),
        mainMenuController(new MainMenuController(*window, mainMenu, balanceMenu, putCashMenu, getCashMenu, transferMenu)),
        balanceMenuController(new BalanceMenuController(*window, mainMenu, balanceMenu)),
        putCashMenuController(new PutCashMenuController(*window, mainMenu, putCashMenu)),
        getCashMenuController(new GetCashMenuController(*window, mainMenu, getCashMenu)),
        transferController(new TransferController(*window, mainMenu, transferMenu)),
        menus{&startMenu, &enterCardMenu, &enterPinMenu, &mainMenu, &balanceMenu, &putCashMenu, &getCashMenu, &transferMenu },
        controllers{startMenuController, enterCardController, enterPinController, mainMenuController, balanceMenuController, putCashMenuController, getCashMenuController, transferController }
    {
        init();
    }

	~AtmManager() { 

        delete startMenuController;
        delete enterCardController;
        delete enterPinController;
        delete mainMenuController;
        delete balanceMenuController;
        delete putCashMenuController;
        delete getCashMenuController;
        delete transferController;
        delete window;
    }

    void start() {
        // ---Program Cycle---
            //findActiveController - find current active controller
            //activeController.handleEvent(event) - complete action for current event
            //findActiveController - if event has changed view - need to find new active controller
            //draw current active menu
        // ---Program Cycle---
        while (window->isOpen())
        {
            Event event;

            Controller* activeController = findActiveController();
            while (window->pollEvent(event))
            {
                if (event.type == Event::Closed)
                {
                    window -> close();
                }
                else
                {
                    activeController->handleEvent(event);
                    activeController = findActiveController();
                }
            }
            window->clear();
            window->draw(Assets::Instance().background);
            window->draw(activeController->menu());
            window->display();
        }
    }

    Controller* findActiveController()
    {
        for (auto& controller: controllers)
        {
            if (controller->isActive()) return controller;
        }

        return startMenuController;
    }
};
