#pragma once
#include <cstdlib>
#include <time.h>

#include "BankCard.h"

class CardRepository
{
private:

	static const char* dir;

	static void executeStatement(const string& sql, int(*callback)(void*, int, char**, char**), void* entity)
	{
		sqlite3* DB;
		char* messageError;

		try
		{
			int exit = 0;
			exit = sqlite3_open(dir, &DB);
			/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
			exit = sqlite3_exec(DB, sql.c_str(), callback, entity, &messageError);
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

	static int existsCallback(void* resEntity, int argc, char** argv, char** azColName)
	{
		BankCard* resCard = static_cast<BankCard*>(resEntity);
		resCard->setId(std::atoi(argv[0]));

		return 0;
	}

public:
	CardRepository() {}

	~CardRepository() {}

	bool cardExists(int cardNum)
	{
		BankCard resCard(-1);
		string sql = "SELECT * FROM BANKCARD WHERE CARDID =" + to_string(cardNum) + ";";
		executeStatement(sql, existsCallback, &resCard);
		return resCard.getId() > -1;
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

const char* CardRepository::dir = R"(c:\\UniversityBd\\ATM.db)";

