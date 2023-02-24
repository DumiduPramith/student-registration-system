#include "User.h"

User::User(string u_role):is_authenticated(0),role(u_role){}

User::~User(){}

bool User::login() {
	return true;
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