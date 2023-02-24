#pragma once
#include "User.h"
#include<iostream>
#include <string>

class Academic :
	public User
{
private:
protected:
	int academic_id;
public:
	Academic();
	static void login();


	static void reg_user();
};

