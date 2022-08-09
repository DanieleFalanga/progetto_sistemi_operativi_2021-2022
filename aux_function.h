#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 5096

void strtok_aux(char* path, char* delimiter, char** str_buffer);
float mem_info(char* path_memfile, char** mem_buffer);