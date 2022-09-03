#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <regex.h>
#include <math.h>
#include <time.h>
#include <sys/times.h>
#include <ncurses.h>
#include <signal.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>


#define BUFFER_SIZE 5096
#define NUM_OF_CORES (take_num_of_cores())
#define UPTIME (take_uptime("/proc/uptime"))
#define PID_COLUMN 3    
#define USER_COLUMN 10 
#define PRI_COLUMN 30 
#define NI_COLUMN 35 
#define VIRT_COLUMN 40
#define RES_COLUMN 50
#define SHR_COLUMN 60
#define S_COLUMN 70
#define CPU_COLUMN 75
#define TIME_COLUMN 82
#define CMD_COLUMN 95
//int counter_row_min;



void strtok_aux(char* path, char* delimiter, char** str_buffer);
int search_first_occurrence(char* path, char* delimiter, char* expression);
void search_all_occurrences(char* path, char* delimiter, char* expression, int* buffer_indices);
double take_uptime(char* path);
void take_group_info(char** group_buffer);
int is_regular_file(const char *path); 
static void fine(int sig); 
