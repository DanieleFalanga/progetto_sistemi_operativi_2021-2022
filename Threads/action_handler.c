#include "action_handler.h"

void* action_handler(void* input){
    WINDOW* process_box=((struct args*)input)->process_box;
    WINDOW* terminal_box=((struct args*)input)->terminal_box;
    int command;
    curs_set(1);
            int row, cols;

    while(1){
        command=wgetch(process_box);
        int row, cols;

        switch (command){
            case KEY_LEFT:
                wmove(terminal_box, 1, 1);
                terminal_handler(terminal_box);
            case KEY_DOWN:
                wmove(process_box, 1, 1);
                wclrtoeol(process_box);
                wrefresh(process_box);
                counter_row_min++;
            case KEY_UP:
                getmaxyx(process_box, row, cols);
                row--;
                wmove(process_box, row, 1);
                wclrtoeol(process_box);
                wrefresh(process_box);
                counter_row_min--;
                wmove(process_box, 1, 1);


        }
     /*   
        command = getchar();
        switch(command) {
            case 't':
                    wmove(terminal_box, 1, 1);
                    terminal_handler(terminal_box);
                case 's':
                    //row=1;
                    wmove(process_box, row, 1);
                    wclrtoeol(process_box);
                    row++;
                  //  wclear(process_box);

                    wrefresh(process_box);
                    counter_row_min++;                  
                    wmove(process_box, 1, 1);
                case 'w':
                    getmaxyx(process_box, row, cols);
                    row--;
                    wmove(process_box, row, 1);
                    wclrtoeol(process_box);
                    wrefresh(process_box);
                    counter_row_min--;
                    wmove(process_box, 1, 1);
        }
*/
    }
}