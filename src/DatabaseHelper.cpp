#include "DatabaseHelper.h"

bool DatabaseHelper::save_user(std::string table, std::string datas[])
{
    int exit;
    std::string sql = "insert into "+ table+ "(username,email,password) values(?,?,?)";
    exit = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    exit |= sqlite3_bind_text(stmt, 1, datas[0].c_str(), -1, SQLITE_TRANSIENT);
    exit |= sqlite3_bind_text(stmt, 2, datas[1].c_str(), -1, SQLITE_TRANSIENT);
    std::string hashed_password = gen_hashed_pword(datas[2]);
    exit |= sqlite3_bind_text(stmt, 3, hashed_password.c_str(), -1, SQLITE_TRANSIENT);
    
    if (exit != SQLITE_OK) {
        // Handle error
        sqlite3_finalize(stmt);
        return false;
    }

    exit = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (exit != SQLITE_DONE) {
        // Handle error
        return false;
    }

    return true;
}


bool DatabaseHelper::find_user_exist(std::string table, std::string uname) {
    std::string sql = "SELECT COUNT(*) FROM "+ table + " WHERE username = ?";
 
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, uname.c_str(), -1, SQLITE_TRANSIENT);

    int result = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = sqlite3_column_int(stmt, 0);
    }
    const char* errmsg = sqlite3_errmsg(db);
    std::cout << "SQLite error message: " << errmsg << std::endl;
    sqlite3_finalize(stmt);
    if (result > 0) {
        return true;
    }
    return false;
}

std::string DatabaseHelper::get_login(std::string uname, std::string table){
    std::string sql = "select password from " + table + " where username= ?";
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, uname.c_str(), -1, SQLITE_TRANSIENT);

    std::string password = "";
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* pw = sqlite3_column_text(stmt, 0);
        if (pw != NULL) {
            password = std::string(reinterpret_cast<const char*>(pw));
        }
    }
    sqlite3_finalize(stmt);
    return password;
}

bool DatabaseHelper::find_course_exist(std::string course_code) {
    std::string sql = "SELECT COUNT(*) FROM course WHERE courseCode = ?";

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, course_code.c_str(), -1, SQLITE_TRANSIENT);

    int result = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = sqlite3_column_int(stmt, 0);
    }
    const char* errmsg = sqlite3_errmsg(db);
    std::cout << "SQLite error message: " << errmsg << std::endl;
    sqlite3_finalize(stmt);
    if (result > 0) {
        return true;
    }
    return false;
}


bool DatabaseHelper::create_course(std::string course_code, std::string course_name, std::string course_description){
    int exit;
    std::string sql = "insert into course(courseCode,courseTitle,Description) values(?,?,?)";
    exit = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    exit |= sqlite3_bind_text(stmt, 1, course_code.c_str(), -1, SQLITE_TRANSIENT);
    exit |= sqlite3_bind_text(stmt, 2, course_name.c_str(), -1, SQLITE_TRANSIENT);
    exit |= sqlite3_bind_text(stmt, 3, course_description.c_str(), -1, SQLITE_TRANSIENT);

    if (exit != SQLITE_OK) {
        // Handle error
        sqlite3_finalize(stmt);
       return false;
    }

    exit = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (exit != SQLITE_DONE) {
        // Handle error
        return false;
    }

    return true;
}

bool DatabaseHelper::register_course(int stu_id, int course_id) {
    int exit;
    std::string sql = "insert into student_course(stuId,courseId) values(?,?)";
    exit = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    exit |= sqlite3_bind_int(stmt, 1, stu_id);
    exit |= sqlite3_bind_int(stmt, 2, course_id);

    if (exit != SQLITE_OK) {
        // Handle error
        sqlite3_finalize(stmt);
        return false;
    }

    exit = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (exit != SQLITE_DONE) {
        // Handle error
        return false;
    }

    return true;
}

