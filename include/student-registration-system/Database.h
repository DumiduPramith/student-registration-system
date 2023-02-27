#pragma once
#include <iostream>
#include<string>
#include<sqlite3.h>
#include<vector>


class Database
{
private:
	
	int exit;
	char* error_msg;
	static bool initialized;
public:
	Database();
	
	void close_connection();

	int createTable(std::string query);
	int insertData(std::string query);
	int select_data(std::string query);
	std::string gen_hashed_pword(std::string);
	static std::vector<std::vector<char*>*> data_lst;
	void clear_data_lst();

protected:
	static sqlite3* db;
	static sqlite3_stmt* stmt;
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
};

