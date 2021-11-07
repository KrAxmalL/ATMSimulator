#pragma once

#include "BankCard.h"

class CardRepository
{
public:
	CardRepository() {}

	~CardRepository() {}

	bool cardExists(int cardNum)
	{
		//sql code - maybe use getCard
	}

	void addCard(const BankCard& card)
	{
		//sql code
	}

	BankCard getCard(int cardNum)
	{
		//sql code
	}

	void updateCard(const BankCard& card)
	{
		//sql code
	}

	void deleteCard(const BankCard& card)
	{
		//sql code
	}
};
