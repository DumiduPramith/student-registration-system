#include "TableCreate.h"
#include <string>

TableCreate::TableCreate() {

}


void TableCreate::create_student() {
	std::string sql = "CREATE TABLE student("
		"stuId INTEGER PRIMARY KEY AUTOINCREMENT,"
		"username VARCHAR(15) UNIQUE NOT NULL,"
		"email VARCHAR(30) NOT NULL,"
		"password TEXT"
		")";
	createTable(sql);
}

void TableCreate::create_admin() {
	std::string sql = "CREATE TABLE admin("
		"adminId INTEGER PRIMARY KEY AUTOINCREMENT,"
		"username VARCHAR(15) UNIQUE NOT NULL,"
		"email VARCHAR(30) NOT NULL,"
		"password TEXT"
		")";
	createTable(sql);
}

void TableCreate::create_management() {
	std::string sql = "CREATE TABLE management("
		"managementId INTEGER PRIMARY KEY AUTOINCREMENT,"
		"username VARCHAR(15) UNIQUE NOT NULL,"
		"email VARCHAR(30) NOT NULL,"
		"password TEXT"
		")";
	createTable(sql);
}


void TableCreate::create_academic() {
	std::string sql = "CREATE TABLE academic("
		"academicId INTEGER PRIMARY KEY AUTOINCREMENT,"
		"username VARCHAR(15) UNIQUE NOT NULL,"
		"email VARCHAR(30) NOT NULL,"
		"password TEXT"
		")";
	createTable(sql);
}

void TableCreate::create_course() {
	std::string sql = "CREATE TABLE course("
		"courseId INTEGER PRIMARY KEY AUTOINCREMENT,"
		"courseCode VARCHAR(10) UNIQUE NOT NULL,"
		"courseTitle VARCHAR(50) NOT NULL,"
		"description TEXT"
		")";
	createTable(sql);
}

void TableCreate::create_student_course() {
	std::string sql = "create table student_course("
		"stuId integer not null,"
		"courseId INT NOT NULL,"
		"PRIMARY KEY(stuId, courseId),"
		"FOREIGN KEY(stuId) REFERENCES student(stuId),"
		"FOREIGN KEY(courseId) REFERENCES course(courseId)"
		")";
	createTable(sql);
}

void TableCreate::create_default_admin() {
	std::string password = "admin";
	std::string hashed_password = Database::gen_hashed_pword(password);
	std::string sql = "INSERT INTO admin(username,email,password) values "
		"(\"admin\",\"admin@example.com\",\"" + hashed_password + "\")";
	Database::insertData(sql);
}

void TableCreate::run() {
	int exit;
	const char* query = "SELECT name FROM sqlite_master WHERE type='table' AND name=?;";
	sqlite3_prepare_v2(db, query, -1, &stmt, NULL);

	for (int i = 0; i < table_lst.size(); i++) {
		sqlite3_bind_text(stmt, 1, table_lst[i].c_str(), -1, SQLITE_TRANSIENT);
		if (sqlite3_step(stmt) != SQLITE_ROW) {
			if (table_lst[i] == "student") {
				create_student();
			}
			else if (table_lst[i] == "admin") {
				create_admin();
				create_default_admin();
			}
			else if (table_lst[i] == "management") {
				create_management();
			}
			else if (table_lst[i] == "academic") {
				create_academic();
			}
			else if (table_lst[i] == "course") {
				create_course();
			}
			else if (table_lst[i] == "student_course") {
				create_student_course();
			}
		}
		sqlite3_reset(stmt);
	}

	sqlite3_finalize(stmt);
}

