#include "action_handler.h"

void* action_handler(void* arg){
    WINDOW* process_box=(WINDOW*) arg;
    int command;
    while(1){
        command=wgetch(process_box);
        switch (command){
            case KEY_DOWN:
                wmove(process_box, 1, 1);
                wclrtoeol(process_box);
                wrefresh(process_box);

                counter_row_min++;
                //printf("counter: %d\n", counter_row_min);
                //refresh();
        }
    }
}