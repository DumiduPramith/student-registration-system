#pragma once
#include "User.h"
#include<iostream>
#include <string>

class Student :
	public User
{

protected:
	int student_id;
	string cources;

public:
	Student();
	void view_cources();
	void register_cource();

	bool save_db(string datas[]) override;

	bool user_exists(string name) override;
};

