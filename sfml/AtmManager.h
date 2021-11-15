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
#include "TransactionsMenu.h"

#include "CardService.h"
#include "TransactionService.h"

#include "StartMenuController.h"
#include "EnterCardController.h"
#include "EnterPinController.h"
#include "MainMenuController.h"
#include "BalanceMenuController.h"
#include "PutCashMenuController.h"
#include "GetCashMenuController.h"
#include "TransferController.h"
#include "TransactionsMenuController.h"
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
    TransactionsMenu transactionsMenu;
    std::vector<Menu*> menus;

    CardService cardService;
    TransactionService transactionService;

    StartMenuController* startMenuController;
    EnterCardController* enterCardController;
    EnterPinController* enterPinController;
    MainMenuController* mainMenuController;
    BalanceMenuController* balanceMenuController;
    PutCashMenuController* putCashMenuController;
    GetCashMenuController* getCashMenuController;
    TransferController* transferController;
    TransactionsMenuController* transactionsMenuController;
    std::vector<Controller*> controllers;

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
        transactionsMenu(*window),
        cardService{},
        transactionService(cardService),
        startMenuController(new StartMenuController(*window, startMenu, enterCardMenu)),
        enterCardController(new EnterCardController(*window, enterCardMenu, enterPinMenu, cardService)),
        enterPinController(new EnterPinController(*window, enterPinMenu, mainMenu, cardService)),
        mainMenuController(new MainMenuController(*window, mainMenu, balanceMenu, putCashMenu, getCashMenu, transferMenu, transactionsMenu)),
        balanceMenuController(new BalanceMenuController(*window, mainMenu, balanceMenu, cardService)),
        putCashMenuController(new PutCashMenuController(*window, mainMenu, putCashMenu, cardService)),
        getCashMenuController(new GetCashMenuController(*window, mainMenu, getCashMenu, cardService)),
        transferController(new TransferController(*window, mainMenu, transferMenu, transactionService, cardService)),
        transactionsMenuController(new TransactionsMenuController(*window, mainMenu, transactionsMenu, transactionService, cardService)),
        menus{&startMenu, &enterCardMenu, &enterPinMenu, &mainMenu, &balanceMenu, &putCashMenu, &getCashMenu, &transferMenu, &transactionsMenu },
        controllers{startMenuController, enterCardController, enterPinController, mainMenuController, 
        balanceMenuController, putCashMenuController, getCashMenuController, transferController, transactionsMenuController }
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
        Controller* activeController = nullptr;
        while (window->isOpen())
        {
            // todo: approve
            std::this_thread::sleep_for(std::chrono::milliseconds{ 20 });
            Event event;

            activeController = findActiveController();
            while (window->pollEvent(event))
            {
                if (event.type == Event::Closed)
                {
                    window -> close();
                }
                else
                {
                    if (event.type == Event::TextEntered) 
                        cout << "enter text" << endl;
                    if (event.type == Event::KeyPressed)
                        cout << "key pressed" << endl;
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
            if (controller->isActive()) 
                return controller;
        }

        return startMenuController;
    }
};
