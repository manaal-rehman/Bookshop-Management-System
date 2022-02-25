#include "Cashbox.h"

using namespace std;

///Default constructor
Cashbox::Cashbox()
{
    cash = 0;
};

///Parameterized constructor
Cashbox::Cashbox(float money)
{
	cash = money;
};


///Reads and displays the value of cash from cashbox.dat
void Cashbox::check_cashbox()
{
	Cashbox cash;
	ifstream money;

	money.open("cashbox.dat", ios::binary);
	money.read((char*)&cash, sizeof(cash));
	cout << cash.get_cash();
	money.close();
}

///Takes the price of book as argument and increases the cash amount - inside the file cashbox.dat
void Cashbox::update_cashbox(float price_of_book)
{
	Cashbox cash;

	ifstream ifile;
	ofstream ofile;

	ifile.open("cashbox.dat", ios::binary);
	ifile.read((char*)&cash, sizeof(cash));
	float update = cash.get_cash() + price_of_book;
	ifile.close();

	ofile.open("cashbox.dat", ios::out | ios::binary);
	Cashbox new_cash(update);
	ofile.write((char*)&new_cash, sizeof(new_cash));
	ofile.close();
}
