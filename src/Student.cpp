#include "Student.h"

Student::Student():User("student") {}

bool Student::get_registered_cources() {
	std::string sql = "select c.courseId, c.courseCode, c.courseTitle, c.description "
		"FROM course c "
		"JOIN student_course sc ON c.courseId = sc.courseId "
		"JOIN student s ON s.stuId = sc.stuId "
		"WHERE s.username = \"" + username + "\"";
	Database::select_data(sql);
	return true;
}

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

int Student::get_userId() {
	std::string sql = "select stuId from " + role + " where username= ?";
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

	sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);

	int userid = 0;
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		int id = sqlite3_column_int(stmt, 0);
		if (id != NULL) {
			userid = id;
		}
	}
	sqlite3_finalize(stmt);
	return userid;
}


bool Student::remove_registered_cources(int userId, int courseId) {
	int exit;
	std::string sql = "DELETE FROM student_course WHERE stuId = ? and courseId = ?";
	exit = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);


	exit |= sqlite3_bind_int(stmt, 1, userId);
	exit |= sqlite3_bind_int(stmt, 2, courseId);
	if (exit != SQLITE_OK) {
		// Handle error
		sqlite3_finalize(stmt);
		return false;
	}
	int result = sqlite3_step(stmt);
	if (result == SQLITE_DONE) {
		std::cout << "Deleted " << sqlite3_changes(db) << " rows." << std::endl;
	}
	else if (result == SQLITE_ERROR) {
		// Handle error
		std::cout << "Failed to execute query: " << sqlite3_errmsg(db) << std::endl;
	}
	sqlite3_finalize(stmt);
	return 1;
}