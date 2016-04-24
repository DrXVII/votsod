/*
 *******************************************************************************
 **                                                                           **
 **    This is an ascii graphics RPG. That's that for now... ;)               **
 **                                                                           **
 *******************************************************************************
*/

/*TODO - create System():{} - for collissions, and other things;
use System():{}; to get cmd information (e.g. KEY_DOWN) from Character.Action()
(or Character.TakeTurn()) then in system():{}; process the key and send back
data (e.g. tile probing results)
*/
/*TODO - think on a more elegant viewport solution, consider placing the main
character into the character array of a map object. Then viewport would work
differently, and more elegantly.*/
//TODO move the welcome and goodbye screens out of main()
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

using namespace std;

void start(int _cmd);
void ncursesInit();//initialise ncurses mode and set initialisation params/funcs
void printInCentre(int _ln, string _s);//prints _s centered on line _ln

string gmVer = "v0.0.20a || 2015-10-24[15:15:55]Saturday";

int main(){
  int cmd = ' ';

  ncursesInit();

  printInCentre(8, "Hello everyone.");
  printInCentre(10, "Welcome to ASCIIWORLD!");
  printInCentre(12, "I do hope you will enjoy your visit.");
  printInCentre(13, "Press 'q' when you shall desire to leave.");
  printInCentre(20, gmVer);
  refresh();
  getch();

  start(cmd);

  clear();
  printInCentre(8, "I do hope you enjoyed your stay.");
  printInCentre(9, "Se you next time :)");
  getch();

  endwin();//end ncurses mode
  return 0;
}

void start(int _cmd){
  Map lMap("tstTxt");
  //lMap.LoadMapFile("tstTxt");
  lMap.test_make_char();
  Viewport mainView(0, 0, 19, 61);

  while(_cmd != 'q'){
    clear();
    mainView.Print(lMap, lMap.test_get_char());
    refresh();

    _cmd = lMap.NextTurn();
  }
}

void ncursesInit(){
  initscr();//start ncurses mode
  //initialisation functions
  raw();//pass all keyboard input to the program, avoiding terminal interupts
  noecho();//do not echo chars to terminal
  keypad(stdscr, true);//enable arrow keys, F1, F2 ,etc... for stdscr
  curs_set(0);//hide the cursor
}

void printInCentre(int _ln, string _s){
  mvprintw(_ln, (80 / 2) - (_s.size() / 2), _s.c_str());
}
