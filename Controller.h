#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "string"

using namespace std;

class Controller
{
protected:

public:
	///Display main menu of project
	void main_menu();

	///Display menu to add book
	void add_book_menu();

	///Function to log out
	void log_out_admin();

	///Display control panel
	void control_panel();

	///Display log-in screen and get login and password from user
	void log_in();

	///Display information about project developer
	void about();

	///Sell book by id and delete it from record
	void sell_book();

	///Find book by id
	void find_book();

	///Display cash box
	void display_cashbox();

private:
    ///Display main menu screen
    void main_menu_screen();

    ///Display login screen
    void login_screen();

    ///Take login from user
    void login_user(string &lgn);

    ///Take password from user
    void password_user(string &psw);

    ///Display wrong login screen
    void wrong_login_screen();

    ///Display control panel screen
    void control_panel_screen();

    ///Display add book menu screen
    void add_book_menu_screen();

    ///Display paper_book
    void display_paper_book(ifstream& f1, float& price);
    void display_paper_book(ifstream& f1);

    ///Display Audio_cd_book
    void display_Audio_cd_book(ifstream& f2, float& price);
    void display_Audio_cd_book(ifstream& f2);

    ///Display Digital_book
    void display_digital_book(ifstream& f3, float& price);
    void display_digital_book(ifstream& f3);

    ///Display book not found screen
    void display_not_found_screen();
};


#endif
