#pragma once
#include "User.h"
class Admin :
    public User
{
private:

protected:
    int admin_id;

public:
    Admin();

    void create_cource();

    bool save_db(string table, string datas[]);
};
