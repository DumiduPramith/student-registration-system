#include <iostream>
#include "TableCreate.h"
#include "Student.h"
#include "Admin.h"
#include "Management.h"
#include "Academic.h"
#include "Course.h"
#include "crow.h"
#include <vector>

using namespace std;


int main()
{
    crow::SimpleApp app;
    TableCreate tbl;
    //tbl.run();
    
    CROW_ROUTE(app, "/hello")
        ([]() {
        return "Hello world!";
            });

    CROW_ROUTE(app, "/api/register").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "Invalid body");
        }
        string role,username, email, password;
        try {
            role = body["role"].s();
            username = body["username"].s();
            email = body["email"].s();
            password = body["password"].s();
        }catch(const runtime_error &err){
            return crow::response(400, "Invalid body");
        }
        switch (stoi(role)) {
        case 1:
        {
            Student student;
            if (student.user_exists(username)) {
                return crow::response(409, "User already exist");
            }
            string datas[] = { username, email, password };
            student.save_db(datas);
            break;
        }
        case 2:
        {
            Academic academic;
            if (academic.user_exists(username)) {
                return crow::response(409, "User already exist");
            }
            string datas[] = { username, email, password };
            academic.save_db(datas);
            break;
        }
        case 3:
        {
            Management management;
            if (management.user_exists(username)) {
                return crow::response(409, "User already exist");
            }
            string datas[] = { username, email, password };
            management.save_db(datas);
            break;
        }
        case 4:
        {
            Admin admin;
            if (admin.user_exists(username)) {
                return crow::response(409, "User already exist");
            }
            string datas[] = { username, email, password };
            admin.save_db(datas);
            break;
        }
        }
        return crow::response(201, "success");
        });

    CROW_ROUTE(app, "/api/login").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        bool is_success = false;
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "Invalid body");
        }
        int role;
        string username, password;
        try {
            role = body["role"].i();
            username = body["username"].s();       
            password = body["password"].s();
            switch (role) {
            case 1:
            {
                Student student;
                student.set_username(username);
                is_success = student.login(password);
                break;
            }
            case 2:
            {
                Academic academic;
                is_success = academic.login(password);
                break;
            }
            case 3:
            {
                Management management;
                is_success = management.login(password);
                break;
            }
            case 4:
            {
                Admin admin;
                is_success = admin.login(password);
                break;
            }
            }
        }
        catch (const runtime_error& err) {
            return crow::response(400, "Invalid body");
        }
        if (is_success) {
            return crow::response(200, "success");
        }
        else {
            return crow::response(401, "failed");
        }
        });

    CROW_ROUTE(app, "/api/create-course").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "Invalid body");
        }
        string course_code,course_name,course_description;
        try {
            course_code = body["course-code"].s();
            course_name = body["course-name"].s();
            course_description = body["course-description"].s();
        }
        catch (const runtime_error& err) {
            return crow::response(400, "Invalid body");
        }
        Course course;
        course.course_code = course_code;
        course.course_name = course_name;
        course.course_description = course_description;
        course.create_course();
        return crow::response(201, "success");
        });
    
    CROW_ROUTE(app, "/api/register-course").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "Invalid body");
        }
        int userId;
        try {
            userId = body["user-id"].i();
            auto courses = body["courses"];
            Course course;
            for (auto courseId : courses) {
                course.register_course(userId, courseId.i());
            }
        }
        catch (const runtime_error& err) {
            return crow::response(400, "Invalid body");
        }
        return crow::response(201, "success");

        });


    CROW_ROUTE(app, "/api/get/reg-students")([]() {
        Academic academic;
        bool exit = academic.view_reg_students();
        std::vector<crow::json::wvalue> students;
        for (auto row : academic.data_lst) {
            auto stuId = row->at(0);
            auto username = row->at(1);
            auto email = row->at(2);
            students.push_back(crow::json::wvalue{
                {"student_id", stuId},
                {"username", username},
                {"email", email}
                });
        }
        academic.clear_data_lst();
        return crow::json::wvalue{ { "data", students } };
        });

    CROW_ROUTE(app, "/api/get/courses")([]() {
        Admin admin;
        bool exit = admin.get_all_cources();
        std::vector<crow::json::wvalue> cources;
        for (auto row : admin.data_lst) {
            auto courseId = row->at(0);
            auto courseCode = row->at(1);
            auto courseTitle = row->at(2);
            auto courseDescription = row->at(3);
            cources.push_back(crow::json::wvalue{
                {"course_id", courseId},
                {"course_code", courseCode},
                {"course_title", courseTitle},
                {"course_descrition", courseDescription}
                });
        }
        admin.clear_data_lst();
        return crow::json::wvalue{ { "data", cources } };
        });


    app.port(8080).run();
    tbl.close_connection();
}
