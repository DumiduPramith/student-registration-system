#include "Management.h"

Management::Management():User("management") {}

void Management::view_registered_student(){}

bool Management::save_db(string table, string datas[]) {
	return DatabaseHelper::save_user("management", datas);
}