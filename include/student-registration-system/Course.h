#pragma once
#include<iostream>
#include <DatabaseHelper.h>

class Course:public DatabaseHelper
{
public:
	Course();
	std::string course_code;
	std::string course_name;
	std::string course_description;

	bool create_course();
};

