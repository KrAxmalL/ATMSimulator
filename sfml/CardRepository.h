#pragma once
#include <cstdlib>
#include <time.h>
#include <string>

#include "sqlite3.h"

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
		string sql = "SELECT * FROM BANKCARD WHERE CARDID =" + std::to_string(cardNum) + ";";
		executeStatement(sql, existsCallback, &resCard);
		return resCard.getId() > -1;
	}

	void addCard(const BankCard& card)
	{
		//expireDate is not written to db
		tm startBlockDate = card.getBlockStartDate();
		tm zeroDate = { 0 };
		string startBlock("-");
		if (startBlockDate.tm_year != 0)
		{
			startBlock = "" + to_string(startBlockDate.tm_year) + "-" + to_string(startBlockDate.tm_mon) + "-" + to_string(startBlockDate.tm_mday);
		}

		tm expireDay = card.getExpireDay();
		string expire("-");
		if (expireDay.tm_year != 0)
		{
			 expire = "" + to_string(expireDay.tm_year) + "-" + to_string(expireDay.tm_mon) + "-" + to_string(expireDay.tm_mday);
		}

		std::string sql =
			std::string(
				"INSERT INTO BANKCARD (CARDID, CARDNAME, CARDPIN, BLOCKED, BLOCKSTARTDATE, EXPIREDATE, CARDBALANCE, FK_CUSTOMERID, FK_BANKID) VALUES(")
			+ to_string(card.getId()) + ",'"
			+ card.getName() + "',"
			+ to_string(card.getPin()) + ","
			+ to_string(card.isBlocked()) + ",'"
			+ startBlock + "','"
			+ expire + "',"
			+ to_string(card.getBalance()) + ", "
			+ to_string(card.getUId()) + ", "
			+ to_string(card.getBId()) + ");";

		executeStatement(sql, NULL, NULL);
	}

	BankCard getCard(int cardNum)
	{
		BankCard resCard(-1);
		string sql = "SELECT * FROM BANKCARD WHERE CARDID =" + std::to_string(cardNum) + ";";
		executeStatement(sql, existsCallback, &resCard);
		if (resCard.getId() == -1)
		{
			//error
		}
		return resCard;
	}

	void updateCard(int cardNum, double addBalance)
	{
		BankCard resCard(-1);
		string sql = "UPDATE BANKCARD SET CARDBALANCE = " + to_string(addBalance) + " WHERE CARDID = " + to_string(cardNum) + "; ";
		executeStatement(sql, existsCallback, &resCard);
	}

	void deleteCard(int cardNum)
	{
		BankCard resCard(-1);
		string sql = "DELETE FROM BANKCARD WHERE CARDID = " + to_string(cardNum) + ";";
		executeStatement(sql, existsCallback, &resCard);
	}
};

const char* CardRepository::dir = R"(c:\\UniversityBd\\ATM.db)";

