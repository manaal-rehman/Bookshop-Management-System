#ifndef CASHBOX_H
#define CASHBOX_H

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class Cashbox
{
private:
    float cash;     ///variable for cash
public:

    ///Default constructor
    Cashbox();

    ///Parameterized constructor
    Cashbox(float money);

    ///Returns the value of cash in cashbox
    float get_cash()
    {
        return cash;
    }

    ///operator overloading in order to show the amount of money in cashbox from object itself
    friend void operator<<(ostream &out, Cashbox cash)
    {
        ifstream money;

        money.open("cashbox.dat", ios::in | ios::binary);
        money.read((char*)&cash, sizeof(cash));
        cout << cash.get_cash();
        money.close();
    }

    ///Reads and displays the value of cash from cashbox.dat
    static void check_cashbox();

    ///Takes the price of book as argument and increases the cash amount - inside the file cashbox.dat
    static void update_cashbox(float);
};

#endif
