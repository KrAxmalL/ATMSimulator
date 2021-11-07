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

		// column name and value
		resCard->setId(std::atoi(argv[0]));
		resCard->setName(argv[1]);
		resCard->setPin(std::atoi(argv[2]));
		resCard->setBlocked(std::atoi(argv[3]));

		if (argv[4] == "-") {
			resCard->setBlockStartDate({});
		}
		else {
			argv[4][4] = argv[4][7] = '\0';
			struct tm tmdate = { 0 };
			tmdate.tm_year = atoi(&argv[4][0]) - 1900;
			tmdate.tm_mon = atoi(&argv[4][5]) - 1;
			tmdate.tm_mday = atoi(&argv[4][8]);
			time_t t = mktime(&tmdate);

			resCard->setBlockStartDate(tmdate);
		}

		if (argv[5] == "-") {
			resCard->setExpireDay({});
		}
		else {
			argv[5][4] = argv[5][7] = '\0';
			struct tm tmdate = { 0 };
			tmdate.tm_year = atoi(&argv[5][0]) - 1900;
			tmdate.tm_mon = atoi(&argv[5][5]) - 1;
			tmdate.tm_mday = atoi(&argv[5][8]);
			time_t t = mktime(&tmdate);

			resCard->setExpireDay(tmdate);
		}

		resCard->setBalance(std::atof(argv[6]));
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

