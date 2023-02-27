#include "Student.h"

Student::Student():User("student") {}

void Student::view_cources() {}

void Student::register_cource() {}

bool Student::save_db (string datas[]) {
	return DatabaseHelper::save_user(role, datas);
}

bool Student::user_exists(string name) {
	return DatabaseHelper::find_user_exist(role, name);
}

bool Student::get_cources() {
	std::string sql = "select * from course";
	Database::select_data(sql);
	return true;
}

