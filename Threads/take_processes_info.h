#include "ProcessesInformation/proc_function.h"

void print_process_info(WINDOW* process_box, int count, char* pid, char* user, char* priority, char* nice_value, char* virt, char* res, char* share, char* status, char* cpu_usage, char* time, char* cmdline);

void take_processes_info(char** group_buffer, WINDOW* process_label);
