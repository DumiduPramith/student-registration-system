#include "User.h"

User::User(string u_role):is_authenticated(0),role(u_role){}

User::~User(){}

bool User::login(string login_pword) {
	string pword;
	pword = DatabaseHelper::get_login(username, role);
	string login_hashed = Database::gen_hashed_pword(login_pword);
	if (login_hashed == pword) {
		return true;
	}
	else {
		return false;
	}
}

void User::set_username(string uname) {
	User::username = uname;
}

void User::set_password(string pword){
	User::password = pword;
}

void User::set_email(string mail){
	User::email = mail;
}