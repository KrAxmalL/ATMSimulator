#pragma once

#include <stdio.h>
#include <vector>
#include <string>
#include <mysql.h>
#include "pch.h"


using namespace std;

class DatabaseConnect
{
private:
    static DatabaseConnect* _instance;
    DatabaseConnect();

    static MYSQL* dbHost;
    static string dbName;
    static string dbPass;
    static string dbUser;
};