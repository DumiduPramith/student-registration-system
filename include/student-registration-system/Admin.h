#pragma once
#include "User.h"
class Admin :
    public User
{
private:
public:
    Admin();

    void create_cource();
    void reg_user();
protected:
    int admin_id;
};
