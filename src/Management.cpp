#include "Management.h"

Management::Management():User("management") {}

void Management::view_registered_student(){}

bool Management::save_db(string datas[]) {
	return DatabaseHelper::save_user(role, datas);
}

bool Management::user_exists(string name) {
	return DatabaseHelper::find_user_exist(role, name);
}

int Management::get_userId() {
	return 0;
}