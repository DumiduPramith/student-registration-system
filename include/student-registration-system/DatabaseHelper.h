#pragma once
#include "Database.h"
class DatabaseHelper :
    public Database
{
protected:
    bool save_user(std::string table, std::string datas[]);

    bool find_user_exist(std::string table, std::string uname);

    bool find_course_exist(std::string course_code);

    bool create_course(std::string course_code, std::string course_name, std::string course_description);
    
    std::string get_login(std::string uname, std::string table);

public:
    bool register_course(int stu_id, int course_id);
};

