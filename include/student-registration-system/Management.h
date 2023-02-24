#pragma once
#include "User.h"
class Management :
    public User
{
protected:
    int management_id;
private:
public:
    Management();
    void view_registered_student();
    void reg_user();
};