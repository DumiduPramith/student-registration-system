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

	bool get_registered_cources();

	void register_cource();

	bool save_db(string datas[]) override;

	bool user_exists(string name) override;

	bool get_cources();

	int get_userId();

	bool remove_registered_cources(int userId, int courseId);
};

