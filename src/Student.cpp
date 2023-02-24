#include "Student.h"

Student::Student():User("student") {}

void Student::view_cources() {}

void Student::register_cource() {}

bool Student::save_db (string datas[]) {
	return DatabaseHelper::save_user("student", datas);
}

bool Student::user_exists(string name) {
	return DatabaseHelper::find_user_exist("student", name);
}

