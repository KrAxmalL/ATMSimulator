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
		if (card.isBlocked())
		{
			/*
				if(card.getExpireDay())
				if current date is bigger than expire block date - unblock card and return false;
				else return true
				*/
		}
		else
		{
			return false;
		}
	}

	bool cardExists(int cardNum)
	{
		return cardRepository.cardExists(cardNum);
	}

	void makeActiveCard(int cardNum)
	{
		activeCard = new BankCard(cardRepository.getCard(cardNum));
	}

	void blockCard(BankCard& card)
	{
		if (!isCardBlocked(card))
		{
			card.changeBlocking();
			//activeCard->setBlockStartDate(); - set current date
			cardRepository.updateCard(card.getId(), card.getBalance());
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
						blockCard(dbCard);
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
			//error message
		}
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
			card.setBalance(newBalance);
			cardRepository.updateCard(card.getId(), card.getBalance());
		}
	}
};
