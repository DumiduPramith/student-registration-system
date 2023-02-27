#pragma once
#include "User.h"
class Management :
    public User
{
private:

protected:
    int management_id;

public:
    Management();
    void view_registered_student();
    
    bool save_db(string datas[]) override;

    bool user_exists(string name) override;
};