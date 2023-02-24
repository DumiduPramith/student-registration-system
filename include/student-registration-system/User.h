#pragma once
#include<iostream>
#include<string>
#include "DatabaseHelper.h"

using namespace std;

class User: public DatabaseHelper
{
protected:
    string username;
    string password;
    string email;
    bool is_authenticated;
    string role;


public:
    User(string u_role);
    ~User();

    void set_username(string uname);
    void set_password(string pword);
    void set_email(string mail);
    bool login();
    virtual bool save_db(string datas[]) = 0;
    virtual bool user_exists(string name) = 0;
};

