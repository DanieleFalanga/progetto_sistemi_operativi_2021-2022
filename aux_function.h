#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <regex.h>


#define BUFFER_SIZE 5096
#define NUM_OF_CORES (take_num_of_cores())
#define UPTIME (take_uptime("/proc/uptime"))

void strtok_aux(char* path, char* delimiter, char** str_buffer);
float take_mem_info(char* path_memfile);
double take_uptime(char* path_uptime);
int take_num_of_cores();
char* take_num_running_processes();     //return a string (not a number)
char* take_num_blocked_processes();     //return a string (not a number)
void take_cores_usage_percentages();
int searc_first_occurrence(char* path, char* delimiter, char* expression);
void searc_all_occurrences(char* path, char* delimiter, char* expression, int* buffer_indices);


