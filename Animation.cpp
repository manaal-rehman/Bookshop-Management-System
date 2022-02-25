#include "Animation.h"
#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

///Display two points of border
void Animation::points()
{
	colorize_text("*", 10);     ///prints * in Light Green color
	colorize_text("*", 10);
}

///Exit from the system
int Animation::exit()
{
		system("cls");
		string s;
        s = "Exiting from Bookshop Management System";
        cout << endl;
        colorize_text(s, 10);
		cout << endl;
		cout << endl << endl;
		return 0;
}

///System initialization
void Animation::initializing()
{
	int color = 10;
	cout << endl;
	draw_border(30, color);
	frame_phrase("                          ", color);
	frame_phrase("        LOGGED IN         ", color);
	frame_phrase("      SUCCESSFULLY.       ", color);
	frame_phrase("                          ", color);
	draw_border(30, color);
	Sleep(1000);    ///wait for 1000 milliseconds
	system("cls");

}

///Display phrase with borders
void Animation::frame_phrase(string phrase, int color, int count)
{
	string ch = "*";
	for (int i = 0; i < count; i++)
	{
		cout << "\t";
	}
	colorize_text(ch, color);
	colorize_text(ch, color);
	colorize_text(phrase, 14);
	colorize_text(ch, color);
	colorize_text(ch, color);
	cout << endl;
}

///Draw horizontal borders
void Animation::draw_border(int amount, int color, int count)
{
	string g = "*";
	for (int i = 0; i < count; i++)
	{
		cout << "\t";
	}
	for (int i = 0; i < amount; i++)
	{
		colorize_text(g, color);
	}
	cout << endl;
}

///Colorizes text
void Animation::colorize_text(string text, int color)
{
	int color_white = 15;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  ///Get a handle to the standard output
	SetConsoleTextAttribute(hConsole, color);
	cout << text;
	SetConsoleTextAttribute(hConsole, color_white);

}

