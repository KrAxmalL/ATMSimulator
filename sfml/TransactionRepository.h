#pragma once
#include <vector>
#include <string>

#include "sqlite3.h"

#include "Transaction.h"
#include "BankCard.h"

#include "CardRepository.h"

class TransactionRepository
{
private:

	CardRepository cardRepository;

	static const char* dir;

	static void executeStatement(const string& sql, int(*callback)(void*, int, char**, char**))
	{
		sqlite3* DB;
		char* messageError;

		try
		{
			int exit = 0;
			exit = sqlite3_open(dir, &DB);
			/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
			exit = sqlite3_exec(DB, sql.c_str(), callback, 0, &messageError);
			if (exit != SQLITE_OK) {
				cerr << "Error in createTable 'Customer' function.\n";
				sqlite3_free(messageError);
			}
			else
				cout << "Table created 'Customer' Successfully\n";
			sqlite3_close(DB);
		}
		catch (const exception& e)
		{
			cerr << e.what();
		}
	}

	static int existsCallback(void* NotUsed, int argc, char** argv, char** azColName)
	{
		
		return 0;
	}

public:
	explicit TransactionRepository(): cardRepository() 
	{
		
	}

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


const char* TransactionRepository::dir = R"(c:\\UniversityBd\\ATM.db)";
