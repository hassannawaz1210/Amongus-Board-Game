
#include "Game.h"
#include "winScreen.h"
#include <X11/Xlib.h>




int main()
{
    srand(time(0));
   //\\ XInitThreads();
    MainMenu menu;
    if(!menu.display()) return 0; //quit game on clicking '(x)'

    int winner = -1;
    Game game(menu.numOfPlayers);
    winner = game.launch();

    if(winner != -1)
    {
        winScreen winscreen;
        winscreen.display(winner);
    }

    return 0;
}
