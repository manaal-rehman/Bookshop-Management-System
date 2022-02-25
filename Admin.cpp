#include "Admin.h"

///Default constructor
Admin::Admin()
{
    login = "Default login";
    pswd = "Default password";
};

///Parameterized constructor
Admin::Admin(string log, string pass)
{
	login = log;
	pswd = pass;
}

///Returns login value
string Admin::get_login() const
{
	return login;
}

///Returns password value
string Admin::get_pswd() const
{
	return pswd;
}
