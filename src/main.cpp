/*
 *******************************************************************************
 **																																					 **
 **		This is an ascii graphics RPG. That's that for now... ;)							 **
 **																																					 **
 *******************************************************************************
*/

//TODO implement actor moving/handling @ Map.NextTurn
//TODO refactor code to conform to sanity and consistant style
/*TODO store map objects and actors in a "list" array (vector's gonna get slow
 * here)*/
/*TODO - think on a more elegant viewport solution, consider placing the main
character into the character array of a map object. Then viewport would work
differently, and more elegantly.*/
/*TODO - due to different arrays containing items to be seen, consider
implementing a screen buffer instead of several print passes.*/
//TODO - destructors for classes storing objects in the heap

//core libraries
#include <string>
#include <fstream>
//third party libraries
#include <ncurses.h>
//proprietary classes,classes
#include "Map.h"
#include "Char.h"
#include "Viewport.h"
#include "System.h"

using namespace std;

void start(int _cmd);
void init_ncurses();//initialise ncurses mode and set initialisation params/funcs
void print_cen(int _ln, string _s);//prints _s centered on line _ln
void wellcome();
void goodbye();

string gmVer = "v0.0.20a || 2015-10-24[15:15:55]Saturday";

int main()
{
	int cmd = ' ';

	init_ncurses();
	wellcome();
	start(cmd);
	goodbye();
	
	endwin();//end ncurses mode
	return 0;
}

void start(int _cmd)
{
	Map lMap("tstTxt");
	System system;
	//lMap.LoadMapFile("tstTxt");
	lMap.test_make_char();
	Viewport mainView(0, 0, 19, 61);

	while(_cmd != 'q'){
		clear();
		mainView.Print(lMap, lMap.test_get_char());
		refresh();

		//_cmd = lMap.NextTurn();
		_cmd = system.startTurn(lMap);
	}
}

void init_ncurses()
{
	initscr();//start ncurses mode
	//initialisation functions
	raw();//pass all keyboard input to the program, avoiding terminal interupts
	noecho();//do not echo chars to terminal
	keypad(stdscr, true);//enable arrow keys, F1, F2 ,etc... for stdscr
	curs_set(0);//hide the cursor
}

void wellcome()
{
	print_cen(8, "Hello everyone.");
	print_cen(10, "Welcome to ASCIIWORLD!");
	print_cen(12, "I do hope you will enjoy your visit.");
	print_cen(13, "Press 'q' when you shall desire to leave.");
	print_cen(20, gmVer);
	refresh();
	getch();
}

void goodbye()
{
	clear();
	print_cen(8, "I do hope you enjoyed your stay.");
	print_cen(9, "Se you next time :)");
	getch();
}

void print_cen(int _ln, string _s)
{
	mvprintw(_ln, (80 / 2) - (_s.size() / 2), _s.c_str());
}
