#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <regex.h>


#define BUFFER_SIZE 5096
#define NUM_OF_CORES (take_num_of_cores())

void strtok_aux(char* path, char* delimiter, char** str_buffer);
int take_num_of_cores();