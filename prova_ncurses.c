#include <ncurses.h>
#include <stdio.h>
void print_process_information(){
    WINDOW* menu_win;
    int highlight=1;


    //start ncurses source
    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    refresh();    
  	mvprintw(10, 10, "Use arrow keys to go up and down, Press enter to select a choice");
 	getch();			/* Wait for user input */
	endwin();
}

int main(){
    print_process_information();
}