#include "AuxiliarFunctions/aux_functions.h"



char* take_priority(char** buffer);
char* take_nice_value(char** buffer);
/*char* take_virt(char** buffer);
char* take_time(char** buffer);
char* take_res(char** buffer);
char* take_share(char** buffer);*/
void take_cmdline(char* path, char* string);
//char* take_cpu_usage_process(char** buffer_stat);
void take_status(char* buffer, char* status);
int search_group_id(char* path);
int is_a_process(char** buffer);
void take_virt(char** buffer, char* str);
void take_time(char** buffer, char* str);
void take_res(char** buffer, char* str);
void take_share(char** buffer, char* str);
void take_cpu_usage_process(char** buffer_stat, char* str);
