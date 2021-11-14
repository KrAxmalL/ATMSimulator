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
				cerr << "Error in executeStatement 'BankCard' function.\n";
				sqlite3_free(messageError);
			}
			else
				cout << "executeStatement in 'BankCard' finished Successfully\n";
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

	//to finish
	static int getCallback(void* resEntity, int argc, char** argv, char** azColName)
	{
		BankCard* resCard = static_cast<BankCard*>(resEntity);

		resCard->setId(std::atoi(argv[0]));
		resCard->setName(argv[1]);
		resCard->setPin(std::atoi(argv[2]));
		resCard->setBlocked(std::atoi(argv[3]));
		struct tm startBlockDate = { 0 };
		struct tm expireBlockDate = { 0 };
		if (resCard->isBlocked())
		{
			argv[4][4] = argv[4][7] = argv[4][10] = argv[4][13] = argv[4][16] = '\0';
			startBlockDate.tm_year = atoi(&argv[4][0]) - 1900;
			startBlockDate.tm_mon = atoi(&argv[4][5]) - 1;
			startBlockDate.tm_mday = atoi(&argv[4][8]);
			startBlockDate.tm_hour = atoi(&argv[4][11]) - 1;
			startBlockDate.tm_min = atoi(&argv[4][14]);
			startBlockDate.tm_sec = atoi(&argv[4][17]);

			argv[5][4] = argv[5][7] = argv[5][10] = argv[5][13] = argv[5][16] = '\0';
			expireBlockDate.tm_year = atoi(&argv[5][0]) - 1900;
			expireBlockDate.tm_mon = atoi(&argv[5][5]) - 1;
			expireBlockDate.tm_mday = atoi(&argv[5][8]);
			expireBlockDate.tm_hour = atoi(&argv[5][11]) - 1;
			expireBlockDate.tm_min = atoi(&argv[5][14]);
			expireBlockDate.tm_sec = atoi(&argv[5][17]);
		}
		resCard->setBlockStartDate(startBlockDate);
		resCard->setExpireDay(expireBlockDate);
		resCard->setBalance(std::atoi(argv[6]));
		resCard->setUId(std::atoi(argv[7]));
		resCard->setBId(std::atoi(argv[8]));

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
		executeStatement(sql, getCallback, &resCard);
		if (resCard.getId() == -1)
		{
			//error
		}
		std::cout << "In getCard: " << resCard << std::endl;
		return resCard;
	}

	void updateCard(int cardNum, double addBalance)
	{
		BankCard resCard(-1);
		string sql = "UPDATE BANKCARD SET CARDBALANCE = " + to_string(addBalance) + " WHERE CARDID = " + to_string(cardNum) + "; ";
		executeStatement(sql, getCallback, &resCard);
	}

	void deleteCard(int cardNum)
	{
		BankCard resCard(-1);
		string sql = "DELETE FROM BANKCARD WHERE CARDID = " + to_string(cardNum) + ";";
		executeStatement(sql, existsCallback, &resCard);
	}
};

const char* CardRepository::dir = R"(c:\\UniversityBd\\ATM.db)";

