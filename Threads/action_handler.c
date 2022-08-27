#include "action_handler.h"

void* action_handler(void* arg){
    WINDOW* process_box=(WINDOW*) arg;
    int command;
    while(1){
        wgetch(process_box);
        switch (command){
            case KEY_DOWN:
                counter_row_min++;
        }
    }
}