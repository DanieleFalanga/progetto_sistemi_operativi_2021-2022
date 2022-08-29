#include "take_processes_info.h"
#include "terminal_handler.h"

struct args{
  WINDOW* process_box;
  WINDOW* terminal_box;
};
void* action_handler(void* input);