#include "SystemInformation/system_function.h"

extern int counter_row_min;

void take_info_system(WINDOW* system_box);
void print_system_info(WINDOW* system_box, float* percentages, float mem_info, char* num_blocked_processes, char* num_running_processes);

