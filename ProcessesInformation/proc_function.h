#include "AuxiliarFunctions/aux_functions.h"

#define PID_COLUMN 3    
#define USER_COLUMN 10 
#define PRI_COLUMN 22 
#define NI_COLUMN 27 
#define VIRT_COLUMN 32
#define RES_COLUMN 40
#define SHR_COLUMN 47
#define S_COLUMN 54
#define CPU_COLUMN 57
#define TIME_COLUMN 63
#define CMD_COLUMN 72

char* take_priority(char** buffer);
char* take_nice_value(char** buffer);
/*char* take_virt(char** buffer);
char* take_time(char** buffer);
char* take_res(char** buffer);
char* take_share(char** buffer);
*/char* take_cmdline(char* path);
//char* take_cpu_usage_process(char** buffer_stat);
char* take_status(char** buffer);
int search_group_id(char* path);
int is_a_process(char** buffer);
void take_virt(char** buffer, char* str);
void take_time(char** buffer, char* str);
void take_res(char** buffer, char* str);
void take_share(char** buffer, char* str);
void take_cpu_usage_process(char** buffer_stat, char* str);
