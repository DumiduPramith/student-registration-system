#include "Academic.h"

Academic::Academic():User("academic") {}


bool Academic::save_db(string datas[]) {
	return DatabaseHelper::save_user(role, datas);
}

bool Academic::user_exists(string name) {
	return DatabaseHelper::find_user_exist(role, name);
}

bool Academic::view_reg_students() {
	std::string sql = "select * from student";
	Database::select_data(sql);
	return true;
}

int Academic::get_userId() {
	return 0;
}