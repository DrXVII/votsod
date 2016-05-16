/*
 *******************************************************************************
 **																																					 **
 **		This is an ascii graphics RPG. That's that for now... ;)							 **
 **																																					 **
 *******************************************************************************
*/

/*TODO store map objects and actors in a "list" array (vector's gonna get slow
 * here)*/
/*TODO - due to different arrays containing items to be seen, consider
implementing a screen buffer instead of several print passes.*/
//TODO - destructors for classes storing objects in the heap (e.g. Map class)

//core libraries
#include <string>
#include <fstream>
//third party libraries
#include <ncurses.h>
//own libs,classes
#include "Actors.h"
#include "Map.h"
#include "Viewport.h"
#include "System.h"

using std::string;

void start(int _cmd);
void render_mainw();// print the main game window
void init_ncurses();//initialise ncurses mode and set initialisation params/funcs
void wellcome();
void endgame();
void goodbye();
void print_cen(int _ln, const string& _s);//prints _s centered on line _ln

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
	System gamesys;
	gamesys.init();
	
	gamesys.add_actr(new Actor_Human(1, 1));
	/*gamesys.add_actr("watcher", 10, 38); caution - these use the old add_actr()
	gamesys.add_actr("watcher", 18, 58);
	gamesys.add_actr("watcher", 14, 73);
	gamesys.add_actr("watcher", 3, 42);
	gamesys.add_actr("watcher", 55, 20);
	gamesys.add_actr("watcher", 55, 40);
	gamesys.add_actr("watcher", 39, 14);
	gamesys.add_actr("watcher", 18, 7);*/

	while(_cmd != 'q'){
		gamesys.render_mainw();
		
		if(gamesys.get_herohp() <= 0){
			endgame();
			break;
		}

		_cmd = gamesys.start_turn();
		if(_cmd == -1){
			break;
		}
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
	string gmVer = "build: v0.00.5 || 2016-5-13[22:52:00]Friday";
	
	print_cen(8, "Hello everyone.");
	print_cen(10, "Welcome to ASCIIWORLD!");
	print_cen(12, "I do hope you will enjoy your visit.");
	print_cen(13, "Press 'q' when you shall desire to leave.");
	print_cen(20, gmVer);
	refresh();
	getch();
}

void endgame()
{
	print_cen(6,  "**********************************************");
	print_cen(7,  "***                                        ***");
	print_cen(8,  "***   The life of our hero has ended, and  ***");
	print_cen(9,  "*** with it - the story.                   ***");
	print_cen(10, "***                                        ***");
	print_cen(11, "**********************************************");
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

void print_cen(int _ln, const string& _s)
{
	mvprintw(_ln, (80 / 2) - (_s.size() / 2), _s.c_str());
}
