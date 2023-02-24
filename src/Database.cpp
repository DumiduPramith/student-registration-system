#include "Database.h"
#include<sqlite3.h>
#include<string>
#include<iostream>
#include <vector>
#include <openssl/sha.h>
#include<sstream>
#include<iomanip>

using namespace std;

std::vector<std::vector<char*>*> Database::data_lst;

sqlite3* Database::db;
sqlite3_stmt* Database::stmt;

bool Database::initialized = false;


Database::Database() {
	if (!initialized) {
		exit = sqlite3_open("test.db",&db);
		if (exit) {
			cout << "Cannot open database" << endl;
		}
		else {
			cout << "Database open success" << endl;
		}
		initialized = true;
	}
}


void Database::close_connection() {
	cout << "connection closed" << endl;
	sqlite3_close(db);
	sqlite3_free(error_msg);
}

int Database::createTable(string query){
	exit = sqlite3_exec(db, query.c_str(), NULL, 0, &error_msg);
	if (exit != SQLITE_OK) {
		cout << "Data Insertion Failed" << endl;
		sqlite3_free(error_msg);
	}
	else {
		cout << "Record created Successfully" << endl;
	}
	return 0;

}

int Database::insertData(string query){
	exit = sqlite3_exec(db, query.c_str(), NULL, 0, &error_msg);
	if (exit != SQLITE_OK) {
		cout << "Data Insertion Failed" << endl;
		sqlite3_free(error_msg);
	}
	else {
		cout << "Record created Successfully" << endl;
	}
	return 0;
}

int Database::select_data(string query){
	sqlite3_exec(db, query.c_str(), callback, NULL, NULL);
	/*clear_data_lst();
	for (int i = 0; i < data_lst.size(); i++) {
		for (int j = 0; j < data_lst[i]->size(); j++) {
			
			cout << data_lst[i]->at(j) << endl;
		}
	}*/
	return 0;
}

int Database::callback(void* NotUsed, int argc, char** argv, char** azColName) {
	std::vector<char*>* tmp= new std::vector<char*>();
	char* tmp_char;
	
	for (int i = 0; i < argc; i++) {
		tmp_char = new char[strlen(argv[i])+1];
		strcpy_s(tmp_char, strlen(argv[i])+1, argv[i]);
		tmp->push_back(tmp_char);
	}
	data_lst.push_back(tmp);

	return 0;
}


void Database::clear_data_lst() {
	for (int i = 0; i < static_cast<int>(data_lst.size()); i++) {
		for (int j = 0; j < static_cast<int>(data_lst[i]->size()); j++) {
			char* ptr = data_lst[i]->at(j);
			delete[] ptr;
		}
		data_lst.clear();
	}
}

std::string Database::gen_hashed_pword(std::string pword) {
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256((const unsigned char*)pword.c_str(), pword.length(), hash);

	// Convert the hash to a hexadecimal string
	std::stringstream ss;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
	}
	std::string hash_str = ss.str();

	return hash_str;
}
