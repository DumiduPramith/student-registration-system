#pragma once
#include "Database.h"
class DatabaseHelper :
    public Database
{
protected:
    bool save_user(std::string table, std::string datas[]);

    bool find_user_exist(std::string table, std::string uname);
};

