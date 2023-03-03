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

	bool save_db(string datas[]) override;

	bool user_exists(string name) override;

	bool view_reg_students();

	int get_userId();
};

