#include "action_handler.h"


//Flavio
void* action_handler(void* input){
    WINDOW* process_box=((struct args*)input)->process_box;
    WINDOW* terminal_box=((struct args*)input)->terminal_box;
    int command;
    curs_set(1);
            int row, cols;

    while(1){
        command=wgetch(process_box);
        int row, cols;

        if(command==KEY_DOWN){
            wmove(process_box, 1, 1);
            wclrtoeol(process_box);
            counter_row_min++;
        }
        else if(command== KEY_UP){
            getmaxyx(process_box, row, cols);
            row--;
            wmove(process_box, row, 1);
            wclrtoeol(process_box);
            wmove(process_box, 1, 1);
            counter_row_min--;

        }
        else if(command==KEY_LEFT){
            wmove(terminal_box, 1, 1);
            terminal_handler(terminal_box);
        }
    }
}