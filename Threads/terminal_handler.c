#include "terminal_handler.h"

void* terminal_handler(void* arg){
    WINDOW* terminal_box=(WINDOW*) arg;
    int character;
    wmove(terminal_box, 1, 1);
    echo();
    while(1){
        wgetch(terminal_box);
    }
}