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
	CardService cardService;

public:

	explicit TransactionService(): transactionRepository(), cardService() {}

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

					Transaction res{};
					res.setCardFromId(fromId);
					res.setCardToId(toId);
					res.setSum(sum);
					//res.setTransactionDate(); - set current date
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
