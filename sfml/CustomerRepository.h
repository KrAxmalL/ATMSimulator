#pragma once
#include "Customer.h"

class CustomerRepository
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
				cerr << "Error in executeStatement 'Customer' function.\n";
				sqlite3_free(messageError);
			}
			else
				cout << "executeStatement in 'Customer' finished Successfully\n";
			sqlite3_close(DB);
		}
		catch (const exception& e)
		{
			cerr << e.what();
		}
	}

	static int existsCallback(void* resEntity, int argc, char** argv, char** azColName)
	{
		Customer* resCustomer = static_cast<Customer*>(resEntity);
		resCustomer->setId(std::atoi(argv[0]));

		return 0;
	}

	static int getCallback(void* resEntity, int argc, char** argv, char** azColName)
	{
		Customer* resCustomer = static_cast<Customer*>(resEntity);

		resCustomer->setId(std::atoi(argv[0]));
		resCustomer->setFName(argv[1]);
		resCustomer->setSName(argv[2]);

		return 0;
	}

public:

	explicit CustomerRepository() {}
	~CustomerRepository() {}

	Customer getCustomer(int customerId)
	{
		Customer resCustomer{ -1 };
		std::string sql = "SELECT * FROM CUSTOMER WHERE CUSTOMERID = " + to_string(customerId);
		executeStatement(sql, &getCallback, &resCustomer);

		if (resCustomer.getId() == -1)
		{
			throw std::exception("Customer doesn't exist");
		}

		return resCustomer;
	}

};

const char* CustomerRepository::dir = R"(c:\\UniversityBd\\ATM.db)";
