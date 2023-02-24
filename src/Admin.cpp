#include "Admin.h"

Admin::Admin() :User("admin") { cout << "test" << endl; }

void Admin::create_cource(){}

bool Admin::save_db(string table, string datas[]) {
	return DatabaseHelper::save_user("admin", datas);
}

