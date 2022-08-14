#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <regex.h>
#include <math.h>
#include <time.h>
#include <sys/times.h>

#define BUFFER_SIZE 5096
#define NUM_OF_CORES (take_num_of_cores())
#define UPTIME (take_uptime("/proc/uptime"))




void strtok_aux(char* path, char* delimiter, char** str_buffer);
int search_first_occurrence(char* path, char* delimiter, char* expression);
void search_all_occurrences(char* path, char* delimiter, char* expression, int* buffer_indices);
double take_uptime(char* path);
void take_group_info(char** group_buffer);

