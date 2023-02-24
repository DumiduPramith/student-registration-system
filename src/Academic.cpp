#include "Academic.h"


Academic::Academic():User("academic") {}


bool Academic::save_db(string table, string datas[]) {
	return DatabaseHelper::save_user("academic", datas);
}