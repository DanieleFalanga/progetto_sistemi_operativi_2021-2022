#include "AuxiliarFunctions/aux_functions.h"

float take_mem_info(char** buffer);
double take_uptime(char* path);
int take_num_of_cores();
char* take_num_running_processes();     //return a string (not a number)
char* take_num_blocked_processes();     //return a string (not a number)
void take_first_cores_usage_percentages(float* percentages, float* cpu_last_sum, float* cpu_last_idle);

void take_cores_usage_percentages(float* percentages, float* cpu_last_sum, float* cpu_last_idle);



