#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include "BankCard.h"
#include "CardRepository.h"

class CardService
{
private:
	CardRepository cardRepository;
	BankCard* activeCard;

	int wrongPinCounter;

	static const int pinAttempts = 3;

public:

	explicit CardService(): cardRepository(), activeCard(nullptr), wrongPinCounter(0) {}

	~CardService() { delete activeCard; }

	bool isCardBlocked(const BankCard& card)
	{
		return card.isBlocked();
		//if (card.isBlocked())
		//{
		//	/*
		//		if(card.getExpireDay())
		//		if current date is bigger than expire block date - unblock card and return false;
		//		else return true
		//		*/
		//}
		//else
		//{
		//	return false;
		//}
	}

	bool cardExists(int cardNum)
	{
		return cardRepository.cardExists(cardNum);
	}

	void makeActiveCard(int cardNum)
	{
		delete activeCard;
		activeCard = new BankCard(cardRepository.getCard(cardNum));
	}

	bool isActiveCardBlocked()
	{
		checkExpireDate(*activeCard);
		return activeCard->isBlocked();
	}

	void checkActiveCardExpireDate()
	{
		checkExpireDate(*activeCard);
	}

	void checkExpireDate(BankCard& bc) {
		if (bc.isBlocked()) {
			std::time_t t = std::time(0);
			std::tm* now = std::localtime(&t);// get time now
			std::tm copy = bc.getExpireDay();
			++copy.tm_hour;

			if (difftime(mktime(now), mktime(&copy)) >= 0.0) {
				activeCard->setExpireDay({ 0 });
				activeCard->setBlocked(false);

				cardRepository.deleteCard(bc.getId());
				cardRepository.addCard(bc);
			}
		}
	}

	bool correctPinForActiveCard(int pin)
	{
		std::cout << "Active card pin: " << activeCard->getPin() << std::endl;
		std::cout << "Pin to check: " << pin << std::endl;
		bool isCorrectPin = activeCard->getPin() == pin;
		if (!isCorrectPin)
		{
			++wrongPinCounter;

			if (wrongPinCounter == pinAttempts)
			{
				std::time_t t = std::time(0);   // get time now
				std::tm* now = std::localtime(&t);
				std::tm expire = *now;
				// note: change to fasten
				expire.tm_sec += 20;
				time_t expire_t = mktime(&expire);
				expire = *std::localtime(&expire_t);

				blockCard(*activeCard, expire);
				cout << "somthientg" << endl;
				throw - 1;
				//show message that card is blocked
			}
		}
		return isCorrectPin;
	}

	void blockActiveCard(tm& expire)
	{
		blockCard(*activeCard, expire);
	}

	void blockCard(BankCard& card, tm& expire)
	{
		if (!isCardBlocked(card))
		{
			card.setBlocked(true);

			std::time_t t = std::time(0);   // get time now
			std::tm* now = std::localtime(&t);

			card.setBlockStartDate(*now);
			card.setExpireDay(expire);

			cardRepository.deleteCard(card.getId());
			cardRepository.addCard(card);
			//cardRepository.updateCard(card); replace with delete and add
		}
	}

	const BankCard& getActiveCard()
	{
		if (activeCard != nullptr)
		{
			return *activeCard;
		}
		else
		{
			//exception
		}
	}

	void processInsertedCard(int cardNum, int pin)
	{
		if (cardRepository.cardExists(cardNum)) {

			BankCard dbCard = cardRepository.getCard(cardNum);
			if (!isCardBlocked(dbCard))
			{
				if (dbCard.getPin() == pin)
				{
					activeCard = new BankCard(dbCard);
				}
				else
				{
					//show menu that pin is invalid
					++wrongPinCounter;
					if (wrongPinCounter == pinAttempts)
					{
						std::time_t t = std::time(0);   // get time now
						std::tm* now = std::localtime(&t);
						std::tm expire = *now;
						// note: change to fasten
						expire.tm_sec += 20;

						blockCard(dbCard, expire);
						//show message that card is blocked
					}
				}
			}
			else
			{
				//error message
			}
		}
		else
		{
			//error message
		}
	}

	BankCard getCard(int cardNum)
	{
		if (cardRepository.cardExists(cardNum))
		{
			return cardRepository.getCard(cardNum);
		}
		else
		{
			throw - 1;
		}
	}

	void changeActiveCardBalance(double sum)
	{
		//changeBalance(*activeCard, sum);
		double newBalance = activeCard->getBalance() + sum;
		if (newBalance < 0)
		{
			throw - 1;
		}
		else
		{
			activeCard->setBalance(newBalance);
			cout << activeCard << endl;
			cardRepository.deleteCard(activeCard->getId());
			cardRepository.addCard(*activeCard);
		}
	}

	void changeActiveCardPin(int newPin)
	{
		activeCard->setPin(newPin);
		cardRepository.deleteCard(activeCard->getId());
		cardRepository.addCard(*activeCard);
	}

	void changeBalance(BankCard& card, double sum)
	{
		double newBalance = card.getBalance() + sum;
		if (newBalance < 0)
		{
			//error message
		}
		else
		{
			if (card.getId() == activeCard->getId())
			{
				activeCard->setBalance(newBalance);
			}
			card.setBalance(newBalance);
			cout << card << endl;
			cardRepository.deleteCard(card.getId());
			cardRepository.addCard(card);
			// cardRepository.updateCard(card);
		}
	}

	void resetPin() 
	{
		wrongPinCounter = 0;
	}
};
