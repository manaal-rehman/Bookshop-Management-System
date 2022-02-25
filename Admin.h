#ifndef ADMIN_H
#define ADMIN_H

#include <string>

using namespace std;

class Admin
{
public:
	///Default constructor
	Admin();

	///Parameterized constructor
	Admin(string log, string pass);

	///Returns login value
	string get_login() const;

	///Returns password value
	string get_pswd() const;

private:
	string login;   ///variable to hold login value
	string pswd;    ///variable to hold password value
};

#endif
