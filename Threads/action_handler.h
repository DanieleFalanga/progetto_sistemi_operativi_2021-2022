#include "take_processes_info.h"
#include "terminal_handler.h"

struct args{
  WINDOW* process_box;
  WINDOW* terminal_box;
};

extern int counter_row_min;

void* action_handler(void* input);