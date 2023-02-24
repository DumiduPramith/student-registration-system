#include "Student.h"

Student::Student():User("student") {}

void Student::view_cources() {}

void Student::register_cource() {}
int Student::save_file() {
	return 0;
}

void Student::reg_user() {
	Student student;
	string uname;
	string email;
	string pword;
	cout << "Name:- "; cin >> uname;
	cout << "Email:- "; cin >> email;
	cout << "Password:- "; cin >> pword;
	student.set_username(uname);
	student.set_password(pword);
	student.set_email(email);
}
