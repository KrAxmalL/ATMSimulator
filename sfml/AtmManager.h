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
        startMenuController(new StartMenuController(*window, startMenu, enterCardMenu)),
        enterCardController(new EnterCardController(*window, enterCardMenu, enterPinMenu)),
        enterPinController(new EnterPinController(*window, enterPinMenu, mainMenu)),
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
        for (auto controller: controllers)
        {
            if (controller->isActive()) return controller;
        }

        return startMenuController;
    }

    /*Menu* findActiveMenu()
{
    for (auto men : menus)
    {
        if (men -> isActive()) return men;
    }

    return &startMenu;
}*/

    /*void mouseButtonPressedActive() {
        if (startMenu.btnStart.isMouseOver(*window) && startMenu.isActive()) {
            //startMenu.setVisible(false);
            startMenu.setActive(false);
            //enterCardMenu.setVisible(true);
            enterCardMenu.setActive(true);
            
            
        }
        else if (enterCardMenu.btnOkCard.isMouseOver(*window) && enterCardMenu.isActive()) {
            enterCardMenu.areaCard.setText("Input PIN number");
            enterCardMenu.setActive(false);
            //enterCardMenu.setVisible(false);
            enterPinMenu.boxCardNum.clear();
            enterPinMenu.boxCardNum.setSecret(true);
            enterPinMenu.boxCardNum.setlimit(true, 4);
            enterPinMenu.setActive(true);
            //enterPinMenu.setVisible(true);
           
        }
        else if (enterPinMenu.btnOkPin.isMouseOver(*window) && enterPinMenu.isActive()) {
            enterPinMenu.setActive(false);
            //enterPinMenu.setVisible(true);
            mainMenu.setActive(true);
            //mainMenu.setVisible(true);
            


            /*btnf1->setVisible(true);
            btnf2->setVisible(true);
            btnf3->setVisible(true);
            btnf4->setVisible(true);

            btnf5->setVisible(true);
            btnf6->setVisible(true);
            btnf7->setVisible(true);
            btnf8->setVisible(true);
        }
        /*else if (btnf1->isMouseOver(*window)) {
            btnf1->setVisible(false);
            btnf2->setVisible(false);
            btnf3->setVisible(false);
            btnf4->setVisible(false);

            btnf5->setVisible(false);
            btnf6->setVisible(false);
            btnf7->setVisible(false);
            btnf8->setVisible(false);

            //action for button func1
        }
        else if (btnf2->isMouseOver(*window)) {
            /*btnf1->setVisible(false);
           btnf2->setVisible(false);
           btnf3->setVisible(false);
           btnf4->setVisible(false);

           btnf5->setVisible(false);
           btnf6->setVisible(false);
           btnf7->setVisible(false);
           btnf8->setVisible(false);

           //action for button func2
        }
        else if (btnf3->isMouseOver(*window)) {
            /*btnf1->setVisible(false);
           btnf2->setVisible(false);
           btnf3->setVisible(false);
           btnf4->setVisible(false);

           btnf5->setVisible(false);
           btnf6->setVisible(false);
           btnf7->setVisible(false);
           btnf8->setVisible(false);

           //action for button func3
        }
        else if (btnf4->isMouseOver(*window)) {
            /*btnf1->setVisible(false);
           btnf2->setVisible(false);
           btnf3->setVisible(false);
           btnf4->setVisible(false);

           btnf5->setVisible(false);
           btnf6->setVisible(false);
           btnf7->setVisible(false);
           btnf8->setVisible(false);

           //action for button func4
        }
        else if (btnf5->isMouseOver(*window)) {
            /*btnf1->setVisible(false);
            btnf2->setVisible(false);
            btnf3->setVisible(false);
            btnf4->setVisible(false);

            btnf5->setVisible(false);
            btnf6->setVisible(false);
            btnf7->setVisible(false);
            btnf8->setVisible(false);

            //action for button func5
        }
        else if (btnf6->isMouseOver(*window)) {
            /*btnf1->setVisible(false);
           btnf2->setVisible(false);
           btnf3->setVisible(false);
           btnf4->setVisible(false);

           btnf5->setVisible(false);
           btnf6->setVisible(false);
           btnf7->setVisible(false);
           btnf8->setVisible(false);
           //action for button func6
        }
        else if (btnf7->isMouseOver(*window)) {
            /*btnf1->setVisible(false);
            btnf2->setVisible(false);
            btnf3->setVisible(false);
            btnf4->setVisible(false);

            btnf5->setVisible(false);
            btnf6->setVisible(false);
            btnf7->setVisible(false);
            btnf8->setVisible(false);

            //action for button func7
            std::cout << "Controller called: " << controller->getData() << '\n';

        }
        else if (btnf8->isMouseOver(*window)) {
            /*btnf1->setVisible(false);
           btnf2->setVisible(false);
           btnf3->setVisible(false);
           btnf4->setVisible(false);

           btnf5->setVisible(false);
           btnf6->setVisible(false);
           btnf7->setVisible(false);
           btnf8->setVisible(false);

           //action for button func8
        }
    }*/

    /*void mouseButtonPressed() {
        if (startMenu.btnStart.isMouseOver(*window)) {
            startMenu.setVisible(false);
            enterCardMenu.setVisible(true);


        }
        else if (enterCardMenu.btnOkCard.isMouseOver(*window)) {
            enterCardMenu.areaCard.setText("Input PIN number");
            enterCardMenu.setVisible(false);
            enterPinMenu.boxCardNum.clear();
            enterPinMenu.boxCardNum.setSecret(true);
            enterPinMenu.boxCardNum.setlimit(true, 4);
            enterPinMenu.setVisible(true);


        }
        else if (enterPinMenu.btnOkPin.isMouseOver(*window)) {
            enterPinMenu.setVisible(false);
            mainMenu.setVisible(true);


            btnf1->setVisible(true);
            btnf2->setVisible(true);
            btnf3->setVisible(true);
            btnf4->setVisible(true);

            btnf5->setVisible(true);
            btnf6->setVisible(true);
            btnf7->setVisible(true);
            btnf8->setVisible(true);
        }
        /*else if (btnf1->isMouseOver(*window)) {
            btnf1->setVisible(false);
            btnf2->setVisible(false);
            btnf3->setVisible(false);
            btnf4->setVisible(false);

            btnf5->setVisible(false);
            btnf6->setVisible(false);
            btnf7->setVisible(false);
            btnf8->setVisible(false);

            //action for button func1
        }
        else if (btnf2->isMouseOver(*window)) {
            /*btnf1->setVisible(false);
           btnf2->setVisible(false);
           btnf3->setVisible(false);
           btnf4->setVisible(false);

           btnf5->setVisible(false);
           btnf6->setVisible(false);
           btnf7->setVisible(false);
           btnf8->setVisible(false);

           //action for button func2
        }
        else if (btnf3->isMouseOver(*window)) {
            /*btnf1->setVisible(false);
           btnf2->setVisible(false);
           btnf3->setVisible(false);
           btnf4->setVisible(false);

           btnf5->setVisible(false);
           btnf6->setVisible(false);
           btnf7->setVisible(false);
           btnf8->setVisible(false);

           //action for button func3
        }
        else if (btnf4->isMouseOver(*window)) {
            /*btnf1->setVisible(false);
           btnf2->setVisible(false);
           btnf3->setVisible(false);
           btnf4->setVisible(false);

           btnf5->setVisible(false);
           btnf6->setVisible(false);
           btnf7->setVisible(false);
           btnf8->setVisible(false);

           //action for button func4
        }
        else if (btnf5->isMouseOver(*window)) {
            /*btnf1->setVisible(false);
            btnf2->setVisible(false);
            btnf3->setVisible(false);
            btnf4->setVisible(false);

            btnf5->setVisible(false);
            btnf6->setVisible(false);
            btnf7->setVisible(false);
            btnf8->setVisible(false);

            //action for button func5
        }
        else if (btnf6->isMouseOver(*window)) {
            /*btnf1->setVisible(false);
           btnf2->setVisible(false);
           btnf3->setVisible(false);
           btnf4->setVisible(false);

           btnf5->setVisible(false);
           btnf6->setVisible(false);
           btnf7->setVisible(false);
           btnf8->setVisible(false);
           //action for button func6
        }
        else if (btnf7->isMouseOver(*window)) {
            /*btnf1->setVisible(false);
            btnf2->setVisible(false);
            btnf3->setVisible(false);
            btnf4->setVisible(false);

            btnf5->setVisible(false);
            btnf6->setVisible(false);
            btnf7->setVisible(false);
            btnf8->setVisible(false);

            //action for button func7
            std::cout << "Controller called: " << controller->getData() << '\n';

        }
        else if (btnf8->isMouseOver(*window)) {
            /*btnf1->setVisible(false);
           btnf2->setVisible(false);
           btnf3->setVisible(false);
           btnf4->setVisible(false);

           btnf5->setVisible(false);
           btnf6->setVisible(false);
           btnf7->setVisible(false);
           btnf8->setVisible(false);

           //action for button func8
        }
    }*/

};
