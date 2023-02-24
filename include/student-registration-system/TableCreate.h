#pragma once
#include "Database.h"

class TableCreate :
    public Database
{
private:
    
  
public:
    std::vector<std::string> table_lst{"student","admin","management","academic","course","student_course"};
    TableCreate();
    
    void create_student();
    void create_admin();
    void create_management();
    void create_academic();
    void create_course();
    void create_student_course();

    void run();
};

