#pragma once
#include<iostream>
#include<string>

using namespace std;

class User
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
    virtual int save_file() = 0;
};

