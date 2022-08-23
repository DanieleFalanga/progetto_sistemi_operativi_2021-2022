#include "AuxiliarFunctions/aux_functions.h"

#define PID_COLUMN 3    
#define USER_COLUMN 10 
#define PRI_COLUMN 22 
#define NI_COLUMN 27 
#define VIRT_COLUMN 32
#define RES_COLUMN 39
#define SHR_COLUMN 45
#define S_COLUMN 52
#define CPU_COLUMN 55
#define TIME_COLUMN 61
#define CMD_COLUMN 70

char* take_priority(char** buffer);
char* take_nice_value(char** buffer);
char* take_virt(char** buffer);
char* take_time(char** buffer);
char* take_res(char** buffer);
char* take_share(char** buffer);
void take_cmdline(char* path, char* string);
char* take_cpu_usage_process(char** buffer_stat);
char* take_status(char** buffer);
int search_group_id(char* path);
int is_a_process(char** buffer);
