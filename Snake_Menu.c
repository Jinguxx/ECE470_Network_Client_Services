#include <menu.h>
#include <ncurses.h>
#include <string.h>
#include "optionMenus.h"

//menu for game option
void gameMenu() {
    WINDOW *w;
    char list[5][30] = {"Single", 
                        "Multiplayer", 
                        "Exit Game"};
    char item[5];
    int ch, i = 0, width = 7;
    initscr(); // initialize Ncurses

    w = newwin( 7, 20 , 1, 1 ); // create a new window
    box( w, 0, 0 ); // sets default borders for the window
    // now print all the menu items and highlight the first one
    for( i=0; i<5; i++ ) {
        if( i == 0 ) 
            wattron( w, A_STANDOUT ); // highlights the first item.
        else
            wattroff( w, A_STANDOUT );
        sprintf(item, "%-7s",  list[i]);
        mvwprintw( w, i+1, 2, "%s", item );
    }
    wrefresh( w ); // update the terminal screen
    i = 0;
    noecho(); // disable echoing of characters on the screen
    keypad( w, TRUE ); // enable keyboard input for the window.
    curs_set( 0 ); // hide the default screen cursor.
    // get the input
    while(( ch = wgetch(w)) != 'q'){ 
        // right pad with spaces to make the items appear with even width.
        sprintf(item, "%-7s",  list[i]); 
        mvwprintw( w, i+1, 2, "%s", item ); 
        // use a variable to increment or decrement the value based on the input.
        switch( ch ) {
            case KEY_UP:
                i--;
                //i = ( i<0 ) ? 4 : i;
                if (i == -1){
					i = 0;
				}
                break;
            case KEY_DOWN:
                i++;
                //i = ( i>4 ) ? 0 : i;
                if (i == 3){
					i = 2;
				}
                break;
            default:
                break;
        }
        // now highlight the next item in the list.
        
        wattron( w, A_STANDOUT );
        sprintf(item, "%-7s",  list[i]);
        mvwprintw( w, i+1, 2, "%s", item);
        wattroff( w, A_STANDOUT );
        
    }
    delwin( w );
    endwin();
}

void mainMenu(){
//Create Ncurses Window, with input, no echo and hidden cursor
    initscr();      
    cbreak();
    noecho();
    start_color();
    use_default_colors();    
    curs_set(0);

    WINDOW* win;
    int HEIGHT = 24;
    int WIDTH = 80;

    //Set window to new ncurses window
    win = newwin(HEIGHT, WIDTH, 0, 0);


    mvprintw((HEIGHT-20)/2, (WIDTH-58)/2,    "                  _");
    mvprintw((HEIGHT-20)/2 + 1, (WIDTH-58)/2,"                 | |");
    mvprintw((HEIGHT-20)/2 + 2, (WIDTH-58)/2,"  ___ _ __   __ _| | _____  ___");
    mvprintw((HEIGHT-20)/2 + 3, (WIDTH-58)/2," / __| '_ \\ / _` | |/ / _ \\/ __|");
    mvprintw((HEIGHT-20)/2 + 4, (WIDTH-58)/2," \\__ \\ | | | (_| |   <  __/\\__ \\");
    mvprintw((HEIGHT-20)/2 + 5, (WIDTH-58)/2," |___/_| |_|\\__,_|_|\\_\\___||___/  ");
    mvprintw((HEIGHT-20)/2 + 10, (WIDTH-58)/2," Instructions:"); 
    mvprintw((HEIGHT-20)/2 + 12, (WIDTH-58)/2," - Use the keys w, a, s, d to move your snake.");
    mvprintw((HEIGHT-20)/2 + 13, (WIDTH-58)/2," - Eat fruit to grow in length.");
    mvprintw((HEIGHT-20)/2 + 14, (WIDTH-58)/2," - Do not run in to other snakes, the game border"); 
    mvprintw((HEIGHT-20)/2 + 15, (WIDTH-58)/2,"   or yourself.");
    mvprintw((HEIGHT-20)/2 + 16, (WIDTH-58)/2," - The first snake to reach length 15 wins!");
    mvprintw((HEIGHT-20)/2 + 17, (WIDTH-58)/2," - Press '.' to quit at any time.");
    mvprintw((HEIGHT-20)/2 + 19, (WIDTH-58)/2,"Press any key to start . . ."); 
    getch();
    wrefresh(win);
    gameMenu();

}
