#include "AuxiliarFunctions/aux_functions.h"

char* take_priority(char** buffer);
char* take_nice_value(char** buffer);
char* take_virt(char** buffer);
int take_time(char** buffer);
int take_res(char** buffer);
int take_share(char** buffer);
char* take_cmdline(char* path, char* string);
double take_cpu_usage_process(char** buffer_stat);
char* take_status(char** buffer);
int search_group_id(char* path);