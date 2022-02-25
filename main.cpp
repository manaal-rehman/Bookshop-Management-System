#include "Admin.h"
#include "Controller.h"
#include "fstream"

using namespace std;

	int main()
	{
	    Admin admin("MANAAL", "OOP");       ///Instance of Admin created and initialized

	    /// admin login and password written in file
        ofstream Administration;
        Administration.open("Admin.txt", ios::out);
        Administration << admin.get_login() << endl;
        Administration << admin.get_pswd();
        Administration.close();

		Controller bookShop;        ///Instance of Controller created
		bookShop.main_menu();
		return 0;
	}
