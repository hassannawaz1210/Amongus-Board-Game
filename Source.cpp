
#include "Game.h"
#include <X11/Xlib.h>




int main()
{
    srand(time(0));
   //\\ XInitThreads();
    MainMenu menu;
    if(!menu.display()) return 0; //quit game on clicking 'exit'

    Game game(menu.numOfPlayers);
    game.launch();

    return 0;
}