#include "Controller.h"
#include "Cashbox.h"
#include "Books.h"
#include "Animation.h"
#include "Admin.h"

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>

using namespace std;

///Display main menu of project
void Controller::main_menu()
{
    main_menu_screen();

	while (true)
	{
        char ch = getch();
		switch (ch)
		{
			case '1':
				system("cls");
				log_in();
				break;
			case '2':
				system("cls");
				about();
				break;
			default:
				system("cls");
				Animation::exit();
				exit(1);
        }
	}
}

///Display log-in screen and get login and password from user
void Controller::log_in()
{
	string lgn, psw;

	login_screen();

	Animation::colorize_text("\t\t\t\t    Login: ", 14);
	login_user(lgn);

	Animation::colorize_text("\r\t\t\t\t    Password: ", 14);
	password_user(psw);

    ///Reading login and password from file
    string login, passwd;
	ifstream Administration;
	Administration.open("Admin.txt", ios::in);
	Administration >> login;
	Administration >> passwd;
	Administration.close();
	Admin admin(login, passwd);

    ///Checking if the login or password wrong
	if (lgn != admin.get_login() || psw != admin.get_pswd())
	{
		system("cls");
		wrong_login_screen();
		Sleep(1000);
		system("cls");
		log_in();
	}

	///Go to next menu
	system("cls");
	Animation::initializing();
	control_panel();
}


///Display control panel
void Controller::control_panel()
{
	control_panel_screen();

	while (true)
	{
        char ch = getch();
		switch (ch)
		{
			case '1':
				add_book_menu();
				break;
			case '2':
				sell_book();
				break;
			case '3':
				find_book();
				break;
			case '4':
			    display_cashbox();
				break;
			case '0':
				log_out_admin();
				break;
        }
	}
}

//Log out function for admin
void Controller::log_out_admin()
{
	//Asks user the permission to exit from account
	system("cls");
	int color = 10;

	cout << endl;
	Animation::draw_border(30, color);
	Animation::frame_phrase("                          ", color);
	Animation::frame_phrase("       Are you sure?      ", color);
	Animation::frame_phrase("    Y -> Yes | N <- No    ", color);
	Animation::frame_phrase("                          ", color);
	Animation::draw_border(30, color);

	while (true)
	{
        char ch = getch();
		switch (ch)
		{
			case 'Y':
			case 'y':
				system("cls");
				main_menu();
				break;
			case 'N':
			case 'n':
				system("cls");
				control_panel();
				break;
		}
	}
}

//add book menu
void Controller::add_book_menu()
{
  	Book* b;

    add_book_menu_screen();
	while (true)
	{
		char ch = getch();
		switch (ch)
		{
			case '1':
			    b = new Paper_book;
				b->add_book();
				delete b;
				break;
			case '2':
			    b = new Audio_cd;
				b->add_book();
				delete b;
				break;
			case '3':
			    b = new Digital_book;
				b->add_book();
				delete b;
				break;
			default:
				control_panel();
				break;
		}
	}
}

///Sell book by id and delete it from record
void Controller::sell_book()
{
	system("cls");
	int color = 10;
	int color_lightblue = 14;
	float price;
	int id = -1 ;

	Animation::draw_border(62, color);
	Animation::colorize_text("\t\t\t\t             System needs ID of book to sell       \n", color_lightblue);
	Animation::draw_border(62, color);
	cout << endl;

	while (id < 0 )
	{
		Animation::colorize_text("\t\t\t\t    Sell by ID: ", color_lightblue);
		cin >> id;
	}
	system("cls");

	string n1 = "DataBase/Paper Books/book - " + to_string(id) + ".info";
	string n2 = "DataBase/Audio CD/book - " + to_string(id) + ".info";
	string n3 = "DataBase/Digital Books/book - " + to_string(id) + ".info";

	ifstream f1;
	f1.open(n1, ios::in);

	if (f1.is_open())
	    display_paper_book(f1, price);

	ifstream f2;
	f2.open(n2, ios::in);

	if (f2.is_open())
	    display_Audio_cd_book(f2, price);

	ifstream f3;
	f3.open(n3, ios::in);
	if (f3.is_open())
        display_digital_book(f3, price);

	if (f3.is_open() | f1.is_open() | f2.is_open())
	{
		Animation::draw_border(61, color);
		Animation::frame_phrase("                                                         ", color);
		Animation::frame_phrase("        This action will delete book from database       ", color);
		Animation::frame_phrase("                 Are you sure about that?                ", color);
		Animation::frame_phrase("                                                         ", color);
		Animation::frame_phrase("                   Y <- Yes | NO -> N                    ", color);
		Animation::frame_phrase("                                                         ", color);
		Animation::draw_border(61, color);

		while (true)
		{
			char ch = getch();
			switch (ch)
			{
				case 'Y':
				case 'y':
					system("cls");
					if (f1.is_open())
					{
						f1.close();
						remove(n1.c_str());
					}
					if (f2.is_open())
					{
						f2.close();
						remove(n2.c_str());
					}
					if (f3.is_open())
					{
						f3.close();
						remove(n3.c_str());
					}

					Cashbox::update_cashbox(price);

					system("cls");
					Animation::draw_border(61, color);
					Animation::frame_phrase("                                                         ", color);
					Animation::frame_phrase("              Book was deleted from database             ", color);
					Animation::frame_phrase("                                                         ", color);
					Animation::draw_border(61, color);
					Sleep(1500); ///wait for 1500 milliseconds
					control_panel();
					break;
				case 'N':
				case 'n':
					system("cls");
					control_panel();
					break;
				default:
					system("cls");
					control_panel();
            }//switch close
		}//while close
	}//if close
	else
	    display_not_found_screen();
}//function close

///Find book by id
void Controller::find_book()
{
	system("cls");
	int color = 10;
	int color_lightblue = 14;
	int id;

	Animation::draw_border(62, color);
	Animation::colorize_text("\t\t\t\t             System needs ID to find a book       \n", color_lightblue);
	Animation::draw_border(62, color);
	cout << endl;

    Animation::colorize_text("\t\t\t\t    Find by ID: ", color_lightblue);
	cin >> id;

	try
	{
	    if (id < 0)
            throw (id);
	} //end of try block
	catch (int thrownValue) // start of catch block
	{
	    cout << endl;
	    Animation::colorize_text("Exception caught. Id cannot be negative", 4);
		cout << endl;
	    Sleep(2000);
	    find_book();
	} // end of catch block

	system("cls");

	string n1 = "DataBase/Paper Books/book - " + to_string(id) + ".info";
	string n2 = "DataBase/Audio CD/book - " + to_string(id) + ".info";
	string n3 = "DataBase/Digital Books/book - " + to_string(id) + ".info";

	ifstream f1;
	f1.open(n1, ios::in);

	if (f1.is_open())
        display_paper_book(f1);

	ifstream f2;
	f2.open(n2, ios::in);

	if (f2.is_open())
        display_Audio_cd_book(f2);

	ifstream f3;
	f3.open(n3, ios::in);
	if (f3.is_open())
        display_digital_book(f3);

	if (f3.is_open() | f1.is_open() | f2.is_open())
	{
        Animation::draw_border(61, color);
        Animation::frame_phrase("                                                         ", color);
        Animation::frame_phrase("                    Any key to go back                   ", color);
        Animation::frame_phrase("                     to control panel                    ", color);
        Animation::frame_phrase("                                                         ", color);
        Animation::draw_border(61, color);
        f1.close();
        f2.close();
        f3.close();

        while (true)
        {
            getch();
            system("cls");
            control_panel();
        }
	}//if close
	else
        display_not_found_screen();
}

///Display information about project developer
void Controller::about()
{
	int color = 10;

    cout << endl;
	Animation::draw_border(56, color);
	Animation::frame_phrase("                                                    ", color);
	Animation::frame_phrase("                    Final Project                   ", color);
	Animation::frame_phrase("                                                    ", color);
	Animation::draw_border(56, color);
	Animation::frame_phrase("                                                    ", color);
	Animation::frame_phrase("     Course Title: Object Oriented Programming      ", color);
	Animation::frame_phrase("              Teacher: Amber Madeeha Zeb            ", color);
	Animation::frame_phrase("                                                    ", color);
	Animation::frame_phrase("                     Made by:                       ", color);
	Animation::frame_phrase("                                                    ", color);
	Animation::frame_phrase("            Manaal Waseem - FA18-BCE-074            ", color);
	Animation::frame_phrase("                                                    ", color);
	Animation::frame_phrase("                                                    ", color);
	Animation::draw_border(56, color);

	while (true)
	{
		getch();
        system("cls");
		main_menu();
	}
}

///Display main menu screen
void Controller::main_menu_screen()
{
    int color = 10; ///Black background, Light green foreground
	cout << endl;
	Animation::draw_border(36, color);
	Animation::frame_phrase("                                ", color);
	Animation::frame_phrase("        Manaal Book shop        ", color);
	Animation::frame_phrase("                                ", color);
	Animation::draw_border(36, color);
	Animation::frame_phrase("                                ", color);
	Animation::frame_phrase("           1.  Login            ", color);
	Animation::frame_phrase("           2.  About            ", color);
	Animation::frame_phrase("                                ", color);
	Animation::frame_phrase("    Press any other to Exit     ", color);
	Animation::frame_phrase("                                ", color);
	Animation::draw_border(36, color);
}

///Display login screen
void Controller::login_screen()
{
    int color = 10;     ///Black background, Light green foreground

    cout << endl;
	Animation::draw_border(32, color);
	Animation::frame_phrase("                            ", color);
	Animation::frame_phrase("       Login as admin       ", color);
	Animation::frame_phrase("                            ", color);
	Animation::draw_border(32, color);
	cout << endl;
}

///Take login from user
void Controller::login_user(string &lgn)
{
    char c;
    while ((c = getch()) != '\r')
	{
		if (c == 27)    //ESC key
		{
			system("cls");
			log_in();
		}
		if (c == 8) //backspace
		{
			if (lgn.length() == 0)
				continue;
			cout << '\b' << " " << '\b';
			lgn = lgn.substr(0, lgn.length() - 1);
			continue;
		}
		if (((c >= 48) && (c <= 57)) || ((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122)))    //(0-9) or (A-Z) or (a-z)
		{
			lgn += c;
			cout << c;
		}
	}
	cout << endl;
}

///Take password from user
void Controller::password_user(string &psw)
{
    char c;
    	while ((c = getch()) != '\r')
	{
		if (c == 27)    //ESC  key
		{
			system("cls");
			log_in();
		}
		if (c == 8) //backspace
		{
			if (psw.length() == 0)
				continue;
			cout << '\b' << " " << '\b';
			psw = psw.substr(0, psw.length() - 1);
			continue;
		}
		if (((c >= 48) && (c <= 57)) || ((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122)))    //(0-9) or (A-Z) or (a-z)
		{
			psw += c;
			cout << "*";        ///Hiding the password with '*'
		}
	}
}

///Display wrong login screen
void Controller::wrong_login_screen()
{
    int color = 10;     ///Black background, Light green foreground

    cout << endl;
    Animation::draw_border(32, color);
	Animation::frame_phrase("                            ", color);
	Animation::frame_phrase("  Wrong login or password!  ", color);
	Animation::frame_phrase("                            ", color);
	Animation::draw_border(32, color);
}

///Display control panel screen
void Controller::control_panel_screen()
{
    int color =  10;
	int color_lightblue = 14;
	int color_white = 15;

	system("cls");
	cout << endl;
	Animation::draw_border(39, color);
	Animation::frame_phrase("                                   ", color);
	Animation::frame_phrase("           CONTROL PANEL           ", color);
	Animation::frame_phrase("                                   ", color);
	Animation::draw_border(39, color);
	Animation::frame_phrase("                                   ", color);
	cout << "\t\t\t        ";
	Animation::points();
	Animation::colorize_text("	    1.", color_lightblue);
	Animation::colorize_text(" Add new book  ", color_white);
	cout << "        ";
	Animation::points();
	cout << endl;
	cout << "\t\t\t        ";
	Animation::points();
	Animation::colorize_text("	    2.", color_lightblue);
	Animation::colorize_text(" Sell book     ", color_white);
	cout << "        ";
	Animation::points();
	cout << endl;
	cout << "\t\t\t        ";
	Animation::points();
	Animation::colorize_text("	    3.", color_lightblue);
	Animation::colorize_text(" Search book   ", color_white);
	cout << "        ";
	Animation::points();
	cout << endl;
	cout << "\t\t\t        ";
	Animation::points();
	Animation::colorize_text("	    4.", color_lightblue);
	Animation::colorize_text(" Check cashbox ", color_white);
	cout << "        ";
	Animation::points();
	cout << "        ";
	cout << endl;
	cout << "\t\t\t        ";
	Animation::points();
	cout << "                                   ";
	Animation::points();
	cout << endl;
	cout << "\t\t\t        ";
	Animation::points();
	Animation::colorize_text("	    0.", color_lightblue);
	Animation::colorize_text(" Log out       ", color_white);
	cout << "        ";
	Animation::points();
	cout << endl;
	cout << "\t\t\t        ";
	Animation::points();
	cout << "                                   ";
	Animation::points();
	cout << endl;
	Animation::draw_border(39, color);
}

///Display cash box
void Controller::display_cashbox()
{
    Cashbox cash;
    int color =  10;
    system("cls");
				Animation::draw_border(40, color);
				Animation::colorize_text("\t\t                    Cashbox in bookshop was checked            \n", 14);
				Animation::draw_border(40, color);
				cout << endl;
				cout << "\t\t\t\tSum of money: " << cash; ///implementation of operator overloading
				cout << endl;
				cout << endl;
				Animation::draw_border(40, color);
				Animation::frame_phrase("                                    ", color);
				Animation::frame_phrase("         Any key to go back         ", color);
				Animation::frame_phrase("          to control panel          ", color);
				Animation::frame_phrase("                                    ", color);
				Animation::draw_border(40, color);
				while (true)
				{
					getch();
					system("cls");
					control_panel();
				}
}

///Display add book menu screen
void Controller::add_book_menu_screen()
{
    system("cls");
	int color = 10;
	cout << endl;
	Animation::draw_border(30, color);
	Animation::frame_phrase("                          ", color);
	Animation::frame_phrase("       TYPE OF BOOK       ", color);
	Animation::frame_phrase("                          ", color);
	Animation::draw_border(30, color);
	Animation::frame_phrase("                          ", color);
	Animation::frame_phrase("     1. Paper book        ", color);
	Animation::frame_phrase("     2. Audio book        ", color);
	Animation::frame_phrase("     3. Digital book      ", color);
	Animation::frame_phrase("                          ", color);
	Animation::frame_phrase(" Any other key to GO BACK ", color);
	Animation::frame_phrase("                          ", color);
	Animation::draw_border(30, color);
}

///Display paper_book
void Controller::display_paper_book(ifstream& f1, float& price)
{
    string line;
    int color = 10;
	int color_lightblue = 14;

    Animation::draw_border(61, color);
    Animation::colorize_text("\t\t\t\t                  Info about book with this ID         \n", 3);
	Animation::draw_border(61, color);
	cout << endl;
	Animation::colorize_text("\t\t\t\t    Type: ", color_lightblue);
	Animation::colorize_text(" Paper Book ", 3);
	Animation::colorize_text("\t\t    ID: ", 3);
	getline(f1, line);
	cout << line;
	cout << endl;
	Animation::colorize_text("\t\t\t\t    Title: ", color_lightblue);
	getline(f1, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Release date: ", color_lightblue);
	getline(f1, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Author: ", color_lightblue);
	getline(f1, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    genre: ", color_lightblue);
	getline(f1, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Edition: ", color_lightblue);
	getline(f1, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Language: ", color_lightblue);
	getline(f1, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Rating (1 -> 10): ", color_lightblue);
	getline(f1, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Price: ", color_lightblue);
	getline(f1, line);
	price = strtof((line).c_str(), 0);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Publisher: ", color_lightblue);
	getline(f1, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Volume in pages: ", color_lightblue);
	getline(f1, line);
	cout << line << endl;
	cout << endl;
	cout << endl;
}
///Display Audio_cd_book
void Controller::display_Audio_cd_book(ifstream& f2, float& price)
{
    int color = 10;
	int color_lightblue = 14;
	string line;

    Animation::draw_border(61, color);
	Animation::colorize_text("\t\t\t\t                  Info about book with this ID         \n", 3);
	Animation::draw_border(61, color);
	cout << endl;
	Animation::colorize_text("\t\t\t\t    Type: ", color_lightblue);
	Animation::colorize_text(" Audio CD Book", 3);
	Animation::colorize_text("\t\t    ID: ", 03);
	getline(f2, line);
	cout << line;
	cout << endl;
	Animation::colorize_text("\t\t\t\t    Title: ", color_lightblue);
    getline(f2, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Release date: ", color_lightblue);
	getline(f2, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Author: ", color_lightblue);
	getline(f2, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    genre: ", color_lightblue);
	getline(f2, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Edition: ", color_lightblue);
	getline(f2, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Language: ", color_lightblue);
	getline(f2, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Rating (1 -> 10): ", color_lightblue);
	getline(f2, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Price: ", color_lightblue);
	getline(f2, line);
	price = strtof((line).c_str(), 0);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Voice: ", color_lightblue);
	getline(f2, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Listening lenth: ", color_lightblue);
	getline(f2, line);
	cout << line << endl;
	cout << endl;
	cout << endl;
}

///Display Digital_book
void Controller::display_digital_book(ifstream& f3, float& price)
{
    int color = 10;
	int color_lightblue = 14;
	string line;

	Animation::draw_border(61, color);
		Animation::colorize_text("\t\t\t\t                  Info about book with this ID         \n", 3);
		Animation::draw_border(61, color);
		cout << endl;
		Animation::colorize_text("\t\t\t\t    Type: ", color_lightblue);
		Animation::colorize_text(" Digital Book ", 3);
		Animation::colorize_text("\t\t    ID: ", 03);
		getline(f3, line);
		cout << line;
		cout << endl;
		Animation::colorize_text("\t\t\t\t    Title: ", color_lightblue);
		getline(f3, line);
		cout << line << endl;
		Animation::colorize_text("\t\t\t\t    Release date: ", color_lightblue);
		getline(f3, line);
		cout << line << endl;
		Animation::colorize_text("\t\t\t\t    Author: ", color_lightblue);
		getline(f3, line);
		cout << line << endl;
		Animation::colorize_text("\t\t\t\t    genre: ", color_lightblue);
		getline(f3, line);
		cout << line << endl;
		Animation::colorize_text("\t\t\t\t    Edition: ", color_lightblue);
		getline(f3, line);
		cout << line << endl;
		Animation::colorize_text("\t\t\t\t    Language: ", color_lightblue);
		getline(f3, line);
		cout << line << endl;
		Animation::colorize_text("\t\t\t\t    Rating (1 -> 10): ", color_lightblue);
		getline(f3, line);
		cout << line << endl;
		Animation::colorize_text("\t\t\t\t    Price: ", color_lightblue);
		getline(f3, line);
		price = strtof((line).c_str(), 0);
		cout << line << endl;
		cout << endl;
		cout << endl;
}

///Display book not found screen
void Controller::display_not_found_screen()
{
    int color = 10;

    system("cls");
    cout << endl;
    Animation::draw_border(61, color);
	Animation::frame_phrase("                                                         ", color);
	Animation::frame_phrase("         We could not found a book with this ID!         ", color);
	Animation::frame_phrase("                                                         ", color);
	Animation::draw_border(61, color);
	Sleep(2000); ///wait for 2000 milliseconds
	control_panel();
}

///Display paper_book
void Controller::display_paper_book(ifstream& f1)
{
    int color = 10;
    int color_lightblue = 14;
    string line;

    Animation::draw_border(61, color);
	Animation::colorize_text("\t\t\t\t                  Info about book with this ID         \n", 3);
	Animation::draw_border(61, color);
	cout << endl;
	Animation::colorize_text("\t\t\t\t    Type: ", color_lightblue);
	Animation::colorize_text(" Paper Book ", 3);
	Animation::colorize_text("\t\t    ID: ", 3);
	getline(f1, line);
	cout << line;
	cout << endl;
    Animation::colorize_text("\t\t\t\t    Title: ", color_lightblue);
	getline(f1, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Release date: ", color_lightblue);
	getline(f1, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Author: ", color_lightblue);
	getline(f1, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    genre: ", color_lightblue);
    getline(f1, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Edition: ", color_lightblue);
	getline(f1, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Language: ", color_lightblue);
	getline(f1, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Rating (1 -> 10): ", color_lightblue);
	getline(f1, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Price: ", color_lightblue);
	getline(f1, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Publisher: ", color_lightblue);
	getline(f1, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Volume in pages: ", color_lightblue);
	getline(f1, line);
	cout << line << endl;
	cout << endl;
	cout << endl;
}

///Display Audio_cd_book
void Controller::display_Audio_cd_book(ifstream& f2)
{
    int color = 10;
    int color_lightblue = 14;
    string line;

    Animation::draw_border(61, color);
	Animation::colorize_text("\t\t\t\t                  Info about book with this ID         \n", 3);
	Animation::draw_border(61, color);
	cout << endl;
	Animation::colorize_text("\t\t\t\t    Type: ", color_lightblue);
	Animation::colorize_text(" Audio CD Book ", 3);
	Animation::colorize_text("\t\t    ID: ", 3);
	getline(f2, line);
	cout << line;
	cout << endl;
	Animation::colorize_text("\t\t\t\t    Title: ", color_lightblue);
	getline(f2, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Release date: ", color_lightblue);
	getline(f2, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Author: ", color_lightblue);
	getline(f2, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    genre: ", color_lightblue);
	getline(f2, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Edition: ", color_lightblue);
	getline(f2, line);
    cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Language: ", color_lightblue);
	getline(f2, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Rating (1 -> 10): ", color_lightblue);
	getline(f2, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Price: ", color_lightblue);
	getline(f2, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Voice: ", color_lightblue);
	getline(f2, line);
    cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Listening lenth: ", color_lightblue);
	getline(f2, line);
	cout << line << endl;
	cout << endl;
	cout << endl;
}

///Display Digital_book
void Controller::display_digital_book(ifstream& f3)
{
    int color = 10;
    int color_lightblue = 14;
    string line;

    Animation::draw_border(61, color);
    Animation::colorize_text("\t\t\t\t                  Info about book with this ID         \n", 3);
	Animation::draw_border(61, color);
	cout << endl;
	Animation::colorize_text("\t\t\t\t    Type: ", color_lightblue);
	Animation::colorize_text(" Digital Book ", 3);
	Animation::colorize_text("\t\t\t\t    ID: ", 3);
	getline(f3, line);
	cout << line;
	cout << endl;
	Animation::colorize_text("\t\t\t\t    Title: ", color_lightblue);
	getline(f3, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Release date: ", color_lightblue);
	getline(f3, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Author: ", color_lightblue);
	getline(f3, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    genre: ", color_lightblue);
	getline(f3, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Edition: ", color_lightblue);
	getline(f3, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Language: ", color_lightblue);
	getline(f3, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Rating (1 -> 10): ", color_lightblue);
	getline(f3, line);
	cout << line << endl;
	Animation::colorize_text("\t\t\t\t    Price: ", color_lightblue);
	getline(f3, line);
	cout << line << endl;
	cout << endl;
	cout << endl;
}
