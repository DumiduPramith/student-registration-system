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

    bool save_db(string datas[]) override;

    bool user_exists(string name) override;

    bool get_all_cources();
};
