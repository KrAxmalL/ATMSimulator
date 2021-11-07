#pragma once
#include <vector>
#include <string>
#include <time.h>

#include "sqlite3.h"

#include "Transaction.h"
#include "BankCard.h"

#include "CardRepository.h"

class TransactionRepository
{
private:

	CardRepository cardRepository;

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

	static int existsCallback(void* resTrans, int argc, char** argv, char** azColName)
	{
		Transaction* resTransaction = static_cast<Transaction*>(resTrans);

		resTransaction->setId(std::atoi(argv[0]));

		return 0;
	}

	static int getCallback(void* resTrans, int argc, char** argv, char** azColName)
	{
		Transaction* resTransaction = static_cast<Transaction*>(resTrans);

		resTransaction->setId(std::atoi(argv[0]));
		resTransaction->setSum(std::atoi(argv[2]));
		resTransaction->setCardToId(std::atoi(argv[3]));
		resTransaction->setCardFromId(std::atoi(argv[4]));

		argv[1][4] = argv[1][7] = argv[1][10] = argv[1][13] = argv[1][16] = '\0';
		struct tm tmdate = { 0 };
		tmdate.tm_year = atoi(&argv[1][0]) - 1900;
		tmdate.tm_mon = atoi(&argv[1][5]) - 1;
		tmdate.tm_mday = atoi(&argv[1][8]);
		tmdate.tm_hour = atoi(&argv[1][11]) - 1;
		tmdate.tm_min = atoi(&argv[1][14]);
		tmdate.tm_sec = atoi(&argv[1][17]);

		resTransaction->setTransactionDate(tmdate);

		return 0;
	}

public:
	explicit TransactionRepository(): cardRepository() 
	{
		
	}

	~TransactionRepository() {}

	bool transactionExists(int transactionId)
	{
		Transaction resTransaction(-1);
		string sql = "SELECT * FROM CARDTRANSACTION WHERE TRANSACTIONID =" + to_string(transactionId) + ";";
		executeStatement(sql, existsCallback, &resTransaction);
		return resTransaction.getId() > -1;
	}

	void addTransaction(const Transaction& transaction)
	{
		char buffer[20];
		strftime(buffer, 20, "%F %T", &transaction.getTransactionDate());

		string sql = std::string("INSERT INTO CARDTRANSACTION (DATEOFTRANSACTION, SUMCURRENCY, FK_CARDIDTO, FK_CARDIDFROM) VALUES('") +
			string(buffer) + "'," +
			to_string(transaction.getSum()) + "," +
			to_string(transaction.getCardToId()) + "," +
			to_string(transaction.getCardFromId()) + ");";

		executeStatement(sql, NULL, NULL);
	}

	Transaction getTransaction(int transactionId)
	{
		Transaction resTransaction(-1);
		string sql = "SELECT * FROM CARDTRANSACTION WHERE TRANSACTIONID = " + to_string(transactionId) + "; ";
		executeStatement(sql, getCallback, &resTransaction);

		if (resTransaction.getId() > -1)
			// todo: custom exception TransactionNotFoundException
			cerr << "No such transaction" << endl;

		return resTransaction;
	}

	std::vector<Transaction> getTransactionsOf(int cardNum)
	{
		vector<Transaction> transactions;
		string sql = "SELECT * FROM CARDTRANSACTION WHERE FK_CARDIDTO = " + to_string(cardNum) + 
			" OR FK_CARDIDFROM = " + to_string(cardNum) + "; ";
		sqlite3* DB;
		sqlite3_open(dir, &DB);
		sqlite3_stmt* stmt;

		int rc = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
		if (rc != SQLITE_OK) {
			printf("error: %s!\n", sqlite3_errmsg(DB));
			return {};
		}

		while (true) {
			rc = sqlite3_step(stmt);
			if (rc == SQLITE_DONE)
				break;
			if (rc != SQLITE_ROW) {
				printf("error: %s!\n", sqlite3_errmsg(DB));
				break;
			}

			Transaction t;
			t.setId(sqlite3_column_int(stmt, 0));
			t.setSum(sqlite3_column_double(stmt, 2));
			t.setCardFromId(sqlite3_column_int(stmt, 3));
			t.setCardToId(sqlite3_column_int(stmt, 4));
			
			char* dateStr = (char*)sqlite3_column_text(stmt, 1);
			dateStr[4] = dateStr[7] = dateStr[10] = dateStr[13] = dateStr[16] = '\0';
			struct tm tmdate = { 0 };
			tmdate.tm_year = atoi(&dateStr[0]) - 1900;
			tmdate.tm_mon = atoi(&dateStr[5]) - 1;
			tmdate.tm_mday = atoi(&dateStr[8]);
			tmdate.tm_hour = atoi(&dateStr[11]) - 1;
			tmdate.tm_min = atoi(&dateStr[14]);
			tmdate.tm_sec = atoi(&dateStr[17]);
			t.setTransactionDate(tmdate);
			
			transactions.push_back(t);
		}

		sqlite3_finalize(stmt);


		return transactions;
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
