#include "Course.h"

Course::Course() {
	course_code = "";
	course_name = "";
	course_description = "";
}

bool Course::create_course() {
	if (course_code == "" && course_name == "" && course_description == "") {
		return false;
	}
	
	if (DatabaseHelper::find_course_exist(course_code)) {
		std::cout << "Course already exist" << std::endl;
		return false;
	}
	return DatabaseHelper::create_course(course_code, course_name, course_description);
}