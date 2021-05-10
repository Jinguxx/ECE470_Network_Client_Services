
#include <menu.h>
#include <ncurses.h>
#include <string.h>

//menu for game option
gameOption() {
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
