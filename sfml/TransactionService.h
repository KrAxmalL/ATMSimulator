#pragma once
#include <vector>

#include "BankCard.h"
#include "Transaction.h"
#include "TransactionRepository.h"
#include "CardService.h"


class TransactionService
{
private:

	TransactionRepository transactionRepository;
	CardService& cardService;

public:

	explicit TransactionService(CardService& cardService): transactionRepository(), cardService(cardService) {}

	~TransactionService() {}

	Transaction getTransaction(int transactionId)
	{
		if (transactionRepository.transactionExists(transactionId))
		{
			return transactionRepository.getTransaction(transactionId);
		}
		else
		{
			//error message
		}
	}

	std::vector<Transaction> getTransactionsOf(int cardNum)
	{
		if (cardService.cardExists(cardNum))
		{
			return transactionRepository.getTransactionsOf(cardNum);
		}
		else
		{
			//error message
		}
	}

	void transactionFromActiveCard(int toId, double sum)
	{
		performTransaction(cardService.getActiveCard().getId(), toId, sum);
	}

	void performTransaction(const int fromId, const int toId, double sum)
	{
		if (cardService.cardExists(fromId) && cardService.cardExists(toId))
		{
			BankCard from = cardService.getCard(fromId);
			BankCard to = cardService.getCard(toId);
			if (!from.isBlocked() && !to.isBlocked())
			{
				if (sum > from.getBalance())
				{
					//error message
				}
				else
				{
					cardService.changeBalance(from, -sum);
					cardService.changeBalance(to, sum);
					std::cout << "changed balance on 2 cards" << std::endl;
					std::cout << from << std::endl;
					std::cout << to << std::endl;
					Transaction res{};
					res.setCardFromId(fromId);
					res.setCardToId(toId);
					res.setSum(sum);
					std::time_t t = std::time(0);   // get time now
					std::tm* now = std::localtime(&t);
					res.setTransactionDate(*now);
					transactionRepository.addTransaction(res);
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
};
