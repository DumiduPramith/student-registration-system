#pragma once
#include "User.h"
#include<iostream>
#include <string>

class Student :
	public User
{
	int student_id;
	string cources;

public:
	Student();
	void view_cources();
	void register_cource();

	int save_file();
	static void reg_user();
};

