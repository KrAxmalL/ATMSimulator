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
    const char* dir = R"(c:\\UniversityBd\\ATM.db)";

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

    //selectDataFromCustomer(dir);

   

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

    /*
    {
        Controller controller(new Service(new Repository(5)));

    RenderWindow window(VideoMode(1000, 700), "SFML works!");
    window.setKeyRepeatEnabled(true);
    Texture textureFon;
    if (!textureFon.loadFromFile("Forest.png"))
    {

    }
    Texture textureBox;
    if (!textureBox.loadFromFile("blank.png"))
    {

    }
    Texture textureLabel;
    if (!textureLabel.loadFromFile("label1.png"))
    {

    }
    //Texture textureButton;
    //if (!textureButton.loadFromFile("buttonFon.png"))
    {

    }
    Sprite background(textureFon);
    Color Grey(200, 200, 200);

    Font arial;
    arial.loadFromFile("arial.ttf");

    TextArea areaCard("Input card number", { 300,50 }, 20, Color::White, Color::Black, textureLabel);
    areaCard.setFont(arial);
    areaCard.setPosition({ 350,200 });
    areaCard.setVisible(false);

    Textbox boxCardNum(25, Color::Black, true, textureBox);
    boxCardNum.setFont(arial);
    boxCardNum.setPosition({ 450,300 });
    boxCardNum.setVisible(false);
    boxCardNum.setlimit(true, 5);

    Button btnStart("Start", { 200,50 }, 20, Color::White, Color::Black, textureBox);
    btnStart.setPosition({ 400, 350 });
    btnStart.setFont(arial);

    Button btnOkCard("OK", { 100,50 }, 25, Color::White, Color::Black, textureBox);
    btnOkCard.setPosition({ 450, 500 });
    btnOkCard.setFont(arial);
    btnOkCard.setVisible(false);

    Button btnOkPin("OK", { 80,50 }, 25, Color::White, Color::Black, textureBox);
    btnOkPin.setPosition({ 450, 500 });
    btnOkPin.setFont(arial);
    btnOkPin.setVisible(false);

    Button btnf1("func1", { 240,50 }, 25, Color::White, Color::Black, textureBox);
    btnf1.setPosition({ 250, 300 });
    btnf1.setFont(arial);
    btnf1.setVisible(false);

    Button btnf2("func2", { 240,50 }, 25, Color::White, Color::Black, textureBox);
    btnf2.setPosition({ 510, 300 });
    btnf2.setFont(arial);
    btnf2.setVisible(false);

    Button btnf3("func3", { 240,50 }, 25, Color::White, Color::Black, textureBox);
    btnf3.setPosition({ 250, 370 });
    btnf3.setFont(arial);
    btnf3.setVisible(false);

    Button btnf4("func4", { 240,50 }, 25, Color::White, Color::Black, textureBox);
    btnf4.setPosition({ 510, 370 });
    btnf4.setFont(arial);
    btnf4.setVisible(false);

    Button btnf5("func5", { 240,50 }, 25, Color::White, Color::Black, textureBox);
    btnf5.setPosition({ 250, 440 });
    btnf5.setFont(arial);
    btnf5.setVisible(false);

    Button btnf6("func6", { 240,50 }, 25, Color::White, Color::Black, textureBox);
    btnf6.setPosition({ 510, 440 });
    btnf6.setFont(arial);
    btnf6.setVisible(false);

    Button btnf7("func7", { 240,50 }, 25, Color::White, Color::Black, textureBox);
    btnf7.setPosition({ 250, 510 });
    btnf7.setFont(arial);
    btnf7.setVisible(false);

    Button btnf8("func8", { 240,50 }, 25, Color::White, Color::Black, textureBox);
    btnf8.setPosition({ 510, 510 });
    btnf8.setFont(arial);
    btnf8.setVisible(false);

    while (window.isOpen())
    {
        Event event;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            boxCardNum.setSelected(true);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            boxCardNum.setSelected(false);
        }
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
            case Event::TextEntered:
                boxCardNum.typedOn(event);
            case Event::MouseMoved:
               if (btnStart.isMouseOver(window)) {
                   btnStart.setBackColor(Grey);
                }
                else {
                   btnStart.setBackColor(Color::White);
                }
                if (btnOkCard.isMouseOver(window)) {
                    btnOkCard.setBackColor(Grey);
                }
                else {
                    btnOkCard.setBackColor(Color::White);
                }
                if (btnOkPin.isMouseOver(window)) {
                    btnOkPin.setBackColor(Grey);
                }
                else {
                    btnOkPin.setBackColor(Color::White);
                }
                if (btnf1.isMouseOver(window)) {
                    btnf1.setBackColor(Grey);
                }
                else {
                    btnf1.setBackColor(Color::White);
                }
                if (btnf2.isMouseOver(window)) {
                    btnf2.setBackColor(Grey);
                }
                else {
                    btnf2.setBackColor(Color::White);
                }
                if (btnf3.isMouseOver(window)) {
                    btnf3.setBackColor(Grey);
                }
                else {
                    btnf3.setBackColor(Color::White);
                }
                if (btnf4.isMouseOver(window)) {
                    btnf4.setBackColor(Grey);
                }
                else {
                    btnf4.setBackColor(Color::White);
                }
                if (btnf5.isMouseOver(window)) {
                    btnf5.setBackColor(Grey);
                }
                else {
                    btnf5.setBackColor(Color::White);
                }
                if (btnf6.isMouseOver(window)) {
                    btnf6.setBackColor(Grey);
                }
                else {
                    btnf6.setBackColor(Color::White);
                }
                if (btnf7.isMouseOver(window)) {
                    btnf7.setBackColor(Grey);
                }
                else {
                    btnf7.setBackColor(Color::White);
                }
                if (btnf8.isMouseOver(window)) {
                    btnf8.setBackColor(Grey);
                }
                else {
                    btnf8.setBackColor(Color::White);
                }
                break;
            case Event::MouseButtonPressed:
                if (btnStart.isMouseOver(window)) {
                    btnStart.setVisible(false);
                    btnOkCard.setVisible(true);
                    boxCardNum.setVisible(true);
                    areaCard.setVisible(true);

                }
                else if (btnOkCard.isMouseOver(window)) {
                    areaCard.setText("Input PIN number");
                    boxCardNum.clear();
                    boxCardNum.setSecret(true);
                    boxCardNum.setlimit(true, 4);
                    btnOkPin.setVisible(true);
                    btnOkCard.setVisible(false);

                }
                else if (btnOkPin.isMouseOver(window)) {
                    boxCardNum.setVisible(false);
                    areaCard.setVisible(false);
                    btnOkCard.setVisible(false);
                    btnOkPin.setVisible(false);

                    btnf1.setVisible(true);
                    btnf2.setVisible(true);
                    btnf3.setVisible(true);
                    btnf4.setVisible(true);

                    btnf5.setVisible(true);
                    btnf6.setVisible(true);
                    btnf7.setVisible(true);
                    btnf8.setVisible(true);
                }
                else if (btnf1.isMouseOver(window)) {
                    btnf1.setVisible(false);
                    btnf2.setVisible(false);
                    btnf3.setVisible(false);
                    btnf4.setVisible(false);

                    btnf5.setVisible(false);
                    btnf6.setVisible(false);
                    btnf7.setVisible(false);
                    btnf8.setVisible(false);

                    //action for button func1
                }
                else if (btnf2.isMouseOver(window)) {
                    btnf1.setVisible(false);
                    btnf2.setVisible(false);
                    btnf3.setVisible(false);
                    btnf4.setVisible(false);

                    btnf5.setVisible(false);
                    btnf6.setVisible(false);
                    btnf7.setVisible(false);
                    btnf8.setVisible(false);

                    //action for button func2
                }
                else if (btnf3.isMouseOver(window)) {
                    btnf1.setVisible(false);
                    btnf2.setVisible(false);
                    btnf3.setVisible(false);
                    btnf4.setVisible(false);

                    btnf5.setVisible(false);
                    btnf6.setVisible(false);
                    btnf7.setVisible(false);
                    btnf8.setVisible(false);

                    //action for button func3
                }
                else if (btnf4.isMouseOver(window)) {
                    btnf1.setVisible(false);
                    btnf2.setVisible(false);
                    btnf3.setVisible(false);
                    btnf4.setVisible(false);

                    btnf5.setVisible(false);
                    btnf6.setVisible(false);
                    btnf7.setVisible(false);
                    btnf8.setVisible(false);

                    //action for button func4
                }
                else if (btnf5.isMouseOver(window)) {
                    btnf1.setVisible(false);
                    btnf2.setVisible(false);
                    btnf3.setVisible(false);
                    btnf4.setVisible(false);

                    btnf5.setVisible(false);
                    btnf6.setVisible(false);
                    btnf7.setVisible(false);
                    btnf8.setVisible(false);

                    //action for button func5
                }
                else if (btnf6.isMouseOver(window)) {
                    btnf1.setVisible(false);
                    btnf2.setVisible(false);
                    btnf3.setVisible(false);
                    btnf4.setVisible(false);

                    btnf5.setVisible(false);
                    btnf6.setVisible(false);
                    btnf7.setVisible(false);
                    btnf8.setVisible(false);

                    //action for button func6
                }
                else if (btnf7.isMouseOver(window)) {
                    btnf1.setVisible(false);
                    btnf2.setVisible(false);
                    btnf3.setVisible(false);
                    btnf4.setVisible(false);

                    btnf5.setVisible(false);
                    btnf6.setVisible(false);
                    btnf7.setVisible(false);
                    btnf8.setVisible(false);

                    //action for button func7
                    std::cout << "Controller called: " << controller.getData() << '\n';

                }
                else if (btnf8.isMouseOver(window)) {
                    btnf1.setVisible(false);
                    btnf2.setVisible(false);
                    btnf3.setVisible(false);
                    btnf4.setVisible(false);

                    btnf5.setVisible(false);
                    btnf6.setVisible(false);
                    btnf7.setVisible(false);
                    btnf8.setVisible(false);

                    //action for button func8
                }
            }
        }

        window.clear();
        window.draw(background);
        btnStart.drawTo(window);
        btnOkCard.drawTo(window);
        btnOkPin.drawTo(window);
        boxCardNum.drawTo(window);
        areaCard.drawTo(window);
        btnf1.drawTo(window);
        btnf2.drawTo(window);
        btnf3.drawTo(window);
        btnf4.drawTo(window);
        btnf5.drawTo(window);
        btnf6.drawTo(window);
        btnf7.drawTo(window);
        btnf8.drawTo(window);
        window.display();
    }
    }*/

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