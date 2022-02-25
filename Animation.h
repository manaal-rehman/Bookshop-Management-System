#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
using namespace std;

class Animation
{
public:
	///Display phrase with borders
	static void frame_phrase(string, int, int count = 4);

	///Draw horizontal borders
	static void draw_border(int, int, int count = 4);

	///Exit from the system
	static int exit();

	///System initialization
	static void initializing();

	///Colorizes text
	static void colorize_text(string, int);

	///Display two points of border
	static void points();
};

#endif

