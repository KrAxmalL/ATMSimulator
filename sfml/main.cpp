#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "TextBox.h"
#include "TextArea.h"
#include "AtmManager.h"
#include "Assets.h"

#include <iostream>
#include <stdio.h>
#include "sqlite3.h"
#include "TransactionRepository.h"

using namespace sf;
using namespace std;

static int createDB(const char* s);
static int createCustomerTable(const char* s);
static int createBankCardTable(const char* s);
static int createBankTable(const char* s);
static int createTransactionTable(const char* s);
static int createBankTable(const char* s);
static int createProcessingTable(const char* s);
static int createATMTable(const char* s);

static int createATM(const char* s, string n);
static int createBank(const char* s, string n);
static int createCustomer(const char* s, string fN, string lN, string dB);
static int createBankCard(const char* s, int numC, string cN, int pin, int ban, string dB, string exD, double bal, int customerId, int bankId);
static int createBankTransaction(const char* s, string transactionDate, double sum, int cardFrom, int cardTo);
static int selectDataFromCustomer(const char* s);

static int callback(void* NotUsed, int argc, char** argv, char** azColName);
// temp
static tm tmFromString(const char* dateStr);
static void tester();

int main()
{
    const char* dir = R"(C:\\UniversityBd\\ATM.db)";

    /*createDB(dir);
    createCustomerTable(dir);
    createATMTable(dir);
    createBankTable(dir);
    createBankCardTable(dir);
    createTransactionTable(dir);
    createProcessingTable(dir);

    createCustomer(dir, "Lili", "Olyva", "2020-11-11");
    createBank(dir, "Credit Agricole Bank");
    createATM(dir, "Credit Agricole ATM");
    createBankCard(dir, 11111, "Shopping card", 1111, 0, "-", "2022-02-02", 0.0, 1, 1);*/

    /*createBankCard(dir, 10000, "Second shopping card ", 1111, 0, "-", "2022-02-02", 100.0, 1, 1);
    createBankTransaction(dir, "2021-02-02", 2020.0, 0, 1);
    createBankTransaction(dir, "2021-02-05", 2030.0, 0, 1);*/

    selectDataFromCustomer(dir);

   

    /*BankCard toAdd;
    toAdd.setId(55);
    toAdd.setName("Prekol card");
    toAdd.setBalance(666.666);
    toAdd.setBlocked(true);
    std::time_t t = std::time(0);   // get time now
    tm* now = new tm({0});
    localtime_s(now, &t);
    now->tm_year += 1900;
    now->tm_mon += 3;
    tm nowLater(*now);
    nowLater.tm_mon += 1;
    toAdd.setBlockStartDate(*now);
    toAdd.setExpireDay(nowLater);
    toAdd.setPin(222);
    toAdd.setUId(1);
    toAdd.setBId(1);
    cardRepository.addCard(toAdd);
    delete now;*/

   //cardRepository.updateCard(11111, 13);

    Assets::Instance().load();


    AtmManager manager{};
    manager.start();

    return 0;
}


static int createDB(const char* s)
{
    sqlite3* DB;

    int exit = 0;
    exit = sqlite3_open(s, &DB);

    sqlite3_close(DB);

    return 0;
}

static int createCustomerTable(const char* s)
{
    sqlite3* DB;
    char* messageError;

    string sql = "CREATE TABLE IF NOT EXISTS CUSTOMER("
        "CUSTOMERID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "FIRSTNAME TEXT NOT NULL, "
        "LASTNAME TEXT NOT NULL, "
        "BIRTHDATE TEXT(10) NOT NULL);";

    try
    {
        int exit = 0;
        exit = sqlite3_open(s, &DB);
        /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
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

    return 0;
}

static int createBankCardTable(const char* s)
{
    sqlite3* DB;
    char* messageError;

    string sql = "CREATE TABLE IF NOT EXISTS BANKCARD("
        "CARDID INTEGER PRIMARY KEY, "
        "CARDNAME TEXT NOT NULL, "
        "CARDPIN INTEGER NOT NULL, "
        "BLOCKED INTEGER NOT NULL, "
        "BLOCKSTARTDATE TEXT(10) NULL, "
        "EXPIREDATE TEXT(10) NOT NULL, "
        "CARDBALANCE REAL NOT NULL, "
        "FK_CUSTOMERID INTEGER NOT NULL, "
        "FK_BANKID INTEGER NOT NULL, "
        "FOREIGN KEY(FK_CUSTOMERID) REFERENCES CUSTOMER(CUSTOMERID), "
        "FOREIGN KEY(FK_BANKID) REFERENCES BANK(BANKID));";

    try
    {
        int exit = 0;
        exit = sqlite3_open(s, &DB);
        /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Error in createTable 'BancCard' function.\n";
            sqlite3_free(messageError);
        }
        else
            cout << "Table created 'BancCard' Successfully\n";
        sqlite3_close(DB);
    }
    catch (const exception& e)
    {
        cerr << e.what();
    }

    return 0;
}
static int createBankTable(const char* s)
{
    sqlite3* DB;
    char* messageError;

    string sql = "CREATE TABLE IF NOT EXISTS BANK("
        "BANKID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "BANKNAME TEXT(50) NOT NULL);";

    try
    {
        int exit = 0;
        exit = sqlite3_open(s, &DB);
        /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Error in createTable 'Bank' function.\n";
            sqlite3_free(messageError);
        }
        else
            cout << "Table 'Bank' created Successfully\n";
        sqlite3_close(DB);
    }
    catch (const exception& e)
    {
        cerr << e.what();
    }

    return 0;
}
static int createTransactionTable(const char* s)
{
    sqlite3* DB;
    char* messageError;

    string sql = "CREATE TABLE IF NOT EXISTS CARDTRANSACTION("
        "TRANSACTIONID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "DATEOFTRANSACTION TEXT(10) NOT NULL, "
        "SUMCURRENCY REAL NOT NULL, "
        "FK_CARDIDTO INTEGER NOT NULL, "
        "FK_CARDIDFROM INTEGER NOT NULL, "
        "FOREIGN KEY(FK_CARDIDTO) REFERENCES BANKCARD(BANKCARDID), "
        "FOREIGN KEY(FK_CARDIDFROM) REFERENCES BANKCARD(BANKCARDID));";

    try
    {
        int exit = 0;
        exit = sqlite3_open(s, &DB);
        /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Error in createTable 'Transaction' function.\n";
            sqlite3_free(messageError);
        }
        else
            cout << "Table 'Transaction' created Successfully\n";
        sqlite3_close(DB);
    }
    catch (const exception& e)
    {
        cerr << e.what();
    }

    return 0;
}
static int createProcessingTable(const char* s)
{
    sqlite3* DB;
    char* messageError;

    string sql = "CREATE TABLE IF NOT EXISTS PROCESSING("
        "FK_BANKID INTEGER NOT NULL, "
        "FK_ATMID INTEGER NOT NULL, "
        "DATEOF TEXT(10) NOT NULL, "
        "FOREIGN KEY(FK_BANKID) REFERENCES BANK(BANKCARDID), "
        "FOREIGN KEY(FK_ATMID) REFERENCES ATM(ATMID));";

    try
    {
        int exit = 0;
        exit = sqlite3_open(s, &DB);
        /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Error in createTable 'Processing' function.\n";
            sqlite3_free(messageError);
        }
        else
            cout << "Table 'Processing' created Successfully\n";
        sqlite3_close(DB);
    }
    catch (const exception& e)
    {
        cerr << e.what();
    }

    return 0;
}
static int createATMTable(const char* s)
{
    sqlite3* DB;
    char* messageError;

    string sql = "CREATE TABLE IF NOT EXISTS ATM("
        "ATMID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "ATMNAME TEXT(50) NOT NULL);";

    try
    {
        int exit = 0;
        exit = sqlite3_open(s, &DB);
        /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Error in createTable 'ATM' function.\n";
            sqlite3_free(messageError);
        }
        else
            cout << "Table 'ATM' created Successfully\n";
        sqlite3_close(DB);
    }
    catch (const exception& e)
    {
        cerr << e.what();
    }

    return 0;
}


static int createCustomer(const char* s, string fN, string lN, string dB)
{
    sqlite3* DB;
    char* messageError;

    std::string var = std::string("INSERT INTO CUSTOMER (FIRSTNAME, LASTNAME, BIRTHDATE) VALUES('") + fN + "','" + lN + "','" + dB + "');";

    string sql(var);

    int exit = sqlite3_open(s, &DB);
    /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error in insertData To Customer function." << endl;
        sqlite3_free(messageError);
    }
    else
        cout << "Records inserted To Customer Successfully!" << endl;

    return 0;
}

static int createATM(const char* s, string n)
{
    sqlite3* DB;
    char* messageError;

    std::string var = std::string("INSERT INTO ATM (ATMNAME) VALUES('") + n + "');";

    string sql(var);

    int exit = sqlite3_open(s, &DB);
    /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error in insertData To ATM function." << endl;
        sqlite3_free(messageError);
    }
    else
        cout << "Records inserted To ATM Successfully!" << endl;

    return 0;
}

static int createBank(const char* s, string n)
{
    sqlite3* DB;
    char* messageError;

    std::string var = std::string("INSERT INTO BANK (BANKNAME) VALUES('") + n + "');";

    string sql(var);

    int exit = sqlite3_open(s, &DB);
    /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error in insertData To Bank function." << endl;
        sqlite3_free(messageError);
    }
    else
        cout << "Records inserted To Bank Successfully!" << endl;

    return 0;
}

static int createBankCard(const char* s, int numC, string cN, int pin, int ban, string dB, string exD, double bal, int customerId, int bankId)
{
    sqlite3* DB;
    char* messageError;

    std::string var =
        std::string(
            "INSERT INTO BANKCARD (CARDID, CARDNAME, CARDPIN, BLOCKED, BLOCKSTARTDATE, EXPIREDATE, CARDBALANCE, FK_CUSTOMERID, FK_BANKID) VALUES(")
        + to_string(numC) + ",'"
        + cN + "',"
        + to_string(pin) + ","
        + to_string(ban) + ",'"
        + dB + "','"
        + exD + "',"
        + to_string(bal) + ", "
        + to_string(customerId) + ", "
        + to_string(bankId) + ");";

    string sql(var);

    int exit = sqlite3_open(s, &DB);
    /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error in insertData To BankCard function." << endl;
        sqlite3_free(messageError);
    }
    else
        cout << "Records inserted To BankCard Successfully!" << endl;

    return 0;
}

static int createBankTransaction(const char* s, string transactionDate, double sum, int cardFrom, int cardTo)
{
    sqlite3* DB;
    char* messageError;

    std::string var = std::string("INSERT INTO CARDTRANSACTION (DATEOFTRANSACTION, SUMCURRENCY, FK_CARDIDTO, FK_CARDIDFROM) VALUES('") + 
        transactionDate + "'," + 
        to_string(sum) + "," + 
        to_string(cardTo) + "," + 
        to_string(cardFrom) + ");";

    string sql(var);

    int exit = sqlite3_open(s, &DB);
    /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error in insertData To Customer function." << endl;
        sqlite3_free(messageError);
    }
    else
        cout << "Records inserted To Customer Successfully!" << endl;

    return 0;
}

//static int createCustomer(const char* s, string fN, string lN, string dB)
//{
//    sqlite3* DB;
//    char* messageError;
//
//    std::string var = std::string("INSERT INTO CUSTOMER (FIRSTNAME, LASTNAME, BIRTHDATE) VALUES('") + fN + "','" + lN + "','" + dB + "');";
//
//    string sql(var);
//
//    int exit = sqlite3_open(s, &DB);
//    /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
//    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
//    if (exit != SQLITE_OK) {
//        cerr << "Error in insertData To Customer function." << endl;
//        sqlite3_free(messageError);
//    }
//    else
//        cout << "Records inserted To Customer Successfully!" << endl;
//
//    return 0;
//}


static int selectDataFromCustomer(const char* s)
{
    sqlite3* DB;
    char* messageError;

    string sql = "SELECT * FROM CUSTOMER;";

    int exit = sqlite3_open(s, &DB);
    /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
    exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);

    if (exit != SQLITE_OK) {
        cerr << "Error in selectDataFromCustomer function." << endl;
        sqlite3_free(messageError);
    }
    else
        cout << "Records selected FROM CUSTOMER Successfully!" << endl;

    return 0;
}

// retrieve contents of database used by selectData()
/* argc: holds the number of results, argv: holds each value in array, azColName: holds each column returned in array, */
static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    for (int i = 0; i < argc; i++)
    {
        // column name and value
        cout << azColName[i] << ": " << argv[i] << endl;
    }

    cout << endl;

    return 0;
}

static tm tmFromString(const char* dateStrConst) 
{

    char* dateStr = new char[20];
    strcpy(dateStr, dateStrConst);

    dateStr[4] = dateStr[7] = dateStr[10] = dateStr[13] = dateStr[16] = '\0';
    
    struct tm tmdate = { 0 };
    tmdate.tm_year = atoi(&dateStr[0]) - 1900;
    tmdate.tm_mon = atoi(&dateStr[5]) - 1;
    tmdate.tm_mday = atoi(&dateStr[8]);
    tmdate.tm_hour = atoi(&dateStr[11]) - 1;
    tmdate.tm_min = atoi(&dateStr[14]);
    tmdate.tm_sec = atoi(&dateStr[17]);

    return tmdate;
}

static void tester() 
{
   
    CardRepository cardRepository;
    TransactionRepository transactionRepo;

    transactionRepo.addTransaction(Transaction{ 0, tmFromString("2020-02-10 22:44:02"), 1000.0, 0, 1 });
    transactionRepo.addTransaction(Transaction{ 0, tmFromString("2020-08-02 20:20:02"), 1000.0, 0, 1 });


    if (transactionRepo.transactionExists(37)) {
        cout << "Exists" << endl;
        Transaction t = transactionRepo.getTransaction(37);

        cout << t << endl;
    }
    else {
        cout << "No such transaction" << endl;
    }

    vector<Transaction> trs = transactionRepo.getTransactionsOf(1);
    for (Transaction t : trs) {
         cout << t << endl;
    }

    if (cardRepository.cardExists(11111)) {
        cout << "Exists" << endl;
    }
    else {
        cout << "No such card" << endl;
    }
    cardRepository.deleteCard(1111);
    
    BankCard fromGet = cardRepository.getCard(11111);
    cout << fromGet.getName() << endl;
}