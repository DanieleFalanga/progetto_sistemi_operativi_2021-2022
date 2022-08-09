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
