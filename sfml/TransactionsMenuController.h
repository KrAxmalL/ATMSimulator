#pragma once
#ifndef TRANSACTIONSMENUCONTROLLER_H
#define TRANSACTIONSMENUCONTROLLER_H

#include "Controller.h"
#include "MainMenu.h"
#include "TransactionsMenu.h"

class TransactionsMenuController : public Controller 
{
private:
	MainMenu& mainMenu;
    TransactionsMenu& transactionsMenu;

	TransactionService& transactionService;
	CardService& cardService;

    vector<Transaction>* transactions = nullptr;

    bool requiresUpdate;

    size_t currentPage;
    size_t totalPageNumber;
    const size_t TRANSACTIONS_PER_PAGE = 6;

    void mouseButtonPressed(const Event& event) {
        if (transactionsMenu.btnOk.isMouseOver(event)) {
            gotoMenu();
        }
        else if (transactionsMenu.btnNextPage.isMouseOver(event)) {
            if (currentPage < totalPageNumber - 1) {
                ++currentPage;
                requiresUpdate = true;
            }
        }
        else if (transactionsMenu.btnPrevPage.isMouseOver(event)) {
            if (currentPage > 0) {
                --currentPage;
                requiresUpdate = true;
            }
        }
    }

    void mouseMoved(const Event& event) {

        if (transactionsMenu.btnOk.isMouseOver(event)) {
            transactionsMenu.btnOk.setBackColor(Assets::Instance().Grey);
        }
        else
        {
            transactionsMenu.btnOk.setBackColor(Color::White);
        }
        if (transactionsMenu.btnNextPage.isMouseOver(event)) {
            transactionsMenu.btnNextPage.setBackColor(Assets::Instance().Grey);
        }
        else
        {
            transactionsMenu.btnNextPage.setBackColor(Color::White);
        }
        if (transactionsMenu.btnPrevPage.isMouseOver(event)) {
            transactionsMenu.btnPrevPage.setBackColor(Assets::Instance().Grey);
        }
        else
        {
            transactionsMenu.btnPrevPage.setBackColor(Color::White);
        }
    }

    void gotoMenu() {
        delete transactions;
        transactions = nullptr;
        requiresUpdate = true;
        transactionsMenu.setActive(false);
        mainMenu.setActive(true);
    }

    void updatePageNumber() {
        transactionsMenu.pageNum.setText(to_string(currentPage + 1) + "/" + to_string(totalPageNumber));
    }
public:
	TransactionsMenuController(RenderWindow& par, MainMenu& mainMenu, TransactionsMenu& transacationsMenu, TransactionService& transactionService, CardService& cardService) :
		mainMenu(mainMenu), transactionService(transactionService), cardService(cardService), transactionsMenu(transacationsMenu), requiresUpdate(true) {}
	~TransactionsMenuController() {}

    virtual void handleEvent(const Event& event) override
    {
        switch (event.type)
        {
        case Event::MouseButtonPressed:
            mouseButtonPressed(event);
            break;
        case Event::MouseMoved:
            mouseMoved(event);
            break;
        case Event::KeyPressed:
            if (Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                gotoMenu();
            }
            break;
        }
    }

    bool isActive() override
    {
        return transactionsMenu.isActive();
    }

    void setActive(bool isActive) override
    {
        transactionsMenu.setActive(isActive);
    }

    Menu& menu() override
    {
        if (requiresUpdate) {
            if (transactions == nullptr) {
                transactions = new vector<Transaction>(transactionService.getTransactionsOf(cardService.getActiveCard().getId()));
                currentPage = 0;
                totalPageNumber = transactions->size() / TRANSACTIONS_PER_PAGE + 1;
            }
            
            transactionIter end = currentPage == totalPageNumber - 1 ? transactions->end() : transactions->begin() + currentPage * 6 + 6;
            transactionsMenu.transactionsListView = TransactionsListView(transactions->begin() + currentPage*6, end);
            
            updatePageNumber();
            requiresUpdate = false;
        }
        return transactionsMenu;
    }
};


#endif
