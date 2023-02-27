#include "Admin.h"

Admin::Admin() :User("admin") { cout << "test" << endl; }

void Admin::create_cource(){}

bool Admin::save_db(string datas[]) {
	return DatabaseHelper::save_user(role, datas);
}

bool Admin::user_exists(string name) {
	return DatabaseHelper::find_user_exist(role, name);
}

bool Admin::get_all_cources() {
	std::string sql = "select * from course";
	Database::select_data(sql);
	return true;
}