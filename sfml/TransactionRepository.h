#pragma once
#include <vector>

#include "Transaction.h"
#include "BankCard.h"

#include "CardRepository.h"

class TransactionRepository
{
private:

	CardRepository cardRepository;

public:
	explicit TransactionRepository(): cardRepository() {}

	~TransactionRepository() {}

	bool transactionExists(int transactionId)
	{

	}

	void addTransaction(const Transaction& transaction)
	{
		//sql code
	}

	Transaction getTransaction(int transactionId)
	{
		//sql code
	}

	std::vector<Transaction> getTransactionsOf(int cardNum)
	{
		
		//sql code for selecting all transactions of this card
	}

	void updateTransaction(const Transaction& transaction)
	{
		//sql code
	}

	void deleteTransaction(const Transaction& transaction)
	{
		//sql code
	}
};

