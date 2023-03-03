#include <iostream>
#include "TableCreate.h"
#include "Student.h"
#include "Admin.h"
#include "Management.h"
#include "Academic.h"
#include "Course.h"
#include "crow.h"
#include "nlohmann/json.hpp"
#include <vector>
#include <fstream>


using namespace std;
using json = nlohmann::json;

void sendSuccessResponse(crow::response& res, int res_code, string data) {
    json myJson = {
        {"success", true},
        {"data", data}
    };

    std::string jsonString = myJson.dump();

    res.set_header("Content-Type", "application/json");
    res.set_header("Cache-Control", "no-cache");
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
    res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    res.code = res_code;
    res.write(jsonString);
    //res.end();
}

void sendErrorResponse(crow::response& res, int res_code, string data) {
    json myJson = {
        {"success", false},
        {"data", data}
    };

    std::string jsonString = myJson.dump();

    res.set_header("Content-Type", "application/json");
    res.set_header("Cache-Control", "no-cache");
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
    res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    res.code = res_code;
    res.write(jsonString);
    //res.end();
}

int main()
{

    crow::SimpleApp app;
    TableCreate tbl;
    tbl.run();


    CROW_ROUTE(app, "/api/register").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        crow::response res;
        
       if (!body) {
            sendErrorResponse(res, 400, "Invalid body");
            return res;
            
        }
        string role,username, email, password;
        try {
            role = body["role"].s();
            username = body["username"].s();
            email = body["email"].s();
            password = body["password"].s();
        }catch(const runtime_error &err){
            sendErrorResponse(res, 400, "Invalid body");
            return res;
        }
        switch (stoi(role)) {
        case 1:
        {
            Student student;
            if (student.user_exists(username)) {
                sendErrorResponse(res, 409, "User already exist");
                return res;
                
            }
            string datas[] = { username, email, password };
            student.save_db(datas);
            break;
        }
        case 2:
        {
            Academic academic;
            if (academic.user_exists(username)) {
                sendErrorResponse(res, 409, "User already exist");
                return res;                
            }
            string datas[] = { username, email, password };
            academic.save_db(datas);
            break;
        }
        case 3:
        {
            Management management;
            if (management.user_exists(username)) {
                sendErrorResponse(res, 409, "User already exist");
                return res;
            }
            string datas[] = { username, email, password };
            management.save_db(datas);
            break;
        }
        case 4:
        {
            Admin admin;
            if (admin.user_exists(username)) {
                sendErrorResponse(res, 409, "User already exist");
                return res;
            }
            string datas[] = { username, email, password };
            admin.save_db(datas);
            break;
        }
        }

        sendSuccessResponse(res, 201, "success");
        return res;
        });

    CROW_ROUTE(app, "/api/login").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        bool is_success = false;
        crow::response res;
        auto body = crow::json::load(req.body);
        if (!body) {
            sendErrorResponse(res, 400, "Invalid Body");
            
        }
        int role;
        string username, password;
        int userId;
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
                if (is_success) {
                    userId = student.get_userId();
                }
                break;
            }
            case 2:
            {
                Academic academic;
                academic.set_username(username);
                is_success = academic.login(password);
                if (is_success) {
                    userId = academic.get_userId();
                }
                break;
            }
            case 3:
            {
                Management management;
                management.set_username(username);
                is_success = management.login(password);
                if (is_success) {
                    userId = management.get_userId();
                }
                break;
            }
            case 4:
            {
                Admin admin;
                admin.set_username(username);
                is_success = admin.login(password);
                if (is_success) {
                    userId = admin.get_userId();
                }
                break;
            }
            }
        }
        catch (const runtime_error& err) {
            sendErrorResponse(res, 400, "Invalid body");
            return res;
        }
        if (is_success) {
            json myJson = {
                {"userId" , userId},
                {"msg","Success"}
            };
            string jsonString = myJson.dump();
            sendSuccessResponse(res, 200, jsonString);
            return res;
        }
        else {
            sendErrorResponse(res, 401, "password not matched");
            return res;
        }
        });

    CROW_ROUTE(app, "/api/create-course").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        crow::response res;
        if (!body) {
            sendErrorResponse(res, 400, "Invalid Body");
            return res;
        }
        string course_code,course_name,course_description;
        try {
            course_code = body["course_code"].s();
            course_name = body["course_name"].s();
            course_description = body["course_description"].s();
        }
        catch (const runtime_error& err) {
            sendErrorResponse(res, 400, "Invalid Body");
            return res;
        }
        Course course;
        course.course_code = course_code;
        course.course_name = course_name;
        course.course_description = course_description;
        course.create_course();
        sendSuccessResponse(res, 201, "Suceess");
        return res;
        });
    
    CROW_ROUTE(app, "/api/register-course").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        crow::response res;
        if (!body) {
            sendErrorResponse(res, 400, "Invalid body");
            return res;
        }
        int userId;
        try {
            userId = body["user_id"].i();
            auto courses = body["courses"];
            Student student;
            for (auto courseId : courses) {
                student.register_course(userId, courseId.i());
            }
        }
        catch (const runtime_error& err) {
            sendErrorResponse(res, 400, "Invalid body");
            return res;
        }
        sendSuccessResponse(res, 201, "success");
        return res;
        });
  
    CROW_ROUTE(app, "/api/remove-register-course").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        crow::response res;
        if (!body) {
            sendErrorResponse(res, 400, "Invalid body");
            return res;
        }
        int userId;
        try {
            userId = body["user_id"].i();
            auto courses = body["courses"];
            Student student;
            for (auto courseId : courses) {
                student.remove_registered_cources(userId, courseId.i());
            }
        }
        catch (const runtime_error& err) {
            sendErrorResponse(res, 400, "Invalid body");
            return res;
        }
        sendSuccessResponse(res, 201, "success");
        return res;
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
        crow::json::wvalue data{ {"data", students}};
        crow::response res(200, data);
        res.set_header("Content-Type", "application/json");
        res.set_header("Cache-Control", "no-cache");
        res.set_header("Access-Control-Allow-Origin", "*");
        return res;
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
                {"course_description", courseDescription}
                });
        }
        admin.clear_data_lst();
        crow::json::wvalue data{ {"data", cources} };
        crow::response res(200, data);
        res.set_header("Content-Type", "application/json");
        res.set_header("Cache-Control", "no-cache");
        res.set_header("Access-Control-Allow-Origin", "*");
        return res;
        });

    CROW_ROUTE(app, "/api/get/selected-courses")([](const crow::request& req) {
        Student student;
        try {
            auto username = req.url_params.get("username");
            string tmp(username);
            student.set_username(tmp);
            student.get_registered_cources();
        }
        catch (const runtime_error& err) {}
        std::vector<crow::json::wvalue> cources;
        for (auto row : student.data_lst) {
            auto courseId = row->at(0);
            auto courseCode = row->at(1);
            auto courseTitle = row->at(2);
            auto courseDescription = row->at(3);
            cources.push_back(crow::json::wvalue{
                {"course_id", courseId},
                {"course_code", courseCode},
                {"course_title", courseTitle},
                {"course_description", courseDescription}
                });
        }
        student.clear_data_lst();
        crow::json::wvalue data{ {"data", cources} };
        crow::response res(200, data);
        res.set_header("Content-Type", "application/json");
        res.set_header("Cache-Control", "no-cache");
        res.set_header("Access-Control-Allow-Origin", "*");
        return res;
        });


    app.port(8080).run();
    tbl.close_connection();
}
