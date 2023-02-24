#include <iostream>
#include "TableCreate.h"
#include "Student.h"
#include "Admin.h"
#include "Management.h"
#include "Academic.h"
#include "crow.h"

using namespace std;


int main()
{
    crow::SimpleApp app;
    TableCreate tbl;
    tbl.run();
    
    CROW_ROUTE(app, "/hello")
        ([]() {
        return "Hello world!";
            });

    CROW_ROUTE(app, "/api/register").methods(crow::HTTPMethod::POST)([&](const crow::request& req) {
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
            Student student;
            if (student.user_exists(username)) {
                return crow::response(409,"User already exist");
            }
            string datas[] = { username, email, password };
            student.save_db(datas);
        }
        return crow::response(201, "success");
        });

    app.port(8080).run();
    tbl.close_connection();
}
